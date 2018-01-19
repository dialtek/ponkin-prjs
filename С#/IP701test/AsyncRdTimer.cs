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

namespace _701C_src_PGM
{        
    /// <summary>
    /// Инициализация и управления асинхронным таймером
    /// обмен данными по тику
    /// </summary>
    class AsyncRdTimer
    {
        private System.Timers.Timer aTimer;

        private IPEndPoint SrcIpAndPort;
        private string[] SrcRdData = new string[5];

        private string SrcIpArdess;
        private string mV2set;

        private int interval = 300;    // инициализируем интервал таймера по умолчанию
        private int mSelectedSrcId;
        private int mCurrentSrcId;
        private int SrcPort;


        private bool SetOutputFlag = false;
        private bool SetVoltageFlag = false;
        private string OutputState2set;

        private bool SetVolageFlag = false;
        private string SetVСmdStatus;
        private Source IP701C; // экземпляр класса источника
        

        public event EventHandler OnSrcRdComplete; // создаем событие чтения данных источника

        /// <summary>
        /// Инициализация таймера
        /// </summary>
        public void Init()
        {
            try
            {
                // Create a timer with msecond interval.
                aTimer = new System.Timers.Timer(interval);
                // создание новой точки подключения
                SrcIpAndPort = new IPEndPoint(IPAddress.Parse(SrcIpArdess), SrcPort);
                IP701C = new Source(); // Новый экземпляр класса для общения с источниками

                // Hook up the Elapsed event for the timer.
                this.aTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnTimedEvent);
                Form1.OnSrcChargeCtrl += Form1_OnSrcChargeCtrl;
                //Form1.OnSetFileСfg += Form1_OnSetFileСfg;
                Form1.OnSetVoltage += Form1_OnSetVoltage;
                SrcRdData[0] = ID.ToString();
            }

            catch (Exception) { return; }
        }

        private void Form1_OnSrcChargeCtrl(object sender, string e)
        { /// обработка события ВКЛ/ВЫКЛ нагрузки выбранного источника
          /// 
            try
            {
                mSelectedSrcId = Convert.ToInt16(e.Substring(0, 1)); // вытаскиваем ID текущего источника
                OutputState2set = e.Substring(1);                    // вытаскиваем команду
                if (mSelectedSrcId == mCurrentSrcId) // проверяем, совпадают ли ID ? 
                {   // да
                    SetOutputFlag = true;
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
                    IP701C.ChargeON(SrcIpAndPort);
               else IP701C.ChargeOFF(SrcIpAndPort);
            }

            if (SetVolageFlag) // Уст. U
            {
                SetVolageFlag = false;
                SetVСmdStatus = IP701C.SetVoltage(SrcIpAndPort, mV2set);
                SrcRdData[2] = SetVСmdStatus;
                SrcRdData[3] = "1";
            }
            else SrcRdData[3] = "0";


            SrcRdData[4] = IP701C.GetStatus(SrcIpAndPort);
            // читаем массив строк - показаний источника
            SrcRdData[1] = IP701C.GetData(SrcIpAndPort);
            OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных
            Start(); // включаем таймер для нового измерения
        }
    }
}
