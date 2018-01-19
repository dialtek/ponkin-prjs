#region // README
//+1. Что если 1000000000 сообщений в очереди 						
//            если элементов в очереди больше 1000 уст. флаг переполнения 
//            писать в очередь только анализируя статус заполнения

//+2. Что если нет сообщений сутки
//            нет сообщения от прибора: будет callback как при обычном чтнении, 
//                                      но таймаут сработает и в нулевом элементе списка возврата будет стока "r/w error"
//+3. Что если приходят невалидные сообщения от железа
//            будет callback как при обычном чтнении,в нулевом элементе списка возврата будет стока "crc error"

//+5. Если нет соединения 
//            флаг соединения - false, 1 раз в сек. будет попытка соединения
//            если соединиться удастся - флаг соединения станет true

//6. Если есть соединение но нет ответа
//            так же как в п.2

//+7. Если нет соединения сутки
//            будет до усеру пытаться соединиться тк прога вкл. - режим ожидания вкл. прибора, это норм.

//+8. Если закончились элементы в очереди:
//            a) будет callback OnEmptyQueue и если через 2 сек. все еще нет поступления новых элементов в очередь, поток умирает.

//9. ВАЖНО! Не вызывать метод Start если есть элементы в очереди, иначе неведомые ошибки чтения.

//Определить интерфейсы для транспорта
//Прописать поведение на бумаге
#endregion

#region // INTERFACE
///// Геттеры/сеттеры

// 1. IpAdress/Port  - поля установки IP и порта
// 2. dequeue_period - период итераций выборки элементов из очереди: чтение и запись регистров в мс. макс. - 2000 мс, мин.  - 100 мс.
// 3. queue_count    - текущее число элементов в очереди
// 4. queue_overflow_status - состояние очереди:  FALSE - можно загружать новые элементы; TRUE  - переполнена (более 1000 элементов).
// 5. connected - статус соединения с сокетом. FALSE - нет соединения; TRUE  - успешное соединение.

///// методы

// 6. Start() - Запуск процесса подключения к сокету и обмена данными. первый запуск делать после загрузки ряда элементов в очередь,
// последующие - после опустошения очереди
// 7. push_queue() - добавление элемента в очередь

///// события

// 8. 
// 9. OnRwComplete - событие завершения обращения к modbus устройству
// 10. OnEmptyQueue - событие пустой очереди команд, если после вызова в течение 2 сек команды в очерель не поступят, 
// то поток умирает и сам не стартует. необходима новая инициализация.
// 11.OnException  - событие неизвестного исключения. вызывается, если возникшее исключение не попало под существующие классификации
// 12 GetMsgFromDe....
#endregion

using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.IO;

namespace LU20_correctors_ctrl
{
    /// <summary>
    /// класс осуществляет соединение с сокетом, взаимодейтсвие с Modbus устройствами
    /// </summary>
    class modbus_transport
    {
        private static modbus_transport instance;
        private modbus_transport() { }
        public static modbus_transport getInstance()
        {
            if (instance == null)
                instance = new modbus_transport();
            return instance;
        }

        private event EventHandler<KeyValuePair<Dictionary<string, int>, List<string>>> _RwComplete;
        private event EventHandler<string> _Empty_queue;
        private event EventHandler<string> _Exception;
        private event EventHandler<bool> _Connection;

        IPEndPoint IpAndPort;

        private NetworkStream _ns;
        private StreamReader _sr;
        private Socket _socket;

        private string _IPardess = "";               // IP
        private int _port = 0;                       // Port
        private int _empty_queue_cnt = 0;            // cчетчик итераций чикла с пустой очередью
        private int _period = 50;                   // период итараций выборки элементов из очереди: чтение и запись регистров в мс
        private bool queue_overflow_flag = false;    // флаг переполнения очереди
        private bool empty_queue_cbk_status = false; // флаг события пустой очереди
        private bool _connection_status = false;     // флаг состояния соединения
        private int _rw_timeout = 3000;              // таймаут записи и чтения
        private int _reconnect_timeout = 1000;       // таймаут нового подключения

        // для экстренной остановки потока
         static CancellationTokenSource ts = new CancellationTokenSource();
         CancellationToken ct = ts.Token;

        private modbus_rtu_helper _modbus = new modbus_rtu_helper();           // экземпляр класса помошника modbus
        private Queue<QueueElement> _modbus_queue = new Queue<QueueElement>(); // очередь команд

        //-----------------------------------------------------------------
        // PUBLIC REGION
        /// <summary>
        /// установка и чтение IP адреса
        /// </summary>
        public string IpAdress
        {
            get { return _IPardess; }
            set { _IPardess = value; }
        }

        /// <summary>
        /// установка и чтение порта
        /// </summary>
        public int Port
        {
            get { return _port; }
            set { _port = value; }
        }

        /// <summary>
        /// период итераций выборки элементов из очереди: чтение и запись регистров в мс
        /// макс. - 2000 мс
        /// мин.  - 100 мс.
        /// </summary>
        public int dequeue_period
        {
            get { return _period; }
            set
            {
                if (value > 2000) value = 2000;
                if (value < 20) value = 20;

                _period = value;
            }
        }

        /// <summary>
        /// текущее число элементов в очереди
        /// </summary>
        public int queue_count
        {
            get { return _modbus_queue.Count; }
        }

        /// <summary>
        /// состояние очереди: 
        /// FALSE - можно загружать новые элементы;
        /// TRUE  - переполнена (более 1000 элементов).
        /// </summary>
        public bool queue_overflow_status
        {
            get { return queue_overflow_flag; }
        }

        /// <summary>
        /// FALSE - нет соединения;
        /// TRUE  - успешное соединение.
        /// </summary>
        public bool connected
        {
            get { return _connection_status; }
        }

        /// <summary>
        /// Запуск процесса подключения к сокету и обмена данными
        /// </summary>
        public void Start()
        {
            empty_queue_cbk_status = false;
            try
            {
                IpAndPort = new IPEndPoint(IPAddress.Parse(_IPardess), _port); // точка соединения
                Task.Factory.StartNew(ReceiveData, ct);
                //Task.Factory.StartNew(ReceiveData);
            }
            catch (System.FormatException ex)
            {
                return;
            }

        }

        public void Stop()
        {
            ts.Cancel();
            DisconnectServer();
            
        }

        /// <summary>
        /// добавление элемента в очередь
        /// </summary>
        /// <param name="_queue"></param>
        public void push_queue(QueueElement _queue)
        {
            if (_modbus_queue.Count > 999)
            {
                queue_overflow_flag = true;
                return;
            }
            else queue_overflow_flag = false;

            _modbus_queue.Enqueue(_queue);
        }

        /// <summary>
        /// событие изменения статуса соединения
        /// </summary>
        public EventHandler<bool> OnChangeConnectionStatus
        {
            get { return _Connection; }
            set { _Connection += value; }
        }

        /// <summary>
        /// событие завершения обращения к modbus устройству
        /// </summary>
        public EventHandler<KeyValuePair<Dictionary<string, int>, List<string>>> OnRwComplete
        {
            get { return _RwComplete; }
            set { _RwComplete += value; }
        }

        /// <summary>
        /// событие пустой очереди команд
        /// </summary>
        public EventHandler<string> OnEmptyQueue
        {
            get { return _Empty_queue; }
            set { _Empty_queue += value; }
        }

        /// <summary>
        /// событие в случае исключения
        /// </summary>
        public EventHandler<string> OnException
        {
            get { return _Exception; }
            set { _Exception += value; }
        }

        public void GetMsgFromDevice(QueueElement msg)
        {
            push_queue(msg);
        }

        //-----------------------------------------------------------------
        // PRIVATE REGION
        private bool Connect2server(IPEndPoint IpAndPort)
        {
            bool retval = false;

            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _socket.ReceiveTimeout = _rw_timeout;

            // Connect using a timeout
            IAsyncResult result = _socket.BeginConnect(IpAndPort, null, null);
            try
            {
                bool success = result.AsyncWaitHandle.WaitOne(_reconnect_timeout, true);
                if (!success) _socket.Close(); // NOTE, MUST CLOSE THE SOCKET       
            }
            catch { }

            try
            {
                if (_socket.Connected)
                {
                    _ns = new NetworkStream(_socket);
                    _ns.ReadTimeout = _rw_timeout;
                    _ns.WriteTimeout = _rw_timeout;
                    _sr = new StreamReader(_ns);
                    _sr.BaseStream.ReadTimeout = _rw_timeout;
                    _sr.BaseStream.WriteTimeout = _rw_timeout;
                    retval = true;
                }
            }
            catch (Exception)
            {
                _ns.Close();
                _sr.Close();
                _socket.Close();
            }
            return retval;
        }

        private void DisconnectServer()
        {
            // отключение от сервера и закрытие всех потоков
            try
            {
                if (_socket != null)
                {

                    if (_socket.Connected)
                    {
                        _socket.Shutdown(SocketShutdown.Both);
                        // disconnect using a timeout
                        IAsyncResult result = _socket.BeginDisconnect(false, null, null);
                        bool success = result.AsyncWaitHandle.WaitOne(_reconnect_timeout, true);

                        _ns.Close();
                        _sr.Close();
                        _socket.Close();
                    }
                }

            }
            catch (Exception)
            { return; }
        }

        private void ReceiveData()
        {
            while (true) // цикл
            {
                try
                {
                   // if (ct.IsCancellationRequested) // another thread decided to cancel
                   //     break;

                    if (empty_queue_cbk_status == false)
                    {

                        KeyValuePair<Dictionary<string, int>, List<string>> device_response =     // ответ устройства
                                new KeyValuePair<Dictionary<string, int>, List<string>>();


                        DisconnectServer();
                        if (Connect2server(IpAndPort) == false)
                        {
                            _connection_status = false;                          // сброс флага успешного соединения
                            OnChangeConnectionStatus(this, _connection_status);  // вызов события смены статуса соединения с сокетом
                            Thread.Sleep(_reconnect_timeout);
                            continue;
                        }
                        else
                        {
                            _connection_status = true;                           // успешное соедигнение с сокетом, переход к анализу очереди
                            OnChangeConnectionStatus(this, _connection_status);  // вызов события смены статуса соединения с сокетом
                        }

                        while (true) // выполняем чтение, пока есть команды в очереди
                        {
                            try
                            {
                                //if (ct.IsCancellationRequested) // another thread decided to cancel
                                //    break;


                                // если есть элементы в очереди
                                if (_modbus_queue.Count != 0)
                                {
                                    _empty_queue_cnt = 0;                        // сброс счетчика итераций с пустой очередью
                                    var element_to_modbus = _modbus_queue.Dequeue();
                                    // извлечение команды записи из очереди, отсылка в устройство и чтение ответа
                                    device_response = _modbus.do_cmd(_ns, element_to_modbus.get_modbus_cmd());
                                    OnRwComplete(this, device_response);         // callback с результатом обращения к устройству
                                    Thread.Sleep(_period);                       // задержка перед следующей итерацией

                                    // если ошибка чтения/записи - переход к новому подкл.
                                    if (device_response.Value.Contains("r/w error"))
                                        break;
                                }
                                // если очередь пуста
                                else
                                {
                                    _empty_queue_cnt++;                 // инкремент счетчика итераций с пустой очередью 
                                    if (_empty_queue_cnt > 0)          // если более 50 итераций цикла с пустой очередью 
                                    {
                                        OnEmptyQueue(this, "oops");     // callback в случае пустой очереди в течение 5 сек
                                        empty_queue_cbk_status = true;
                                        //_ns.Flush();
                                        //Thread.Sleep(2000);             // ждем еще 2 сек

                                    }
                                    // если все еще очередь пуста..                                     
                                    if (empty_queue_cbk_status == true && _modbus_queue.Count < 1) break; // выход из цикла отправки команд                                                                                                                           
                                    else empty_queue_cbk_status = false;    // была реакция и появились команды в очереди - все ок, сброс флага 
                                }
                            }
                            catch (Exception ex)
                            {
                                OnException(this, ex.Message);
                                break; // без break НЕ РАБОТАЕТ
                            }

                        }
                    }
                    else break; // выход из функции
                }
                catch (Exception ex)
                {
                    OnException(this, ex.Message);
                }
            } // while connect
        } // receive data
        //-----------------------------------------------------------------
    }
}
