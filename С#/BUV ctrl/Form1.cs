using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using System.Media;
using System.IO.IsolatedStorage;

namespace BUV_ctrl
{

    /// <summary>
    /// MAIN CLASS
    /// </summary> 
    public partial class Form1 : Form
    {
        // контейнер с ID и парам. для уст. U
        private Dictionary<int, string> IdAndV2set = new Dictionary<int, string>();
        // контейнер с ID и парам. для уст. выхода
        private Dictionary<int, string> IdAndOutState = new Dictionary<int, string>();

        int U2set = 0;

        // массив элементов ListViewItem для динамического заполнения таблицы данными об источниках питания 
        public static ListViewItem[] Src_data = new ListViewItem[50];
        private AsyncRdTimer[] Src = new AsyncRdTimer[50]; // Инстанциирование класса асинхр. работы с ист.1
        private string[] SrcReadVoltage = new string[50];
        private string[] SrcReadCurrent = new string[50];
        private string[] SrcSetVoltage = new string[50];
        private string[] SrcStatusByte = new string[50];

        public static int NumberOfSources = 1; // переменная количества источников

        public static List<string> IPadrList = new List<string>(); // лист для хранения всех IP адресов источников
        public static List<string> PortList = new List<string>(); // лист для хранения всех портов источников
        public static List<string> SrcNames = new List<string>();  // лист для хранения всех имен источников

        //-------------------------------------------------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        //public static event EventHandler<String> OnSrcOutputCtrl;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetParam;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetFileСfg;

        //---------------------------------  Методы ------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        public static event EventHandler<Dictionary<int, String>> OnSetVoltage;
        public static event EventHandler<Dictionary<int, string>> OnSrcChargeCtrl;

        // Specify a name for your top-level folder.
        const string ISOLATED_FILE_NAME = "buv_cfq.txt";

        private String GetCurrTime()
        {
            /// Получаем текущие дату и время 

            String CurrentTime;

            CurrentTime = DateTime.Now.TimeOfDay.ToString();
            CurrentTime = CurrentTime.Substring(0, 8);
            return ("  " + CurrentTime);
        }

        private String GetTimeAndData()
        {
            /// Получаем текущие дату и время 
            String CurrentTime;
            String CurrentDate;

            CurrentTime = DateTime.Now.TimeOfDay.ToString();
            CurrentTime = CurrentTime.Substring(0, 8);
            CurrentDate = DateTime.Now.Date.ToString();
            CurrentDate = CurrentDate.Substring(0, 10);

            return (CurrentDate + " " + " " + CurrentTime);
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // ЛЖФ ЛУ 0
            Src[0] = new AsyncRdTimer();
            Src[0].Interval = 300;
            Src[0].IpAdress = "172.16.21.80";
            Src[0].Port = 4001;
            Src[0].ID = 0;
            Src[0].Init();
            Src[0].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[0].Start();
            SrcNames.Add("ЛЖФ ЛУ 1");
            // ЛЖФ ЛУ 1
            Src[1] = new AsyncRdTimer();
            Src[1].Interval = 300;
            Src[1].IpAdress = "172.16.21.81";
            Src[1].Port = 4001;
            Src[1].ID = 1;
            Src[1].Init();
            Src[1].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[1].Start();
            SrcNames.Add("ЛЖФ ЛУ 2");
            // ЛЖФ ЛУ 2
            Src[2] = new AsyncRdTimer();
            Src[2].Interval = 300;
            Src[2].IpAdress = "172.16.21.82";
            Src[2].Port = 4001;
            Src[2].ID = 2;
            Src[2].Init();
            Src[2].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[2].Start();
            SrcNames.Add("ЛЖФ ЛУ 3");
            // ЛЖФ ЛУ 3
            Src[3] = new AsyncRdTimer();
            Src[3].Interval = 300;
            Src[3].IpAdress = "172.16.21.83";
            Src[3].Port = 4001;
            Src[3].ID = 3;
            Src[3].Init();
            Src[3].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[3].Start();
            SrcNames.Add("ЛЖФ ЛУ 3");
            // ЛЖФ ЛУ 4
            Src[4] = new AsyncRdTimer();
            Src[4].Interval = 300;
            Src[4].IpAdress = "172.16.21.84";
            Src[4].Port = 4001;
            Src[4].ID = 4;
            Src[4].Init();
            Src[4].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[4].Start();
            SrcNames.Add("ЛЖФ ЛУ 4");
            // ЛЖФ ЛУ 5
            Src[5] = new AsyncRdTimer();
            Src[5].Interval = 300;
            Src[5].IpAdress = "172.16.21.85";
            Src[5].Port = 4001;
            Src[5].ID = 5;
            Src[5].Init();
            Src[5].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[5].Start();
            SrcNames.Add("ЛЖФ ЛУ 5");
            // ЛЖФ ЛУ 6
            Src[6] = new AsyncRdTimer();
            Src[6].Interval = 300;
            Src[6].IpAdress = "172.16.21.86";
            Src[6].Port = 4001;
            Src[6].ID = 6;
            Src[6].Init();
            Src[6].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[6].Start();
            SrcNames.Add("ЛЖФ ЛУ 6");
            // ЛЖФ ЛУ 7
            Src[7] = new AsyncRdTimer();
            Src[7].Interval = 300;
            Src[7].IpAdress = "172.16.21.87";
            Src[7].Port = 4001;
            Src[7].ID = 7;
            Src[7].Init();
            Src[7].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[7].Start();
            SrcNames.Add("ЛЖФ ЛУ 7");
            // ЛЖФ ЛУ 8
            Src[8] = new AsyncRdTimer();
            Src[8].Interval = 300;
            Src[8].IpAdress = "172.16.21.88";
            Src[8].Port = 4001;
            Src[8].ID = 8;
            Src[8].Init();
            Src[8].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[8].Start();
            SrcNames.Add("ЛЖФ ЛУ 8");
            // ЛЖФ ЛУ 9
            Src[9] = new AsyncRdTimer();
            Src[9].Interval = 300;
            Src[9].IpAdress = "172.16.21.89";
            Src[9].Port = 4001;
            Src[9].ID = 9;
            Src[9].Init();
            Src[9].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[9].Start();
            SrcNames.Add("ЛЖФ ЛУ 9");
            // ЛЖФ ЛУ 10
            Src[10] = new AsyncRdTimer();
            Src[10].Interval = 300;
            Src[10].IpAdress = "172.16.21.90";
            Src[10].Port = 4001;
            Src[10].ID = 10;
            Src[10].Init();
            Src[10].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[10].Start();
            SrcNames.Add("ЛЖФ ЛУ 10");
            // ЛЖФ ЛУ 11/1
            Src[11] = new AsyncRdTimer();
            Src[11].Interval = 300;
            Src[11].IpAdress = "172.16.21.91";
            Src[11].Port = 4001;
            Src[11].ID = 11;
            Src[11].Init();
            Src[11].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[11].Start();
            SrcNames.Add("ЛЖФ ЛУ 11/1");
            // ЛЖФ ЛУ 11/2
            Src[12] = new AsyncRdTimer();
            Src[12].Interval = 300;
            Src[12].IpAdress = "172.16.21.92";
            Src[12].Port = 4001;
            Src[12].ID = 12;
            Src[12].Init();
            Src[12].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[12].Start();
            SrcNames.Add("ЛЖФ ЛУ 11/2");
            // ЛЖФ Н 1
            Src[13] = new AsyncRdTimer();
            Src[13].Interval = 300;
            Src[13].IpAdress = "172.16.21.93";
            Src[13].Port = 4001;
            Src[13].ID = 13;
            Src[13].Init();
            Src[13].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[13].Start();
            SrcNames.Add("ЛЖФ Н 1");
            // ЛЖФ Н 2
            Src[14] = new AsyncRdTimer();
            Src[14].Interval = 300;
            Src[14].IpAdress = "172.16.21.94";
            Src[14].Port = 4001;
            Src[14].ID = 14;
            Src[14].Init();
            Src[14].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[14].Start();
            SrcNames.Add("ЛЖФ Н 2");
            // ЛЖФ Н 3
            Src[15] = new AsyncRdTimer();
            Src[15].Interval = 300;
            Src[15].IpAdress = "172.16.21.95";
            Src[15].Port = 4001;
            Src[15].ID = 15;
            Src[15].Init();
            Src[15].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[15].Start();
            SrcNames.Add("ЛЖФ Н 3");
            // ЛЖФ Н 4
            Src[16] = new AsyncRdTimer();
            Src[16].Interval = 300;
            Src[16].IpAdress = "172.16.21.96";
            Src[16].Port = 4001;
            Src[16].ID = 16;
            Src[16].Init();
            Src[16].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[16].Start();
            SrcNames.Add("ЛЖФ Н 4");
            // ЛЖФ Н 5
            Src[17] = new AsyncRdTimer();
            Src[17].Interval = 300;
            Src[17].IpAdress = "172.16.21.97";
            Src[17].Port = 4001;
            Src[17].ID = 17;
            Src[17].Init();
            Src[17].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[17].Start();
            SrcNames.Add("ЛЖФ Н 5");
            // ЛЖФ Н 6
            Src[18] = new AsyncRdTimer();
            Src[18].Interval = 300;
            Src[18].IpAdress = "172.16.21.98";
            Src[18].Port = 4001;
            Src[18].ID = 18;
            Src[18].Init();
            Src[18].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[18].Start();
            SrcNames.Add("ЛЖФ Н 6");
            // ЛЖФ Н 7
            Src[19] = new AsyncRdTimer();
            Src[19].Interval = 300;
            Src[19].IpAdress = "172.16.21.99";
            Src[19].Port = 4001;
            Src[19].ID = 19;
            Src[19].Init();
            Src[19].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[19].Start();
            SrcNames.Add("ЛЖФ Н 7");
            // ЛЖФ Н 8
            Src[20] = new AsyncRdTimer();
            Src[20].Interval = 300;
            Src[20].IpAdress = "172.16.21.100";
            Src[20].Port = 4001;
            Src[20].ID = 20;
            Src[20].Init();
            Src[20].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[20].Start();
            SrcNames.Add("ЛЖФ Н 8");
            // ЛЖФ Н 9
            Src[21] = new AsyncRdTimer();
            Src[21].Interval = 300;
            Src[21].IpAdress = "172.16.21.101";
            Src[21].Port = 4001;
            Src[21].ID = 21;
            Src[21].Init();
            Src[21].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[21].Start();
            SrcNames.Add("ЛЖФ Н 9");
            // ЛЖФ Н 10
            Src[22] = new AsyncRdTimer();
            Src[22].Interval = 300;
            Src[22].IpAdress = "172.16.21.102";
            Src[22].Port = 4001;
            Src[22].ID = 22;
            Src[22].Init();
            Src[22].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[22].Start();
            SrcNames.Add("ЛЖФ Н 10");
            // ЛЖФ Н 11
            Src[23] = new AsyncRdTimer();
            Src[23].Interval = 300;
            Src[23].IpAdress = "172.16.21.103";
            Src[23].Port = 4001;
            Src[23].ID = 23;
            Src[23].Init();
            Src[23].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[23].Start();
            SrcNames.Add("ЛЖФ Н 11");
            // ЛЖФ Н 12
            Src[24] = new AsyncRdTimer();
            Src[24].Interval = 300;
            Src[24].IpAdress = "172.16.21.104";
            Src[24].Port = 4001;
            Src[24].ID = 24;
            Src[24].Init();
            Src[24].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[24].Start();
            SrcNames.Add("ЛЖФ Н 12");

            NumberOfSources = 25; // общее кол-во источников

            try
            {   // загрузка последней конфигурации
                LoadSettings();
            }
            catch (Exception)
            {   // если не нашелся файл конфигурации
                return;
            }

            Update_timer.Start();
        }

        void OnSrcRdComplete(object sender, EventArgs e)
        {
            /// Чтение 

            string[] SRC_data = new string[3];  // Массив строк для чтения показаний источника

            // SrcRdData[0] - I
            // SrcRdData[1] - U
            // SrcRdData[2] - статус

            for (int i = 0; i < NumberOfSources; i++)
            {
                SRC_data = Src[i].GetSrcData;    // читаем показания
                SrcReadCurrent[i] = SRC_data[0]; // сохраняем I
                SrcReadVoltage[i] = SRC_data[1]; // сохраняем U
                SrcStatusByte[i]  = SRC_data[2]; // сохраняем статус
            }

        }

        private void Update_timer_Tick(object sender, EventArgs e)
        {
            try
            {   // обновление значений токов и напряжений всех ВУВов
                B1_Uread.Text = SrcReadVoltage[0];
                B1_Iread.Text = SrcReadCurrent[0];
                B2_Uread.Text = SrcReadVoltage[1];
                B2_Iread.Text = SrcReadCurrent[1];
                B3_Uread.Text = SrcReadVoltage[2];
                B3_Iread.Text = SrcReadCurrent[2];
                B4_Uread.Text = SrcReadVoltage[3];
                B4_Iread.Text = SrcReadCurrent[3];
                B5_Uread.Text = SrcReadVoltage[4];
                B5_Iread.Text = SrcReadCurrent[4];
                B6_Uread.Text = SrcReadVoltage[5];
                B6_Iread.Text = SrcReadCurrent[5];
                B7_Uread.Text = SrcReadVoltage[6];
                B7_Iread.Text = SrcReadCurrent[6];
                B8_Uread.Text = SrcReadVoltage[7];
                B8_Iread.Text = SrcReadCurrent[7];
                B9_Uread.Text = SrcReadVoltage[8];
                B9_Iread.Text = SrcReadCurrent[8];
                B10_Uread.Text = SrcReadVoltage[9];
                B10_Iread.Text = SrcReadCurrent[9];
                B11_Uread.Text = SrcReadVoltage[10];
                B11_Iread.Text = SrcReadCurrent[10];
                B12_Uread.Text = SrcReadVoltage[11];
                B12_Iread.Text = SrcReadCurrent[11];
                B13_Uread.Text = SrcReadVoltage[12];
                B13_Iread.Text = SrcReadCurrent[12];
                B14_Uread.Text = SrcReadVoltage[13];
                B14_Iread.Text = SrcReadCurrent[13];
                B15_Uread.Text = SrcReadVoltage[14];
                B15_Iread.Text = SrcReadCurrent[14];
                B16_Uread.Text = SrcReadVoltage[15];
                B16_Iread.Text = SrcReadCurrent[15];
                B17_Uread.Text = SrcReadVoltage[16];
                B17_Iread.Text = SrcReadCurrent[16];
                B18_Uread.Text = SrcReadVoltage[17];
                B18_Iread.Text = SrcReadCurrent[17];
                B19_Uread.Text = SrcReadVoltage[18];
                B19_Iread.Text = SrcReadCurrent[18];
                B20_Uread.Text = SrcReadVoltage[19];
                B20_Iread.Text = SrcReadCurrent[19];
                B21_Uread.Text = SrcReadVoltage[20];
                B21_Iread.Text = SrcReadCurrent[20];
                B22_Uread.Text = SrcReadVoltage[21];
                B22_Iread.Text = SrcReadCurrent[21];
                B23_Uread.Text = SrcReadVoltage[22];
                B23_Iread.Text = SrcReadCurrent[22];
                B24_Uread.Text = SrcReadVoltage[23];
                B24_Iread.Text = SrcReadCurrent[23];
                B25_Uread.Text = SrcReadVoltage[24];
                B25_Iread.Text = SrcReadCurrent[24];

                if (B1_Uread.Text == "-")
                {   // если источник не отвечает...
                    B1_OutOn_B.Enabled = false; B1_OutOff_B.Enabled = false; B1_OutState.BackColor = Color.LightGray;
                }
                if (B2_Uread.Text == "-")
                {   // если источник не отвечает...
                    B2_OutOn_B.Enabled = false; B2_OutOff_B.Enabled = false; B2_OutState.BackColor = Color.LightGray;
                }
                if (B2_Uread.Text == "-")
                {   // если источник не отвечает...
                    B2_OutOn_B.Enabled = false; B2_OutOff_B.Enabled = false; B2_OutState.BackColor = Color.LightGray;
                }
                if (B3_Uread.Text == "-")
                {   // если источник не отвечает...
                    B3_OutOn_B.Enabled = false; B3_OutOff_B.Enabled = false; B3_OutState.BackColor = Color.LightGray;
                }
                if (B4_Uread.Text == "-")
                {   // если источник не отвечает...
                    B4_OutOn_B.Enabled = false; B4_OutOff_B.Enabled = false; B4_OutState.BackColor = Color.LightGray;
                }
                if (B5_Uread.Text == "-")
                {   // если источник не отвечает...
                    B5_OutOn_B.Enabled = false; B5_OutOff_B.Enabled = false; B5_OutState.BackColor = Color.LightGray;
                }
                if (B6_Uread.Text == "-")
                {   // если источник не отвечает...
                    B6_OutOn_B.Enabled = false; B6_OutOff_B.Enabled = false; B6_OutState.BackColor = Color.LightGray;
                }
                if (B7_Uread.Text == "-")
                {   // если источник не отвечает...
                    B7_OutOn_B.Enabled = false; B7_OutOff_B.Enabled = false; B7_OutState.BackColor = Color.LightGray;
                }
                if (B8_Uread.Text == "-")
                {   // если источник не отвечает...
                    B8_OutOn_B.Enabled = false; B8_OutOff_B.Enabled = false; B8_OutState.BackColor = Color.LightGray;
                }
                if (B9_Uread.Text == "-")
                {   // если источник не отвечает...
                    B9_OutOn_B.Enabled = false; B9_OutOff_B.Enabled = false; B9_OutState.BackColor = Color.LightGray;
                }
                if (B10_Uread.Text == "-")
                {   // если источник не отвечает...
                    B10_OutOn_B.Enabled = false; B10_OutOff_B.Enabled = false; B10_OutState.BackColor = Color.LightGray;
                }
                if (B11_Uread.Text == "-")
                {   // если источник не отвечает...
                    B11_OutOn_B.Enabled = false; B11_OutOff_B.Enabled = false; B11_OutState.BackColor = Color.LightGray;
                }
                if (B12_Uread.Text == "-")
                {   // если источник не отвечает...
                    B12_OutOn_B.Enabled = false; B12_OutOff_B.Enabled = false; B12_OutState.BackColor = Color.LightGray;
                }
                if (B13_Uread.Text == "-")
                {   // если источник не отвечает...
                    B13_OutOn_B.Enabled = false; B13_OutOff_B.Enabled = false; B13_OutState.BackColor = Color.LightGray;
                }
                if (B14_Uread.Text == "-")
                {   // если источник не отвечает...
                    B14_OutOn_B.Enabled = false; B14_OutOff_B.Enabled = false; B14_OutState.BackColor = Color.LightGray;
                }
                if (B15_Uread.Text == "-")
                {   // если источник не отвечает...
                    B15_OutOn_B.Enabled = false; B15_OutOff_B.Enabled = false; B15_OutState.BackColor = Color.LightGray;
                }
                if (B16_Uread.Text == "-")
                {   // если источник не отвечает...
                    B16_OutOn_B.Enabled = false; B16_OutOff_B.Enabled = false; B16_OutState.BackColor = Color.LightGray;
                }
                if (B17_Uread.Text == "-")
                {   // если источник не отвечает...
                    B17_OutOn_B.Enabled = false; B17_OutOff_B.Enabled = false; B17_OutState.BackColor = Color.LightGray;
                }
                if (B18_Uread.Text == "-")
                {   // если источник не отвечает...
                    B18_OutOn_B.Enabled = false; B18_OutOff_B.Enabled = false; B18_OutState.BackColor = Color.LightGray;
                }
                if (B19_Uread.Text == "-")
                {   // если источник не отвечает...
                    B19_OutOn_B.Enabled = false; B19_OutOff_B.Enabled = false; B19_OutState.BackColor = Color.LightGray;
                }
                if (B20_Uread.Text == "-")
                {   // если источник не отвечает...
                    B20_OutOn_B.Enabled = false; B20_OutOff_B.Enabled = false; B20_OutState.BackColor = Color.LightGray;
                }
                if (B21_Uread.Text == "-")
                {   // если источник не отвечает...
                    B21_OutOn_B.Enabled = false; B21_OutOff_B.Enabled = false; B21_OutState.BackColor = Color.LightGray;
                }
                if (B22_Uread.Text == "-")
                {   // если источник не отвечает...
                    B22_OutOn_B.Enabled = false; B22_OutOff_B.Enabled = false; B22_OutState.BackColor = Color.LightGray;
                }
                if (B23_Uread.Text == "-")
                {   // если источник не отвечает...
                    B23_OutOn_B.Enabled = false; B23_OutOff_B.Enabled = false; B23_OutState.BackColor = Color.LightGray;
                }
                if (B24_Uread.Text == "-")
                {   // если источник не отвечает...
                    B24_OutOn_B.Enabled = false; B24_OutOff_B.Enabled = false; B24_OutState.BackColor = Color.LightGray;
                }
                if (B25_Uread.Text == "-")
                {   // если источник не отвечает...
                    B25_OutOn_B.Enabled = false; B25_OutOff_B.Enabled = false; B25_OutState.BackColor = Color.LightGray;
                }
                //-------------------------------------------------------------------------------------------------------
                // обработка байтов ошибок и информации
                if (SrcStatusByte[0].Length == 8)
               {   
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[0][7] == '1')
                    { B1_OutOn_B.Enabled = false; B1_OutOff_B.Enabled = true; B1_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[0][7] == '0') { B1_OutOn_B.Enabled = true; B1_OutOff_B.Enabled = false; B1_OutState.BackColor = Color.LightGray; }
                    else { B1_OutOn_B.Enabled = false; B1_OutOff_B.Enabled = false; B1_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[0][6] == '1') B1_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[0][6] == '0') B1_ErrState.BackColor = Color.LimeGreen;
                    else B1_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[1].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[1][7] == '1')
                    { B2_OutOn_B.Enabled = false; B2_OutOff_B.Enabled = true; B2_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[1][7] == '0') { B2_OutOn_B.Enabled = true; B2_OutOff_B.Enabled = false; B2_OutState.BackColor = Color.LightGray; }
                    else { B2_OutOn_B.Enabled = false; B2_OutOff_B.Enabled = false; B2_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[1][6] == '1') B2_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[1][6] == '0') B2_ErrState.BackColor = Color.LimeGreen;
                    else B2_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[2].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[2][7] == '1')
                    { B3_OutOn_B.Enabled = false; B3_OutOff_B.Enabled = true; B3_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[2][7] == '0') { B3_OutOn_B.Enabled = true; B3_OutOff_B.Enabled = false; B3_OutState.BackColor = Color.LightGray; }
                    else { B3_OutOn_B.Enabled = false; B3_OutOff_B.Enabled = false; B3_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[2][6] == '1') B3_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[2][6] == '0') B3_ErrState.BackColor = Color.LimeGreen;
                    else B3_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[3].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[3][7] == '1')
                    { B4_OutOn_B.Enabled = false; B4_OutOff_B.Enabled = true; B4_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[3][7] == '0') { B4_OutOn_B.Enabled = true; B4_OutOff_B.Enabled = false; B4_OutState.BackColor = Color.LightGray; }
                    else { B4_OutOn_B.Enabled = false; B4_OutOff_B.Enabled = false; B4_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[3][6] == '1') B3_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[3][6] == '0') B4_ErrState.BackColor = Color.LimeGreen;
                    else B4_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[4].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[4][7] == '1')
                    { B5_OutOn_B.Enabled = false; B5_OutOff_B.Enabled = true; B5_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[4][7] == '0') { B5_OutOn_B.Enabled = true; B5_OutOff_B.Enabled = false; B5_OutState.BackColor = Color.LightGray; }
                    else { B5_OutOn_B.Enabled = false; B5_OutOff_B.Enabled = false; B5_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[4][6] == '1') B5_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[4][6] == '0') B5_ErrState.BackColor = Color.LimeGreen;
                    else B5_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[5].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[5][7] == '1')
                    { B6_OutOn_B.Enabled = false; B6_OutOff_B.Enabled = true; B6_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[5][7] == '0') { B6_OutOn_B.Enabled = true; B6_OutOff_B.Enabled = false; B6_OutState.BackColor = Color.LightGray; }
                    else { B6_OutOn_B.Enabled = false; B6_OutOff_B.Enabled = false; B6_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[5][6] == '1') B6_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[5][6] == '0') B6_ErrState.BackColor = Color.LimeGreen;
                    else B6_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[6].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[6][7] == '1')
                    { B7_OutOn_B.Enabled = false; B7_OutOff_B.Enabled = true; B7_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[6][7] == '0') { B7_OutOn_B.Enabled = true; B7_OutOff_B.Enabled = false; B7_OutState.BackColor = Color.LightGray; }
                    else { B7_OutOn_B.Enabled = false; B7_OutOff_B.Enabled = false; B7_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[6][6] == '1') B7_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[6][6] == '0') B7_ErrState.BackColor = Color.LimeGreen;
                    else B7_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[7].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[7][7] == '1')
                    { B8_OutOn_B.Enabled = false; B8_OutOff_B.Enabled = true; B8_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[7][7] == '0') { B8_OutOn_B.Enabled = true; B8_OutOff_B.Enabled = false; B8_OutState.BackColor = Color.LightGray; }
                    else { B8_OutOn_B.Enabled = false; B8_OutOff_B.Enabled = false; B8_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[7][6] == '1') B8_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[7][6] == '0') B8_ErrState.BackColor = Color.LimeGreen;
                    else B8_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[8].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[8][7] == '1')
                    { B9_OutOn_B.Enabled = false; B9_OutOff_B.Enabled = true; B9_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[8][7] == '0') { B9_OutOn_B.Enabled = true; B9_OutOff_B.Enabled = false; B9_OutState.BackColor = Color.LightGray; }
                    else { B9_OutOn_B.Enabled = false; B9_OutOff_B.Enabled = false; B9_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[8][6] == '1') B9_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[8][6] == '0') B9_ErrState.BackColor = Color.LimeGreen;
                    else B9_ErrState.BackColor = Color.LightGray;
                }
                //--------------------------------------------------------------------------
                if (SrcStatusByte[9].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[9][7] == '1')
                    { B10_OutOn_B.Enabled = false; B10_OutOff_B.Enabled = true; B10_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[9][7] == '0') { B10_OutOn_B.Enabled = true; B10_OutOff_B.Enabled = false; B10_OutState.BackColor = Color.LightGray; }
                    else { B10_OutOn_B.Enabled = false; B10_OutOff_B.Enabled = false; B10_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[9][6] == '1') B10_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[9][6] == '0') B10_ErrState.BackColor = Color.LimeGreen;
                    else B10_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[10].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[10][7] == '1')
                    { B11_OutOn_B.Enabled = false; B11_OutOff_B.Enabled = true; B11_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[10][7] == '0') { B11_OutOn_B.Enabled = true; B11_OutOff_B.Enabled = false; B11_OutState.BackColor = Color.LightGray; }
                    else { B11_OutOn_B.Enabled = false; B11_OutOff_B.Enabled = false; B11_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[10][6] == '1') B11_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[10][6] == '0') B11_ErrState.BackColor = Color.LimeGreen;
                    else B11_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[11].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[11][7] == '1')
                    { B12_OutOn_B.Enabled = false; B12_OutOff_B.Enabled = true; B12_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[11][7] == '0') { B12_OutOn_B.Enabled = true; B12_OutOff_B.Enabled = false; B12_OutState.BackColor = Color.LightGray; }
                    else { B12_OutOn_B.Enabled = false; B12_OutOff_B.Enabled = false; B12_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[11][6] == '1') B12_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[11][6] == '0') B12_ErrState.BackColor = Color.LimeGreen;
                    else B12_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[12].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[12][7] == '1')
                    { B13_OutOn_B.Enabled = false; B13_OutOff_B.Enabled = true; B13_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[12][7] == '0') { B13_OutOn_B.Enabled = true; B13_OutOff_B.Enabled = false; B13_OutState.BackColor = Color.LightGray; }
                    else { B13_OutOn_B.Enabled = false; B13_OutOff_B.Enabled = false; B13_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[12][6] == '1') B13_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[12][6] == '0') B13_ErrState.BackColor = Color.LimeGreen;
                    else B13_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[13].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[13][7] == '1')
                    { B14_OutOn_B.Enabled = false; B14_OutOff_B.Enabled = true; B14_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[13][7] == '0') { B14_OutOn_B.Enabled = true; B14_OutOff_B.Enabled = false; B14_OutState.BackColor = Color.LightGray; }
                    else { B14_OutOn_B.Enabled = false; B14_OutOff_B.Enabled = false; B14_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[13][6] == '1') B14_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[13][6] == '0') B14_ErrState.BackColor = Color.LimeGreen;
                    else B14_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[14].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[14][7] == '1')
                    { B15_OutOn_B.Enabled = false; B15_OutOff_B.Enabled = true; B15_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[14][7] == '0') { B15_OutOn_B.Enabled = true; B15_OutOff_B.Enabled = false; B15_OutState.BackColor = Color.LightGray; }
                    else { B15_OutOn_B.Enabled = false; B15_OutOff_B.Enabled = false; B15_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[14][6] == '1') B15_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[14][6] == '0') B15_ErrState.BackColor = Color.LimeGreen;
                    else B15_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[15].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[15][7] == '1')
                    { B16_OutOn_B.Enabled = false; B16_OutOff_B.Enabled = true; B16_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[15][7] == '0') { B16_OutOn_B.Enabled = true; B16_OutOff_B.Enabled = false; B16_OutState.BackColor = Color.LightGray; }
                    else { B16_OutOn_B.Enabled = false; B16_OutOff_B.Enabled = false; B16_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[15][6] == '1') B16_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[15][6] == '0') B16_ErrState.BackColor = Color.LimeGreen;
                    else B16_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[16].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[16][7] == '1')
                    { B17_OutOn_B.Enabled = false; B17_OutOff_B.Enabled = true; B17_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[16][7] == '0') { B17_OutOn_B.Enabled = true; B17_OutOff_B.Enabled = false; B17_OutState.BackColor = Color.LightGray; }
                    else { B17_OutOn_B.Enabled = false; B17_OutOff_B.Enabled = false; B17_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[16][6] == '1') B17_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[16][6] == '0') B17_ErrState.BackColor = Color.LimeGreen;
                    else B17_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[17].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[17][7] == '1')
                    { B18_OutOn_B.Enabled = false; B18_OutOff_B.Enabled = true; B18_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[17][7] == '0') { B18_OutOn_B.Enabled = true; B18_OutOff_B.Enabled = false; B18_OutState.BackColor = Color.LightGray; }
                    else { B18_OutOn_B.Enabled = false; B18_OutOff_B.Enabled = false; B18_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[17][6] == '1') B18_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[17][6] == '0') B18_ErrState.BackColor = Color.LimeGreen;
                    else B18_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[18].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[18][7] == '1')
                    { B19_OutOn_B.Enabled = false; B19_OutOff_B.Enabled = true; B19_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[18][7] == '0') { B19_OutOn_B.Enabled = true; B19_OutOff_B.Enabled = false; B19_OutState.BackColor = Color.LightGray; }
                    else { B19_OutOn_B.Enabled = false; B19_OutOff_B.Enabled = false; B19_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[18][6] == '1') B19_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[18][6] == '0') B19_ErrState.BackColor = Color.LimeGreen;
                    else B19_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[19].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[19][7] == '1')
                    { B20_OutOn_B.Enabled = false; B20_OutOff_B.Enabled = true; B20_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[19][7] == '0') { B20_OutOn_B.Enabled = true; B20_OutOff_B.Enabled = false; B20_OutState.BackColor = Color.LightGray; }
                    else { B20_OutOn_B.Enabled = false; B20_OutOff_B.Enabled = false; B20_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[19][6] == '1') B20_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[19][6] == '0') B20_ErrState.BackColor = Color.LimeGreen;
                    else B20_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[20].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[20][7] == '1')
                    { B21_OutOn_B.Enabled = false; B21_OutOff_B.Enabled = true; B21_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[20][7] == '0') { B12_OutOn_B.Enabled = true; B21_OutOff_B.Enabled = false; B21_OutState.BackColor = Color.LightGray; }
                    else { B21_OutOn_B.Enabled = false; B21_OutOff_B.Enabled = false; B21_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[20][6] == '1') B21_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[20][6] == '0') B21_ErrState.BackColor = Color.LimeGreen;
                    else B21_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[21].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[21][7] == '1')
                    { B22_OutOn_B.Enabled = false; B22_OutOff_B.Enabled = true; B22_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[21][7] == '0') { B22_OutOn_B.Enabled = true; B22_OutOff_B.Enabled = false; B22_OutState.BackColor = Color.LightGray; }
                    else { B22_OutOn_B.Enabled = false; B22_OutOff_B.Enabled = false; B22_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[21][6] == '1') B22_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[21][6] == '0') B22_ErrState.BackColor = Color.LimeGreen;
                    else B22_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[22].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[22][7] == '1')
                    { B23_OutOn_B.Enabled = false; B23_OutOff_B.Enabled = true; B23_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[22][7] == '0') { B23_OutOn_B.Enabled = true; B23_OutOff_B.Enabled = false; B23_OutState.BackColor = Color.LightGray; }
                    else { B23_OutOn_B.Enabled = false; B23_OutOff_B.Enabled = false; B23_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[22][6] == '1') B23_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[22][6] == '0') B23_ErrState.BackColor = Color.LimeGreen;
                    else B23_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[23].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[23][7] == '1')
                    { B24_OutOn_B.Enabled = false; B24_OutOff_B.Enabled = true; B24_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[23][7] == '0') { B24_OutOn_B.Enabled = true; B24_OutOff_B.Enabled = false; B24_OutState.BackColor = Color.LightGray; }
                    else { B24_OutOn_B.Enabled = false; B24_OutOff_B.Enabled = false; B24_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[23][6] == '1') B24_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[23][6] == '0') B24_ErrState.BackColor = Color.LimeGreen;
                    else B24_ErrState.BackColor = Color.LightGray;
                }//--------------------------------------------------------------------------
                if (SrcStatusByte[24].Length == 8)
                {
                    /// ------------- состояние выхода ----------------
                    if (SrcStatusByte[24][7] == '1')
                    { B25_OutOn_B.Enabled = false; B25_OutOff_B.Enabled = true; B25_OutState.BackColor = Color.LimeGreen; }
                    else if (SrcStatusByte[24][7] == '0') { B25_OutOn_B.Enabled = true; B25_OutOff_B.Enabled = false; B25_OutState.BackColor = Color.LightGray; }
                    else { B25_OutOn_B.Enabled = false; B25_OutOff_B.Enabled = false; B25_OutState.BackColor = Color.LightGray; }
                    /// ------------- статус ошибки ----------------
                    if (SrcStatusByte[24][6] == '1') B25_ErrState.BackColor = Color.Red;
                    else if (SrcStatusByte[24][6] == '0') B25_ErrState.BackColor = Color.LimeGreen;
                    else B25_ErrState.BackColor = Color.LightGray;
                }

            } // try

            catch (Exception exp)
            {
                return;
            }
        }

        private void LoadSettings()
        {
            /// восстановление последних значений контролов
            /// 
            int cfg_buf;
            // Read all lines from the file in isolated storage.
            IsolatedStorageFile isoStore =
            IsolatedStorageFile.GetStore(IsolatedStorageScope.User
            | IsolatedStorageScope.Assembly, null, null);

            IsolatedStorageFileStream iStream =
              new IsolatedStorageFileStream(ISOLATED_FILE_NAME,
              FileMode.Open, isoStore);

            StreamReader reader = new StreamReader(iStream);
            string[] settings = new string[25];

            for (int i = 0; i < 25; i++)
                settings[i] = reader.ReadLine(); 
            // восстановление значений из изолированного хранилища посторчно
            B1_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[0]));
            B2_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[1]));
            B3_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[2]));
            B4_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[3]));
            B5_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[4]));
            B6_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[5]));
            B7_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[6]));
            B8_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[7]));
            B9_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[8]));
            B10_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[9]));
            B11_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[10]));
            B12_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[11]));
            B13_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[12]));
            B14_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[13]));
            B15_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[14]));
            B16_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[15]));
            B17_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[16]));
            B18_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[17]));
            B19_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[18]));
            B20_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[19]));
            B21_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[20]));
            B22_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[21]));
            B23_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[22]));
            B24_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[23]));
            B25_U2setUpDown.Value = Convert.ToDecimal(Convert.ToInt32(settings[24]));

            reader.Close();
            reader.Dispose();
        }

        private void Form1_FormClosed_1(object sender, FormClosedEventArgs e)
        {
            /// сохранение текущих значений контролов
            /// 

            // write the settings file
            // Check if the file already exists in isolated storage.
            IsolatedStorageFile isoStore =
              IsolatedStorageFile.GetStore(IsolatedStorageScope.User
              | IsolatedStorageScope.Assembly, null, null);

            string[] fileNames = isoStore.GetFileNames(ISOLATED_FILE_NAME);

            foreach (string file in fileNames)
            {
                if (file == ISOLATED_FILE_NAME)
                {
                    isoStore.DeleteFile(ISOLATED_FILE_NAME);
                }
            }

            // Write some text into the file in isolated storage.
            IsolatedStorageFileStream oStream =
              new IsolatedStorageFileStream(ISOLATED_FILE_NAME,
              FileMode.Create, isoStore);

            StreamWriter writer = new StreamWriter(oStream);

            writer.WriteLine(B1_U2setUpDown.Value.ToString()); // B1 voltage ctrl value
            writer.WriteLine(B2_U2setUpDown.Value.ToString()); // B2 voltage ctrl value
            writer.WriteLine(B3_U2setUpDown.Value.ToString()); // B3 voltage ctrl value
            writer.WriteLine(B4_U2setUpDown.Value.ToString()); // B4 voltage ctrl value
            writer.WriteLine(B5_U2setUpDown.Value.ToString()); // B5 voltage ctrl value
            writer.WriteLine(B6_U2setUpDown.Value.ToString()); // B6 voltage ctrl value
            writer.WriteLine(B7_U2setUpDown.Value.ToString()); // B7 voltage ctrl value
            writer.WriteLine(B8_U2setUpDown.Value.ToString()); // B8 voltage ctrl value
            writer.WriteLine(B9_U2setUpDown.Value.ToString()); // B9 voltage ctrl value
            writer.WriteLine(B10_U2setUpDown.Value.ToString()); // B10 voltage ctrl value
            writer.WriteLine(B11_U2setUpDown.Value.ToString()); // B11 voltage ctrl value
            writer.WriteLine(B12_U2setUpDown.Value.ToString()); // B12 voltage ctrl value
            writer.WriteLine(B13_U2setUpDown.Value.ToString()); // B13 voltage ctrl value
            writer.WriteLine(B14_U2setUpDown.Value.ToString());
            writer.WriteLine(B15_U2setUpDown.Value.ToString());
            writer.WriteLine(B16_U2setUpDown.Value.ToString());
            writer.WriteLine(B17_U2setUpDown.Value.ToString());
            writer.WriteLine(B18_U2setUpDown.Value.ToString());
            writer.WriteLine(B19_U2setUpDown.Value.ToString());
            writer.WriteLine(B20_U2setUpDown.Value.ToString());
            writer.WriteLine(B21_U2setUpDown.Value.ToString());
            writer.WriteLine(B22_U2setUpDown.Value.ToString());
            writer.WriteLine(B23_U2setUpDown.Value.ToString());
            writer.WriteLine(B24_U2setUpDown.Value.ToString());
            writer.WriteLine(B25_U2setUpDown.Value.ToString());

            writer.Close();
        }
       
        private void B1_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B1_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[0].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B2_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B2_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[1].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B3_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B3_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[2].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B4_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B4_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[3].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B5_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B5_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[4].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B6_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B6_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[5].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B7_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B7_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[6].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B8_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B8_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[7].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B9_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B9_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[8].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B10_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B10_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[9].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B11_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B11_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[10].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B12_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B12_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[11].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B13_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B13_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[12].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B1_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[0].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B2_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[1].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B3_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[2].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B4_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[3].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B5_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[4].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B6_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[5].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B7_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[6].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B8_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[7].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B9_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[8].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B10_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[9].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B11_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[10].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B12_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[11].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B13_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[12].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B1_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[0].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B2_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[1].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B3_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[2].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B4_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[3].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B5_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[4].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B6_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[5].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B7_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[6].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B8_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[7].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B9_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[8].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B10_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[9].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B11_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[10].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B12_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[11].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B13_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[12].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void All_OutOn_B_Click(object sender, EventArgs e)
        {
            /// Вкл. выходы всех БУВов
            try 
            {
                for (int i = 0; i < NumberOfSources; i++)
                {
                    try 
                    {
                        IdAndOutState.Clear();
                        IdAndOutState.Add(Src[i].ID, "ON");
                        OnSrcChargeCtrl(this, IdAndOutState);
                        Thread.Sleep(50); 
                    }
                    catch (Exception) { return; }
                    
                }
            }
            catch (Exception) { return; }
        }

        private void All_OutOff_B_Click(object sender, EventArgs e)
        {
            /// Выкл. выходы всех БУВов
            try
            {
                for (int i = 0; i < NumberOfSources; i++)
                {
                    try
                    {
                        IdAndOutState.Clear();
                        IdAndOutState.Add(Src[i].ID, "OFF");
                        OnSrcChargeCtrl(this, IdAndOutState);
                        Thread.Sleep(50);
                    }
                    catch (Exception) { return; }
                }
            }
            catch (Exception) { return; }
        }

        private void B14_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B14_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[13].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B15_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B15_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[14].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B16_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B16_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[15].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B17_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B17_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[16].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B18_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B18_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[17].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B19_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B19_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[18].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B20_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B20_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[19].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B21_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B21_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[20].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B22_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B22_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[21].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B23_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B23_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[22].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B24_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B24_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[23].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B25_U2setB_Click(object sender, EventArgs e)
        {
            try /// Вызов события установки новых параметров
            {
                U2set = Convert.ToUInt16(B25_U2setUpDown.Value);
                IdAndV2set.Clear(); // очистка словаря с ID БУВа и параметром V
                IdAndV2set.Add(Src[24].ID, U2set.ToString()); // сохр. новго знач.
                OnSetVoltage(this, IdAndV2set); // инициирование события
            }
            catch (Exception) { return; }
        }

        private void B14_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[13].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B15_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[14].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B16_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[15].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B17_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[16].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B18_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[17].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B19_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[18].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B20_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[19].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B21_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[20].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B22_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[21].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B23_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[22].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B24_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[23].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B25_OutOn_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[24].ID, "ON");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B14_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[13].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B15_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[14].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B16_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[15].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B17_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[16].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B18_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[17].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B19_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[18].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B20_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[19].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B21_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[20].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B22_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[21].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B23_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[22].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B24_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[23].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }

        private void B25_OutOff_B_Click(object sender, EventArgs e)
        {
            IdAndOutState.Clear();
            IdAndOutState.Add(Src[24].ID, "OFF");
            try { OnSrcChargeCtrl(this, IdAndOutState); }
            catch (Exception) { return; }
        }


    }
}