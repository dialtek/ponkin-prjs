using System;
using System.Data;
using System.Text;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using System.Collections.Generic;

namespace Insitek_src
{        
    /// <summary>
    /// Инициализация и управления асинхронным таймером
    /// обмен данными по тику
    /// </summary>
    class AsyncRdTimer
    {
        private System.Timers.Timer aTimer;

        private IPEndPoint SrcIpAndPort;
        private string[] SrcRdData = new string[3];

        private string SrcIpArdess;
        private ushort mV2set;

        private int interval = 100;    // инициализируем интервал таймера по умолчанию
        private byte mSelectedSrcId;
        private int mCurrentSrcId;
        private int SrcPort;
        private int temp = 0;

        private bool SetOutputFlag = false;
        private bool SetVoltageFlag = false;
        private string OutputState2set;

        private bool SetVolageFlag = false;
        private string SetVСmdStatus;
        private Source Insitek; // экземпляр класса источника
        

        public event EventHandler OnSrcRdComplete; // создаем событие чтения данных источника

        /// <summary>
        /// Инициализация таймера
        /// </summary>
        public void Init()
        {
            // Create a timer with msecond interval.
            aTimer = new System.Timers.Timer(interval);
            // создание новой точки подключения
            SrcIpAndPort = new IPEndPoint(IPAddress.Parse(SrcIpArdess), SrcPort);
            Insitek = new Source(); // Новый экземпляр класса для общения с источниками

            // Hook up the Elapsed event for the timer.
            this.aTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnTimedEvent);
            Form1.OnSrcChargeCtrl += Form1_OnSrcChargeCtrl;
            //Form1.OnSetFileСfg += Form1_OnSetFileСfg;
            Form1.OnSetVoltage += Form1_OnSetVoltage;
            SrcRdData[0] = ID.ToString();
            //Insitek.SetID(247,SrcIpAndPort,10);

        }

        private void Form1_OnSrcChargeCtrl(object sender, string e)
        { /// обработка события ВКЛ/ВЫКЛ нагрузки выбранного источника
          /// 
            try
            {
                
                mSelectedSrcId = Convert.ToByte((e.Split(';')[0])); //ытаскиваем ID текущего источника
                OutputState2set = e.Split(';')[1];                      // вытаскиваем команду
                SetOutputFlag = true;
         
            }
            catch (Exception)
            {
                return;
            }
        }

        private void Form1_OnSetVoltage(object sender, Dictionary<byte, ushort> e)
        {
            /// Изменение параметров выбранного источника
          try
           {
            foreach (KeyValuePair<byte, ushort> pair in e)
                {
                    mSelectedSrcId = pair.Key;
                    mV2set = pair.Value;
                }
            SetVolageFlag = true;
           } 
          catch (Exception)
          {
            return;
          }
        }

        /// <summary>
        /// Установка и чтение ID текущего источника
        /// </summary>
        public int ID
        {
            get { return mCurrentSrcId; }
            set { mCurrentSrcId = value; }
        }

        /// <summary>
        /// Установка и чтение IP адреса текущего источника
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
        /// Чтение напряжения источника 
        /// </summary>
        public string[] GetSrcData
        {
            get { return SrcRdData; }
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

        private void OnTimedEvent(object source, System.Timers.ElapsedEventArgs e)
        {
            /// Измерения

            Stop();   // остановка асинхронного таймера
            // читаем массив строк - показаний источника
            if (SetOutputFlag)
            {
                SetOutputFlag = false;
               if (OutputState2set == "ON")
                    Insitek.SetOutput(mSelectedSrcId, SrcIpAndPort, (ushort)1);
               else Insitek.SetOutput(mSelectedSrcId, SrcIpAndPort, (ushort)0);
            }

            if (SetVolageFlag)
            {
                SetVolageFlag = false;
                SetVСmdStatus = Insitek.SetVoltage(mSelectedSrcId, SrcIpAndPort, mV2set);
                Thread.Sleep(30);
                Insitek.Save2EEPROM(mSelectedSrcId, SrcIpAndPort);
                Thread.Sleep(30);
            }
            SrcRdData = Insitek.GetData(Convert.ToByte(mCurrentSrcId), SrcIpAndPort);

            OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных
           
            Start(); // включаем таймер для нового измерения
        }
    }
}
