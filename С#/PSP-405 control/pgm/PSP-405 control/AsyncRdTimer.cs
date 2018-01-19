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


namespace PSP_405_control
{
    /// <summary>
    /// Инициализация и управления асинхронным таймером
    /// обмен данными по тику
    /// </summary>
    class AsyncRdTimer
    {
        private System.Timers.Timer aTimer;

        private IPEndPoint SrcIpAndPort;
        private String[] SrcRdData = new String[5];

        private string mV2set;
        private String mCurrentLimit;
        private String mVoltageLimit;
        private String SrcIpArdess;

        private String mSrcVoltage, mSRC_I_limit, mSRC_V_limit;// переменные источника ВДК-ФИ

        private int interval = 10;               // инициализируем интервал таймера по умолчанию
        private int mSelectedSrcId;
        private int mCurrentSrcId;
        private int SrcPort;  

        private bool SetOutputFlag  = false;
        private string OutputState2set;

        private bool SetVolageFlag    = false;
        private bool SetCurrLimitFlag = false;
        private bool SetVoltLimitFlag = false;
        private bool SetFileСfgFlag   = false;

        public event EventHandler OnSrcRdComplete; // создаем событие чтения данных источника
        // и тд

        private Source PSP_405; // экземпляр класса источника

        /// <summary>
        /// 
        /// </summary>
        public int SrcId
        {
            get { return mCurrentSrcId; }
            set { mCurrentSrcId = value; }
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
        public void Init()
        {
            // Create a timer with msecond interval.
            aTimer = new System.Timers.Timer(interval);
            // создание новой точки подключения
            SrcIpAndPort = new IPEndPoint(IPAddress.Parse(SrcIpArdess), SrcPort);
            PSP_405 = new Source(); // Новый экземпляр класса для общения с источниками

            // Hook up the Elapsed event for the timer.
            this.aTimer.Elapsed     += new System.Timers.ElapsedEventHandler(OnTimedEvent);
            Form1.OnSrcOutputCtrl += Form1_OnVDK_FI_SetOutput;
            Form1.OnSetFileСfg      += Form1_OnSetFileСfg; 
            Form1.OnSetParam += Form1_OnSetParam;
        }

        private void Form1_OnVDK_FI_SetOutput(object sender, string e)
        { /// обработка события ВКЛ/ВЫКЛ нагрузки выбранного источника
            mSelectedSrcId = Convert.ToInt16(e.Substring(0, 1)); // вытаскиваем ID текущего источника
            OutputState2set = e.Substring(1);                    // вытаскиваем команду
            if (mSelectedSrcId == mCurrentSrcId) // проверяем, совпадают ли ID ? 
            {   // да
                SetOutputFlag = true;
            }           
        }

        private void Form1_OnSetFileСfg(object sender, Dictionary<int, List<string>> e)
        {
            /// Задание параметров из конфигурационного файла
            /// 
            SetFileСfgFlag = true;

            foreach (KeyValuePair<int, List<string>> element in e)
            {
                mSelectedSrcId = element.Key;

                if (mSelectedSrcId == mCurrentSrcId) // проверяем, совпадают ли ID ? 
                {   // да
                    mSrcVoltage = element.Value[0];
                    mSRC_I_limit = element.Value[1];
                    mSRC_V_limit = element.Value[2];
                    //MessageBox.Show(mSrcVoltage + "V" + mSRC_I_limit + "Ilim" + 
                        
                                    //mSRC_V_limit+"Vlim" + mSelectedSrcId.ToString());
                }
            }

        }

        private void Form1_OnSetParam(object sender, Dictionary<int, List<string>> e)
        {
            /// Изменение параметров выбранного источника

            foreach (KeyValuePair<int, List<string>> element in e)
            {
                mSelectedSrcId = element.Key;

                if (mSelectedSrcId == mCurrentSrcId) // проверяем, совпадают ли ID ? 
                {   // да
                    //if (mV2set != element.Value[0])
                    //{
                    //    mV2set = element.Value[0];
                    //    SetVolageFlag = true;
                    //}

                    //if (mCurrentLimit != element.Value[1])
                    //{
                        mCurrentLimit = element.Value[1];
                        SetCurrLimitFlag = true;
                    //}

                    //if (mVoltageLimit != element.Value[2])
                    //{
                        mVoltageLimit = element.Value[2];
                        mV2set = element.Value[2];
                        SetVolageFlag = true;
                        SetVoltLimitFlag = true;
                    //}
                }
            }  
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
        public String[] GetSrcData
        {
            get { return SrcRdData; }
        }

        private void OnTimedEvent(object source, System.Timers.ElapsedEventArgs e)
        {
            /// Измерения

            Stop();   // остановка асинхронного таймера

            if (SetFileСfgFlag) // Применение конфигурации из файла
            {   
                 SetFileСfgFlag = false;

                 PSP_405.SetVoltage(SrcIpAndPort, mSrcVoltage);
                 PSP_405.SetCurrentLimit(SrcIpAndPort, mSRC_I_limit);
                 PSP_405.SetVoltageLimit(SrcIpAndPort, mSRC_V_limit);
                 PSP_405.SetOutputOn(SrcIpAndPort);
            }
            
            if (SetOutputFlag)  // ВКЛ/ВЫКЛ нагрузки
            {
                SetOutputFlag = false;

                if (OutputState2set == "ON") PSP_405.SetOutputOn(SrcIpAndPort);
                else PSP_405.SetOutputOff(SrcIpAndPort);
            }
        

             if (SetVolageFlag) // Уст. U
             {
                 SetVolageFlag = false;

                 PSP_405.SetVoltage(SrcIpAndPort, mV2set);
             }

             if (SetCurrLimitFlag)  // Уст. ограничения по I
             {
                 SetCurrLimitFlag = false;

                 PSP_405.SetCurrentLimit(SrcIpAndPort, mCurrentLimit);
             }

             if (SetVoltLimitFlag) // Уст. ограничения по U
             {
                 SetVoltLimitFlag = false;

                 PSP_405.SetVoltageLimit(SrcIpAndPort, mVoltageLimit);
             }

            // читаем массив строк - показаний источника
            SrcRdData = PSP_405.GetData(SrcIpAndPort);

            OnSrcRdComplete(this, new EventArgs()); // обновляем событие получения данных

            Start(); // включаем таймер для нового измерения
            }
            
        }  
    }