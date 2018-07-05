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
using System.Windows;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.IO;
using System.Collections.Generic;

namespace klystron_mod
{
    /// <summary>
    /// класс осуществляет соединение с сокетом, взаимодейтсвие с ИП702С
    /// </summary>
    class IP702_transport
    {
        private static IP702_transport instance;
        private IP702_transport() { }
        public static IP702_transport getInstance()
        {
            if (instance == null)
                instance = new IP702_transport();
            return instance;
        }

        private event EventHandler<string[]> _RwComplete;
        private event EventHandler<string> _Exception;
        private event EventHandler<bool> _Connection;

        IPEndPoint IpAndPort;
        SourceCommand IP702src;

        private NetworkStream _ns;
        private StreamReader _sr;
        private Socket _socket;

        private string _IPardess = "";               // IP
        private int _port = 0;                       // Port
        private int _period = 200;                   // период итараций выборки элементов из очереди: чтение и запись регистров в мс
        private bool _connection_status = false;     // флаг состояния соединения
        private int _rw_timeout = 1000;              // таймаут записи и чтения
        private int _reconnect_timeout = 1000;       // таймаут нового подключения
        private string[] SrcRdData = new string[5];  // массив для чтения данных из источника
        private bool SetOutputFlag = false;          // флаг уст. состояния выхода источника 
        private int OutputState2set = 0;             // значение уст. выхода источника
        private bool SetVoltageFlag = false;         // флаг уст. напряжения выхода источника 
        private string mV2set;                       // величина U для установки

        // для экстренной остановки потока
        static CancellationTokenSource ts = new CancellationTokenSource();
         CancellationToken ct = ts.Token;
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
        public int read_period
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
            try
            {
                IpAndPort = new IPEndPoint(IPAddress.Parse(_IPardess), _port); // точка соединения
                Task.Factory.StartNew(ReceiveData, ct);
                IP702src = new SourceCommand();
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
        public EventHandler<string[]> OnRwComplete
        {
            get { return _RwComplete; }
            set { _RwComplete += value; }
        }

        /// <summary>
        /// событие в случае исключения
        /// </summary>
        public EventHandler<string> OnException
        {
            get { return _Exception; }
            set { _Exception += value; }
        }

        public void GetMsgFromDevice(Dictionary<string,int> msg)
        {   

            foreach (KeyValuePair<string, int> pair in msg)
            {
                string action = pair.Key;
                int param = pair.Value;     

                switch (action)
                {
                    case "set_voltage":
                        MessageBox.Show("U = " + param.ToString());
                        SetVoltageFlag = true;
                        mV2set = param.ToString("X4");
                    break;
                    //---
                    case "set_output":
                        OutputState2set = param;
                        MessageBox.Show("State = " + param.ToString());
                        SetOutputFlag = true;
                    break;
                }
            }
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
                            if (SetOutputFlag)  // ВКЛ/ВЫКЛ нагрузки
                            {
                                SetOutputFlag = false;

                                if (OutputState2set == 1)
                                     IP702src.ChargeON (_ns,_sr);
                                else IP702src.ChargeOFF(_ns, _sr);
                            }

                            if (SetVoltageFlag) // Уст. U
                            {
                                SetVoltageFlag = false;
                                SrcRdData[2] = IP702src.SetVoltage(_ns, _sr, mV2set);
                                SrcRdData[3] = "1";
                            }
                            else SrcRdData[3] = "0";

                            // читаем массив строк - показаний источника
                            SrcRdData[1] = IP702src.GetVoltage(_ns);
                            SrcRdData[4] = IP702src.GetStatus(_ns);

                            OnRwComplete(this, SrcRdData);         // callback с результатом обращения к устройству
                            Thread.Sleep(_period);                 // задержке перед следующей итерацией
                        }
                        catch (Exception ex)
                        {
                            //OnException(this, ex.Message);
                            //break; // без break НЕ РАБОТАЕТ
                            //System.Windows.MessageBox.Show("");

                        }
                    }
                }
                catch (Exception ex)
                {
                    //OnException(this, ex.Message);
                    System.Windows.MessageBox.Show("");
                }
            } // while connect
        } // receive data
        //-----------------------------------------------------------------
    }
}
