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

namespace BUV_ctrl
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
        private string mV2set;

        private int interval = 100;    // инициализируем интервал таймера по умолчанию
        private int mSelectedSrcId;
        private int mCurrentSrcId;
        private int SrcPort;


        private bool SetOutputFlag = false;
        private bool SetVoltageFlag = false;
        private string OutputState2set;

        private bool SetVolageFlag = false;
        private string SetVСmdStatus;
        private Source BUV; // экземпляр класса источника
        

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
            BUV = new Source(); // Новый экземпляр класса для общения с источниками

            // Hook up the Elapsed event for the timer.
            this.aTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnTimedEvent);
            Form1.OnSrcChargeCtrl += Form1_OnSrcChargeCtrl;
            //Form1.OnSetFileСfg += Form1_OnSetFileСfg;
            Form1.OnSetVoltage += Form1_OnSetVoltage;
        }

        private void Form1_OnSrcChargeCtrl(object sender, Dictionary<int, string> e)
        { /// обработка события ВКЛ/ВЫКЛ нагрузки выбранного источника
          /// 

            try
            {
                foreach (KeyValuePair<int, string> pair in e)
                {
                    mSelectedSrcId = pair.Key;// вытаскиваем ID текущего источника

                    if (mSelectedSrcId == mCurrentSrcId) // проверяем, совпадают ли ID ? 
                    {   // да

                        OutputState2set = pair.Value;
                        SetOutputFlag = true;
                    }
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        private void Form1_OnSetVoltage(object sender, Dictionary<int, string> e)
        {
            /// Изменение параметров выбранного источника

            foreach (KeyValuePair<int, string> pair in e)
            {
                mSelectedSrcId = pair.Key;

                if (mSelectedSrcId == mCurrentSrcId) // проверяем, совпадают ли ID ? 
                {   // да

                    mV2set = pair.Value;
                    SetVolageFlag = true;
                }
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

            //if (SetFileСfgFlag) // Применение конфигурации из файла
            //{
            //    SetFileСfgFlag = false;

            //    PSP_405.SetVoltage(SrcIpAndPort, mSrcVoltage);
            //    PSP_405.SetCurrentLimit(SrcIpAndPort, mSRC_I_limit);
            //    PSP_405.SetVoltageLimit(SrcIpAndPort, mSRC_V_limit);
            //    PSP_405.SetOutputOn(SrcIpAndPort);
            //}

            if (SetOutputFlag)  // ВКЛ/ВЫКЛ нагрузки
            {
                SetOutputFlag = false;

                if (OutputState2set == "ON")
                    BUV.ChargeON(SrcIpAndPort);
               else BUV.ChargeOFF(SrcIpAndPort);
            }

            if (SetVolageFlag) // Уст. U
            {
                SetVolageFlag = false;
                SetVСmdStatus = BUV.SetVoltage(SrcIpAndPort, mV2set);
            }

  
            SrcRdData[2] = BUV.GetStatus(SrcIpAndPort);
            if (SrcRdData[2][5] == '1')
             {
               SrcRdData[0] = BUV.GetCurrent(SrcIpAndPort);
             }
 
            // SrcRdData[0] - I
            // SrcRdData[1] - U
            // SrcRdData[2] - статус

            // читаем массив строк - показаний источника
            SrcRdData[1] = BUV.GetVoltage(SrcIpAndPort);
            OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных
            Start(); // включаем таймер для нового измерения
        }
    }
}
