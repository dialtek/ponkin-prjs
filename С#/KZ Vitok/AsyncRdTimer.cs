using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace KZ_vitok
{
    class AsyncRdTimer
    {
        private System.Timers.Timer aTimer;

        private IPEndPoint SrcIpAndPort;
        private String SrcIpArdess;
        private String SrcRdData = "";
        private NetworkStream ns;
        private StreamReader sr;
        private Socket server;
        
        
        private int WatchDogCounter = 0;
        private int interval = 10;               // инициализируем интервал таймера по умолчанию
        private int mCurrentSrcId;
        private int SrcPort;


        public event EventHandler OnSrcRdComplete; // создаем событие чтения данных источника
        // и тд

        /// <summary>
        /// Инициализация подключения к серверу
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
        private bool Connect2server()
        {
            /// подключаемся к удаленному прибору в новом потоке
            ///

            SrcIpAndPort = new IPEndPoint(IPAddress.Parse(SrcIpArdess), SrcPort);

            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            server.ReceiveTimeout = 100;
            try
            {
                IAsyncResult result = server.BeginConnect(SrcIpAndPort, null, null);
                bool success = result.AsyncWaitHandle.WaitOne(100, true);

                if (!success)
                {
                    server.Close();
                    return false;
                }

            }
            catch (Exception)
            {
                server.Close();
                return false;
            }

            try
            {
                if (server.Connected)
                {
                    ns = new NetworkStream(server);
                    ns.ReadTimeout = 100;
                    sr = new StreamReader(ns);
                    sr.BaseStream.ReadTimeout = 100;
                    return true;
                }
                return false;
            }
            catch (Exception)
            {
                ns.Close();
                sr.Close();
                server.Close();
                return false;
            }
        }

        /// <summary>
        /// Отключение от сервера
        /// </summary>
        public void DisconnectServer()
        {
            /// отключение от сервера и закрытие всех потоков
            /// 
            try
            {
                if (server.Connected)
                {
                    server.Shutdown(SocketShutdown.Both);
                    server.Disconnect(true);
                }
                ns.Close();
                sr.Close();
                server.Close();
            }
            catch (Exception)
            { return; }
        }

        /// <summary>
        /// Установка и чтение ip адреса текущего источника
        /// </summary>
        public String IpAdress
        {
            get { return SrcIpArdess; }
            set { SrcIpArdess = value; }
        }

        /// <summary>
        /// Установка и чтение порта текущего источника
        /// </summary>
        public int Port
        {
            get { return SrcPort; }
            set { SrcPort = value; }
        }
 
        /// <summary>
        /// Чтение и установка интервала таймера
        /// </summary>
        public int Interval
        { 
            get { return interval; }
            set { interval = value; }      
        }

        /// <summary>
        /// Инициализация таймера
        /// </summary>
        public bool Init()
        {
            
            bool status = false;
            // Create a timer with msecond interval.
            aTimer = new System.Timers.Timer(interval);
            //SrcIpAndPort = new IPEndPoint(IPAddress.Parse(SrcIpArdess), SrcPort);
            //server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            // создание новой точки подключения
            //SrcIpAndPort = new IPEndPoint(IPAddress.Parse(SrcIpArdess), SrcPort);

            // Hook up the Elapsed event for the timer.
            this.aTimer.Elapsed     += new System.Timers.ElapsedEventHandler(OnTimedEvent);
            

           // IAsyncResult result = server.BeginConnect(SrcIpAndPort, null, null);
                //bool success = result.AsyncWaitHandle.WaitOne(200, true);


            //   if (server.Connected)
            //   {
            //       ns = new NetworkStream(server);
            //       ns.ReadTimeout = 1000;
            //       sr = new StreamReader(ns);
            //       sr.BaseStream.ReadTimeout = 1000;
            //       status = true;

            //   }
            //   else
            //   {
            //        status = false;
            //   }

            return status;

        }
  
        /// <summary>
        /// Запуск таймера
        /// </summary>
        public void Start() 
        {
            aTimer.Start();
        }

        /// <summary>
        /// Остановка таймера
        /// </summary>
        public void Stop()
        {
            aTimer.Stop();
        }

        /// <summary>
        /// Чтение данных ВДК-ФИ
        /// </summary>
        public String GetSrcData
        {
            get { return SrcRdData; }
        }

        private void OnTimedEvent(object source, System.Timers.ElapsedEventArgs e)
        {
            /// Измерения
            /// 
            Thread.CurrentThread.Priority = ThreadPriority.Highest;
            Stop();   // остановка асинхронного таймера

            if (Connect2server())
            {
                try
                {
                do
                {
                    SrcRdData = sr.ReadLine();
                }
                while (!SrcRdData.StartsWith("V"));
                if (SrcRdData.Contains("V"))
                {
                    SrcRdData = SrcRdData.Split('V')[1];
                    OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных
                }

                }
                 catch (Exception ex)
                {//System.NullReferenceException
                     // действие при отключении питания

                     SrcRdData = "-";
                     OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных
                 }

            }

            else
            {
                SrcRdData = "*";
                OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных

            }

            DisconnectServer();
            Start(); // включаем таймер для нового измерения

            }
        }
    }
