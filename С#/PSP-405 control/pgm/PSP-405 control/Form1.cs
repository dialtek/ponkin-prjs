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

namespace PSP_405_control
{
    /// <summary>
    /// MAIN CLASS
    /// </summary>

    public partial class Form1 : Form
    {
        //---------------------------------  variables ----------------------------------------------------------------//

        private String VDK_FI_voltage, VDK_FI_current, VDK_FI_OutStatus, // переменные источника ВДК-ФИ
                       VDK_FI_I_limit, VDK_FI_V_limit, VDK_FI_OutState = "-";

        private String GDK_FI_voltage, GDK_FI_current, GDK_FI_OutStatus, // переменные источника ГДК-ФИ
                       GDK_FI_I_limit, GDK_FI_V_limit, GDK_FI_OutState = "-";

        private String VDK_1_voltage, VDK_1_current, VDK_1_OutStatus,    // переменные источника ВДК-1
                       VDK_1_I_limit, VDK_1_V_limit, VDK_1_OutState = "-";

        private String GDK_1_voltage, GDK_1_current, GDK_1_OutStatus,   // переменные источника ГДК-1
                       GDK_1_I_limit, GDK_1_V_limit, GDK_1_OutState = "-";

        private String VDK_6_voltage, VDK_6_current, VDK_6_OutStatus,   // переменные источника ВДК-6
                       VDK_6_I_limit, VDK_6_V_limit, VDK_6_OutState = "-";

        private String GDK_6_voltage, GDK_6_current, GDK_6_OutStatus,   // переменные источника ГДК-6
                       GDK_6_I_limit, GDK_6_V_limit, GDK_6_OutState = "-";

        private String SrcId, V2set, Voltage2set, V_limit, I_limit;
        private String[] FileRdDataLines;   // массив строк, прочитанных из конфигурационного файла

        private int SelectedSourceId;        // id выбранного источника для обращения
        // контейнер с ID и парам. для уст.
        private Dictionary<int, List<String>> IdAndData2set = new Dictionary<int, List<String>>();
        // контейнер с ошибками подключения источников 
        private Dictionary<String, bool> ConErrContainer = new Dictionary<String, bool>();
        // контейнер с ошибками вкл. источников 
        private Dictionary<String, bool> PowErrContainer = new Dictionary<String, bool>();
        // Лист загруженных параметров источников из файла
        private List<String> LoadedData = new List<string>();
        
       //-------------------------------------------------------------------------------------------------------------//
        
        // Создание публичных событий для передачи в др. класс
        public static event EventHandler<String> OnSrcOutputCtrl;   
        public static event EventHandler<Dictionary<int, List <String>>> OnSetParam;
        public static event EventHandler<Dictionary<int, List<String>>> OnSetFileСfg;

        private AsyncRdTimer VDK_FI_RwTimer = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ВДК-ФИ
        private AsyncRdTimer GDK_FI_RwTimer = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ГДК-ФИ
        private AsyncRdTimer VDK_1_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ВДК-1
        private AsyncRdTimer GDK_1_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ГДК-1
        private AsyncRdTimer VDK_6_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ВДК-6
        private AsyncRdTimer GDK_6_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ГДК-6

        //---------------------------------  Методы ------------------------------------------------------------------//
        private String Format (String mWord)
        {
            /// Форматируем слово - приводим к формату для преобразования в Double
            /// 0.50 -> 0.5 и тд

            if (mWord.StartsWith("0"))
                mWord = mWord.Substring(1);
            if (mWord.EndsWith("0"))
                mWord = mWord.Substring(0, mWord.Length - 1);
            mWord = mWord.Replace('.', ',');

            return mWord;
        }

        private string Format2Save(string V, string Ilim, string Vlim)
        {
            /// Формирование строки параметров источника для сохр. в файл
            string ConcatData;

            ConcatData = V + ":" + Ilim + ":" + Vlim + "\r\n";

            return ConcatData;
        }

        private string[] FormatFromSave(string SrcDataLine)
        {
            /// Формирование строки параметров источника для сохр. в файл
            /// 

            string[] DataParts = new string[3];
            // 08.00:1.50:09CRLF - формат сохранения строки параметров источника
            try
            {
                DataParts[0] = SrcDataLine.Substring(0, 5);    // Напряжение
                DataParts[1] = SrcDataLine.Substring(6, 4);    // Лимит тока
                DataParts[2] = SrcDataLine.Substring(11, 2);      // Лимит напряжения
            }
            catch (Exception ex)
            {

                Statusbox.Text = "Ошибка загрузки файла...";
            }
            return DataParts;
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
             
            return ("  " + CurrentTime + "\r\n" + CurrentDate);
        }

        //---------------------------------  События -----------------------------------------------------------------//

        public Form1()
        {
            InitializeComponent();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            VDK_FI_RwTimer.Interval = 200;
            VDK_FI_RwTimer.SrcId = 1;
            VDK_FI_RwTimer.IpAdress = "172.16.21.61";
            VDK_FI_RwTimer.Port = 4001;
            VDK_FI_RwTimer.Init();
            VDK_FI_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnVDK_FIdataRd);

            GDK_FI_RwTimer.Interval = 200;
            GDK_FI_RwTimer.SrcId = 2;
            GDK_FI_RwTimer.IpAdress = "172.16.21.62";
            GDK_FI_RwTimer.Port = 4001;
            GDK_FI_RwTimer.Init();
            GDK_FI_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnGDK_FIdataRd);

            VDK_1_RwTimer.Interval = 200;
            VDK_1_RwTimer.SrcId = 3;
            VDK_1_RwTimer.IpAdress = "172.16.21.63";
            VDK_1_RwTimer.Port = 4001;
            VDK_1_RwTimer.Init();
            VDK_1_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnVDK_1_dataRd);

            GDK_1_RwTimer.Interval = 200;
            GDK_1_RwTimer.SrcId = 4;
            GDK_1_RwTimer.IpAdress = "172.16.21.64";
            GDK_1_RwTimer.Port = 4001;
            GDK_1_RwTimer.Init();
            GDK_1_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnGDK_1_dataRd);

            VDK_6_RwTimer.Interval = 200;
            VDK_6_RwTimer.SrcId = 5;
            VDK_6_RwTimer.IpAdress = "172.16.21.65";
            VDK_6_RwTimer.Port = 4001;
            VDK_6_RwTimer.Init();
            VDK_6_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnVDK_6_dataRd);

            GDK_6_RwTimer.Interval = 200;
            GDK_6_RwTimer.SrcId = 6;
            GDK_6_RwTimer.IpAdress = "172.16.21.66";
            GDK_6_RwTimer.Port = 4001;
            GDK_6_RwTimer.Init();
            GDK_6_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnGDK_6_dataRd);

            VoltageUpDown.DecimalPlaces = 2;
            VoltageUpDown.Increment = 1M;
            VoltageUpDown.ForeColor = VoltageUpDown.BackColor;

            CurrentLimitUpDown.DecimalPlaces = 2;
            CurrentLimitUpDown.Increment = 0.01M;

            AllControlsGroupBox.Enabled = false;
            SaveCfg.Enabled = false;
            SetCfg.Enabled = false;
            VsetGroupBox.Visible = false; // скрываем управление напряжением, задается только лимит = ограничению

            VDK_FI_RwTimer.Start();
            GDK_FI_RwTimer.Start();
            VDK_1_RwTimer.Start();
            GDK_1_RwTimer.Start();
            VDK_6_RwTimer.Start();
            GDK_6_RwTimer.Start();
            DataUpdateTimer.Start();
        }

        void SrcReadTimer_OnGDK_FIdataRd(object sender, EventArgs e)
        {
            String[] _GDK_FI_Data;

            _GDK_FI_Data = GDK_FI_RwTimer.GetSrcData;

            GDK_FI_current = _GDK_FI_Data[0];
            GDK_FI_voltage = _GDK_FI_Data[1];
            GDK_FI_OutStatus = _GDK_FI_Data[2];
            GDK_FI_V_limit = _GDK_FI_Data[3];
            GDK_FI_I_limit = _GDK_FI_Data[4];
        }

        void SrcReadTimer_OnVDK_FIdataRd(object sender, EventArgs e)
        {
            /// Чтение U,I,Ilim,Vlim и Out Status ВДК-ФИ

            String[] _VDK_FI_Data;  // Массив строк для чтения показаний источника

            _VDK_FI_Data = VDK_FI_RwTimer.GetSrcData;  // читаем показания

            VDK_FI_current   = _VDK_FI_Data[0];        // показания I источника
            VDK_FI_voltage   = _VDK_FI_Data[1];        // показания U источника
            VDK_FI_OutStatus = _VDK_FI_Data[2];        // состояние выхода источника
            VDK_FI_V_limit   = _VDK_FI_Data[3];        // значение лимита U
            VDK_FI_I_limit   = _VDK_FI_Data[4];        // значение лимита I
        }

        void SrcReadTimer_OnVDK_1_dataRd(object sender, EventArgs e)
        {
            /// Чтение U,I,Ilim,Vlim и Out Status ВДК-1

            String[] _VDK_1_Data;  // Массив строк для чтения показаний источника

            _VDK_1_Data = VDK_1_RwTimer.GetSrcData;  // читаем показания

            VDK_1_current =   _VDK_1_Data[0];        // показания I источника
            VDK_1_voltage =   _VDK_1_Data[1];        // показания U источника
            VDK_1_OutStatus = _VDK_1_Data[2];        // состояние выхода источника
            VDK_1_V_limit =   _VDK_1_Data[3];        // значение лимита U
            VDK_1_I_limit =   _VDK_1_Data[4];        // значение лимита I
        }

        void SrcReadTimer_OnGDK_1_dataRd(object sender, EventArgs e)
        {
            /// Чтение U,I,Ilim,Vlim и Out Status ГДК-1

            String[] _GDK_1_Data;  // Массив строк для чтения показаний источника

            _GDK_1_Data = GDK_1_RwTimer.GetSrcData;  // читаем показания

            GDK_1_current   = _GDK_1_Data[0];        // показания I источника
            GDK_1_voltage   = _GDK_1_Data[1];        // показания U источника
            GDK_1_OutStatus = _GDK_1_Data[2];        // состояние выхода источника
            GDK_1_V_limit   = _GDK_1_Data[3];        // значение лимита U
            GDK_1_I_limit   = _GDK_1_Data[4];        // значение лимита I
        }

        void SrcReadTimer_OnVDK_6_dataRd(object sender, EventArgs e)
        {
            /// Чтение U,I,Ilim,Vlim и Out Status ВДК-6

            String[] _VDK_6_Data;  // Массив строк для чтения показаний источника

            _VDK_6_Data = VDK_6_RwTimer.GetSrcData;  // читаем показания

            VDK_6_current   = _VDK_6_Data[0];        // показания I источника
            VDK_6_voltage   = _VDK_6_Data[1];        // показания U источника
            VDK_6_OutStatus = _VDK_6_Data[2];        // состояние выхода источника
            VDK_6_V_limit   = _VDK_6_Data[3];        // значение лимита U
            VDK_6_I_limit   = _VDK_6_Data[4];        // значение лимита I
        }

        void SrcReadTimer_OnGDK_6_dataRd(object sender, EventArgs e)
        {
            /// Чтение U,I,Ilim,Vlim и Out Status ГДК-6

            String[] _GDK_6_Data;  // Массив строк для чтения показаний источника

            _GDK_6_Data = GDK_6_RwTimer.GetSrcData;  // читаем показания

            GDK_6_current   = _GDK_6_Data[0];        // показания I источника
            GDK_6_voltage   = _GDK_6_Data[1];        // показания U источника
            GDK_6_OutStatus = _GDK_6_Data[2];        // состояние выхода источника
            GDK_6_V_limit   = _GDK_6_Data[3];        // значение лимита U
            GDK_6_I_limit   = _GDK_6_Data[4];        // значение лимита I
        }

        public void VDK_FI_OutputB_Click(object sender, EventArgs e)
        {
            /// ВКЛ/ВЫКЛ нагрузки ВДК-ФИ
            /// 

            string ID = "1"; // ID источника ВДК-ФИ

            if (VDK_FI_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcOutputCtrl(this, ID + "ON"); // команда вкл. если сейчас выкл.
            else
             {
                 OnSrcOutputCtrl(this, ID + "OFF"); // команда выкл. если сейчас вкл. 
             } 
                
        }

        private void GDK_FI_OutputB_Click(object sender, EventArgs e)
        {
            string ID = "2"; // ID источника ГДК-ФИ

            if (GDK_FI_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcOutputCtrl(this, ID + "ON");
            else
            {
                OnSrcOutputCtrl(this, ID + "OFF");
            } 
        }

        public void VDK_1_OutputB_Click(object sender, EventArgs e)
        {
            /// ВКЛ/ВЫКЛ нагрузки ВДК-1
            /// 

            string ID = "3"; // ID источника ВДК-1

            if (VDK_1_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcOutputCtrl(this, ID + "ON"); // команда вкл. если сейчас выкл.
            else
            {
                OnSrcOutputCtrl(this, ID + "OFF"); // команда выкл. если сейчас вкл. 
            }

        }

        public void GDK_1_OutputB_Click(object sender, EventArgs e)
        {
            /// ВКЛ/ВЫКЛ нагрузки ГДК-ФИ
            /// 

            string ID = "4"; // ID источника ГДК-ФИ

            if (GDK_1_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcOutputCtrl(this, ID + "ON"); // команда вкл. если сейчас выкл.
            else
            {
                OnSrcOutputCtrl(this, ID + "OFF"); // команда выкл. если сейчас вкл. 
            }
        }

        public void VDK_6_OutputB_Click(object sender, EventArgs e)
        {
            /// ВКЛ/ВЫКЛ нагрузки ВДК-6
            /// 

            string ID = "5"; // ID источника ВДК-6

            if (VDK_6_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcOutputCtrl(this, ID + "ON"); // команда вкл. если сейчас выкл.
            else
            {
                OnSrcOutputCtrl(this, ID + "OFF"); // команда выкл. если сейчас вкл. 
            }
        }

        public void GDK_6_OutputB_Click(object sender, EventArgs e)
        {
            /// ВКЛ/ВЫКЛ нагрузки ГДК-6
            /// 

            string ID = "6"; // ID источника ГДК-6

            if (GDK_6_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcOutputCtrl(this, ID + "ON"); // команда вкл. если сейчас выкл.
            else
            {
                OnSrcOutputCtrl(this, ID + "OFF"); // команда выкл. если сейчас вкл. 
            }
        }

        private void DataUpdateTimer_Tick(object sender, EventArgs e)
        {
            /// Обновление показаний на форме, анализ ошибок
            /// 

            CurrTime.Text = GetTimeAndData();   // Выводим текущие время и дату
            ConErrContainer.Clear();            // Очищаем контейнеры ошибок перед -
            PowErrContainer.Clear();            // - новым добавлением элементов
            string ConErrMsg = null;            // ничего не пишем, если нет ошибок

            //---------------------------------  ВДК-ФИ ------------------------------------------------//
            VDK_FI_voltBox.Text = VDK_FI_voltage;
            VDK_FI_currBox.Text = VDK_FI_current;
            VDK_FI_OutputB.Text = VDK_FI_OutStatus;
            VDK_FI_OutputB.BackColor = (VDK_FI_OutStatus == "+") ? Color.LawnGreen : Color.Silver;

            if (VDK_FI_voltage == "*") PowErrContainer.Add("ВДК-ФИ", true);
            else PowErrContainer.Add("ВДК-ФИ", false);
            if (VDK_FI_voltage == "-") ConErrContainer.Add("ВДК-ФИ", true);
            else ConErrContainer.Add("ВДК-ФИ", false);
            //---------------------------------  ГДК-ФИ ------------------------------------------------//
            GDK_FI_voltBox.Text = GDK_FI_voltage;
            GDK_FI_currBox.Text = GDK_FI_current;
            GDK_FI_OutputB.Text = GDK_FI_OutStatus;
            GDK_FI_OutputB.BackColor = (GDK_FI_OutStatus == "+") ? Color.LawnGreen : Color.Silver;

            if (GDK_FI_voltage == "*") PowErrContainer.Add("ГДК-ФИ", true);
            else PowErrContainer.Add("ГДК-ФИ", false);
            if (GDK_FI_voltage == "-") ConErrContainer.Add("ГДК-ФИ", true);
            else ConErrContainer.Add("ГДК-ФИ", false);
            //---------------------------------  ВДК-1 ------------------------------------------------//
            VDK_1_voltBox.Text = VDK_1_voltage;
            VDK_1_currBox.Text = VDK_1_current;
            VDK_1_OutputB.Text = VDK_1_OutStatus;
            VDK_1_OutputB.BackColor = (VDK_1_OutStatus == "+") ? Color.LawnGreen : Color.Silver;

            if (VDK_1_voltage == "*") PowErrContainer.Add("ВДК-1", true);
            else PowErrContainer.Add("ВДК-1", false);
            if (VDK_1_voltage == "-") ConErrContainer.Add("ВДК-1", true);
            else ConErrContainer.Add("ВДК-1", false);
            //---------------------------------  ГДК-1 ------------------------------------------------//
            GDK_1_voltBox.Text = GDK_1_voltage;
            GDK_1_currBox.Text = GDK_1_current;
            GDK_1_OutputB.Text = GDK_1_OutStatus;
            GDK_1_OutputB.BackColor = (GDK_1_OutStatus == "+") ? Color.LawnGreen : Color.Silver;

            if (GDK_1_voltage == "*") PowErrContainer.Add("ГДК-1", true);
            else PowErrContainer.Add("ГДК-1", false);
            if (GDK_1_voltage == "-") ConErrContainer.Add("ГДК-1", true);
            else ConErrContainer.Add("ГДК-1", false);
            //---------------------------------  ВДК-6 ------------------------------------------------//
            VDK_6_voltBox.Text = VDK_6_voltage;
            VDK_6_currBox.Text = VDK_6_current;
            VDK_6_OutputB.Text = VDK_6_OutStatus;
            VDK_6_OutputB.BackColor = (VDK_6_OutStatus == "+") ? Color.LawnGreen : Color.Silver;

            if (VDK_6_voltage == "*") PowErrContainer.Add("ВДК-6", true);
            else PowErrContainer.Add("ВДК-6", false);
            if (VDK_6_voltage == "-") ConErrContainer.Add("ВДК-6", true);
            else ConErrContainer.Add("ВДК-6", false);
            //---------------------------------  ГДК-6 ------------------------------------------------//
            GDK_6_voltBox.Text = GDK_6_voltage;
            GDK_6_currBox.Text = GDK_6_current;
            GDK_6_OutputB.Text = GDK_6_OutStatus;
            GDK_6_OutputB.BackColor = (GDK_6_OutStatus == "+") ? Color.LawnGreen : Color.Silver;

            if (GDK_6_voltage == "*") PowErrContainer.Add("ГДК-6", true);
            else PowErrContainer.Add("ГДК-6", false);
            if (GDK_6_voltage == "-") ConErrContainer.Add("ГДК-6", true);
            else ConErrContainer.Add("ГДК-6", false);

            // проверка наличия ошибок подключения
            if (ConErrContainer.Values.Contains(true))
            {
                ConErrMsg = "Проверьте подключение источников:\r\n";

                foreach( KeyValuePair<String, bool> element in ConErrContainer)
                {
                    if (element.Value == true) ConErrMsg += element.Key + " "; 
                }
            }

            // проверка наличия ошибок питания
            if (PowErrContainer.Values.Contains(true))
            {
                ConErrMsg = "Проверьте питание источников:\r\n";

                foreach (KeyValuePair<String, bool> element in PowErrContainer)
                {
                    if (element.Value == true) ConErrMsg += element.Key + " ";
                }
            }

            Statusbox.Text = ConErrMsg; // выводим сообщения об ошибках
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            /// Сброс значений тока и напряжения для установки
            /// 
            //VoltageUpDown.ForeColor = VoltageUpDown.BackColor;
            //Current2set.Text = null;
            //SourceId.Text = null;
            //Output_On.Enabled = false;
            //Output_off.Enabled = false;

        }
        
        private void LoadCfg_Click(object sender, EventArgs e)
        {
            /// загрузка конфигурации из файла
            ///  

            //VDK_FI_RwTimer.Stop();
            //GDK_FI_RwTimer.Stop();
            DataUpdateTimer.Stop();

            // нужен делегат, запускать в отдельном потоке...
            OpenFileDialog open = new OpenFileDialog();
            open.Title  = "Укажите файл конфигурации...";
            open.Filter = "Файл конфигурации | *.dat";
            String RdDataLines = "";

            if (open.ShowDialog() == DialogResult.OK) 
            {
                StreamReader read = new StreamReader(File.OpenRead(open.FileName));
                RdDataLines = read.ReadToEnd(); // считываем весь файл (целиком)
                // отделяем конфигурации отдельных источников
                FileRdDataLines = RdDataLines.Split(new string[] { "\r\n" }, StringSplitOptions.None);

                // загрузка из файла параметров источника ВДК-ФИ
                LoadedData.Add(FormatFromSave(FileRdDataLines[0])[0]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[0])[1]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[0])[2]);
                VDK_FI_voltBox.Text = VDK_FI_voltage;
                VDK_FI_currBox.Text = "";
                // загрузка из файла параметров источника ГДК-ФИ
                LoadedData.Add(FormatFromSave(FileRdDataLines[1])[0]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[1])[1]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[1])[2]);
                GDK_FI_voltBox.Text = GDK_FI_voltage;
                GDK_FI_currBox.Text = "";
                // загрузка из файла параметров источника ВДК-1
                LoadedData.Add(FormatFromSave(FileRdDataLines[2])[0]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[2])[1]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[2])[2]);
                VDK_1_voltBox.Text = VDK_1_voltage;
                VDK_1_currBox.Text = "";
                // загрузка из файла параметров источника ГДК-1
                LoadedData.Add(FormatFromSave(FileRdDataLines[3])[0]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[3])[1]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[3])[2]);
                GDK_1_voltBox.Text = VDK_1_voltage;
                GDK_1_currBox.Text = "";
                // загрузка из файла параметров источника ВДК-6
                LoadedData.Add(FormatFromSave(FileRdDataLines[4])[0]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[4])[1]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[4])[2]);
                VDK_6_voltBox.Text = VDK_6_voltage;
                VDK_6_currBox.Text = "";
                // загрузка из файла параметров источника ГДК-6
                LoadedData.Add(FormatFromSave(FileRdDataLines[5])[0]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[5])[1]);
                LoadedData.Add(FormatFromSave(FileRdDataLines[5])[2]);
                GDK_6_voltBox.Text = GDK_6_voltage;
                GDK_6_currBox.Text = "";

                read.Dispose(); // закрываем стримридер
                SetCfg.Enabled  = true;
            }
         }

        private void SaveCfg_Click(object sender, EventArgs e)
        {
            /// Сохранение текущей конфигурациии в файл
            ///

            SaveFileDialog save = new SaveFileDialog();
            StringBuilder Data2Save = new StringBuilder();
            String sVDK_FI_data;
            String sGDK_FI_data;
            String sVDK_1_data;
            String sGDK_1_data;
            String sVDK_6_data;
            String sGDK_6_data;

            save.Title = "Сохранение конфигурационного файла...";
            save.Filter = "Файл конфигурации | *.dat";

            if (save.ShowDialog() == DialogResult.OK)
            {
                TextWriter tw = new StreamWriter(File.Create(save.FileName));
                // сохранение параметров источников в переменные
                sVDK_FI_data = Format2Save(VDK_FI_voltage, VDK_FI_I_limit, VDK_FI_V_limit);
                sGDK_FI_data = Format2Save(GDK_FI_voltage, GDK_FI_I_limit, GDK_FI_V_limit);
                sVDK_1_data  = Format2Save(VDK_1_voltage, VDK_1_I_limit, VDK_1_V_limit);
                sGDK_1_data  = Format2Save(GDK_1_voltage, GDK_1_I_limit, GDK_1_V_limit);
                sVDK_6_data  = Format2Save(VDK_6_voltage, VDK_6_I_limit, VDK_6_V_limit);
                sGDK_6_data  = Format2Save(GDK_6_voltage, GDK_6_I_limit, GDK_6_V_limit);
                // конкатинация строк - параметров источников
                Data2Save.Append(sVDK_FI_data);
                Data2Save.Append(sGDK_FI_data);
                Data2Save.Append(sVDK_1_data);
                Data2Save.Append(sGDK_1_data);
                Data2Save.Append(sVDK_6_data);
                Data2Save.Append(sGDK_6_data);
                // запись в файл
                tw.Write(Data2Save);
                tw.Close(); // закрытие файла          
            }         
        }
        
        private void SetCfg_Click(object sender, EventArgs e)
        {
            /// Применить загруженную конфигурацию
            ///
            List<String> AllData2set = new List<string>();

            IdAndData2set.Clear();

            AllData2set.Add(LoadedData[0]);
            AllData2set.Add(LoadedData[1]);
            AllData2set.Add(LoadedData[2]);

            IdAndData2set.Add(1, AllData2set);
            OnSetFileСfg(this, IdAndData2set);

            IdAndData2set.Clear();
            AllData2set.Clear();

            AllData2set.Add(LoadedData[3]);
            AllData2set.Add(LoadedData[4]);
            AllData2set.Add(LoadedData[5]);

            IdAndData2set.Add(2, AllData2set);
            OnSetFileСfg(this, IdAndData2set);

            IdAndData2set.Clear();
            AllData2set.Clear();

            AllData2set.Add(LoadedData[6]);
            AllData2set.Add(LoadedData[7]);
            AllData2set.Add(LoadedData[8]);

            IdAndData2set.Add(3, AllData2set);
            OnSetFileСfg(this, IdAndData2set);

            IdAndData2set.Clear();
            AllData2set.Clear();

            AllData2set.Add(LoadedData[9]);
            AllData2set.Add(LoadedData[10]);
            AllData2set.Add(LoadedData[11]);

            IdAndData2set.Add(4, AllData2set);
            OnSetFileСfg(this, IdAndData2set);

            AllData2set.Add(LoadedData[12]);
            AllData2set.Add(LoadedData[13]);
            AllData2set.Add(LoadedData[14]);

            IdAndData2set.Add(5, AllData2set);
            OnSetFileСfg(this, IdAndData2set);

            AllData2set.Add(LoadedData[15]);
            AllData2set.Add(LoadedData[16]);
            AllData2set.Add(LoadedData[17]);

            IdAndData2set.Add(6, AllData2set);
            OnSetFileСfg(this, IdAndData2set);

            DataUpdateTimer.Start();

        }
          
        private void S1_name_MouseEnter(object sender, EventArgs e)
        {
            /// Изменение цвета при наведении курсора мыши

            S1_name.ForeColor = Color.Blue;
        }

        private void S1_name_MouseLeave(object sender, EventArgs e)
        {
            /// Изменение цвета при уходе курсора мыши

            S1_name.ForeColor = Color.DimGray;
        }

        private void S2_name_MouseEnter(object sender, EventArgs e)
        {
            /// Изменение цвета при наведении курсора мыши

            S2_name.ForeColor = Color.Blue;
        }

        private void S2_name_MouseLeave(object sender, EventArgs e)
        {
            /// Изменение цвета при уходе курсора мыши

            S2_name.ForeColor = Color.DimGray;
        }

        private void S3_name_MouseEnter(object sender, EventArgs e)
        {
            /// Изменение цвета при наведении курсора мыши

            S3_name.ForeColor = Color.Blue;
        }

        private void S3_name_MouseLeave(object sender, EventArgs e)
        {
            /// Изменение цвета при уходе курсора мыши

            S3_name.ForeColor = Color.DimGray;
        }

        private void S4_name_MouseEnter(object sender, EventArgs e)
        {
            /// Изменение цвета при наведении курсора мыши

            S4_name.ForeColor = Color.Blue;
        }

        private void S4_name_MouseLeave(object sender, EventArgs e)
        {
            /// Изменение цвета при уходе курсора мыши

            S4_name.ForeColor = Color.DimGray;
        }

        private void S5_name_MouseEnter(object sender, EventArgs e)
        {
            /// Изменение цвета при наведении курсора мыши

            S5_name.ForeColor = Color.Blue;
        }

        private void S5_name_MouseLeave(object sender, EventArgs e)
        {
            /// Изменение цвета при уходе курсора мыши

            S5_name.ForeColor = Color.DimGray;
        }

        private void S6_name_MouseEnter(object sender, EventArgs e)
        {
            /// Изменение цвета при наведении курсора мыши

            S6_name.ForeColor = Color.Blue;
        }

        private void S6_name_MouseLeave(object sender, EventArgs e)
        {
            /// Изменение цвета при уходе курсора мыши

            S6_name.ForeColor = Color.DimGray;
        }

        private void S1_name_Click(object sender, EventArgs e)
        {
            /// обработка клика по на ВДК-ФИ

            AllControlsGroupBox.Enabled = true; // вкл. видимость элементов управления источником при выборе
            SaveCfg.Enabled = true;             // вкл. видимость кнопки Сохранить конфигурацию

            S1_name.Font = new Font(S1_name.Font, FontStyle.Bold);  // жирный шрифт, видимость клика
            VoltageUpDown.ForeColor = Color.Black;                  // показываем числа
            this.Refresh();     // обновляем форму                                 
            Thread.Sleep(50);   // даем пользователю увидеть
            S1_name.Font = new Font(S1_name.Font, FontStyle.Regular | FontStyle.Underline); // возвращ. старые парам.

            SelectedSourceId = 1;           // сохраняем id текущего источника
            SourceId.Text = S1_name.Text;   // показываем имя текущего источника
            try
            {
                Voltage2set = VDK_FI_voltBox.Text;  // выводим напряжение
            }
            catch (Exception)
            { return; }

            try
            {
                VoltageUpDown.Value      = (Decimal)Convert.ToDouble(Format(Voltage2set));
                VoltageLimitUpDown.Value = (Decimal)Convert.ToInt16(VDK_FI_V_limit);
                CurrentLimitUpDown.Value = (Decimal)Convert.ToDouble(Format(VDK_FI_I_limit));
            }
            catch (Exception) { return; }
        }

        private void S2_name_Click(object sender, EventArgs e)
        {
            /// обработка клика по ГДК-ФИ
            ///

            AllControlsGroupBox.Enabled = true; // вкл. видимость элементов управления источником при выборе
            SaveCfg.Enabled = true;             // вкл. видимость кнопки Сохранить конфигурацию

            S2_name.Font = new Font(S2_name.Font, FontStyle.Bold);  // жирный шрифт, видимость клика
            VoltageUpDown.ForeColor = Color.Black;                  // показываем числа
            this.Refresh();     // обновляем форму                                 
            Thread.Sleep(50);   // даем пользователю увидеть
            S2_name.Font = new Font(S2_name.Font, FontStyle.Regular | FontStyle.Underline); // возвращ. старые парам.

            SelectedSourceId = 2;           // сохраняем id текущего источника
            SourceId.Text = S2_name.Text;   // показываем имя текущего источника
            try
            {
                Voltage2set = GDK_FI_voltBox.Text;  // выводим напряжение
            }
            catch (Exception)
            { return; }

            try
            {
                VoltageUpDown.Value = (Decimal)Convert.ToDouble(Format(Voltage2set));
                VoltageLimitUpDown.Value = (Decimal)Convert.ToInt16(GDK_FI_V_limit);
                CurrentLimitUpDown.Value = (Decimal)Convert.ToDouble(Format(GDK_FI_I_limit));
            }
            catch (Exception) { return; }
        }

        private void S3_name_Click(object sender, EventArgs e)
        {
            /// обработка клика по ВДК-1
            ///

            AllControlsGroupBox.Enabled = true; // вкл. видимость элементов управления источником при выборе
            SaveCfg.Enabled = true;             // вкл. видимость кнопки Сохранить конфигурацию

            S3_name.Font = new Font(S3_name.Font, FontStyle.Bold);  // жирный шрифт, видимость клика
            VoltageUpDown.ForeColor = Color.Black;                  // показываем числа
            this.Refresh();     // обновляем форму                                 
            Thread.Sleep(50);   // даем пользователю увидеть
            S3_name.Font = new Font(S3_name.Font, FontStyle.Regular | FontStyle.Underline); // возвращ. старые парам.

            SelectedSourceId = 3;           // сохраняем id текущего источника
            SourceId.Text = S3_name.Text;   // показываем имя текущего источника
            try
            {
                Voltage2set = VDK_1_voltBox.Text;  // выводим напряжение
            }
            catch (Exception)
            { return; }

            try
            {
                VoltageUpDown.Value = (Decimal)Convert.ToDouble(Format(Voltage2set));
                VoltageLimitUpDown.Value = (Decimal)Convert.ToInt16(VDK_1_V_limit);
                CurrentLimitUpDown.Value = (Decimal)Convert.ToDouble(Format(VDK_1_I_limit));
            }
            catch (Exception) { return; }
        }

        private void S4_name_Click(object sender, EventArgs e)
        {
            /// обработка клика по ГДК-1
            ///

            AllControlsGroupBox.Enabled = true; // вкл. видимость элементов управления источником при выборе
            SaveCfg.Enabled = true;             // вкл. видимость кнопки Сохранить конфигурацию

            S4_name.Font = new Font(S4_name.Font, FontStyle.Bold);  // жирный шрифт, видимость клика
            VoltageUpDown.ForeColor = Color.Black;                  // показываем числа
            this.Refresh();     // обновляем форму                                 
            Thread.Sleep(50);   // даем пользователю увидеть
            S4_name.Font = new Font(S4_name.Font, FontStyle.Regular | FontStyle.Underline); // возвращ. старые парам.

            SelectedSourceId = 4;           // сохраняем id текущего источника
            SourceId.Text = S4_name.Text;   // показываем имя текущего источника
            try
            {
                Voltage2set = GDK_1_voltBox.Text;  // выводим напряжение
            }
            catch (Exception)
            { return; }

            try
            {
                VoltageUpDown.Value = (Decimal)Convert.ToDouble(Format(Voltage2set));
                VoltageLimitUpDown.Value = (Decimal)Convert.ToInt16(GDK_1_V_limit);
                CurrentLimitUpDown.Value = (Decimal)Convert.ToDouble(Format(GDK_1_I_limit));
            }
            catch (Exception) { return; }
        }

        private void S5_name_Click(object sender, EventArgs e)
        {
            /// обработка клика по ВДК-6
            ///

            AllControlsGroupBox.Enabled = true; // вкл. видимость элементов управления источником при выборе
            SaveCfg.Enabled = true;             // вкл. видимость кнопки Сохранить конфигурацию

            S5_name.Font = new Font(S5_name.Font, FontStyle.Bold);  // жирный шрифт, видимость клика
            VoltageUpDown.ForeColor = Color.Black;                  // показываем числа
            this.Refresh();     // обновляем форму                                 
            Thread.Sleep(50);   // даем пользователю увидеть
            S5_name.Font = new Font(S5_name.Font, FontStyle.Regular | FontStyle.Underline); // возвращ. старые парам.

            SelectedSourceId = 5;           // сохраняем id текущего источника
            SourceId.Text = S5_name.Text;   // показываем имя текущего источника
            try
            {
                Voltage2set = VDK_6_voltBox.Text;  // выводим напряжение
            }
            catch (Exception)
            { return; }

            try
            {
                VoltageUpDown.Value = (Decimal)Convert.ToDouble(Format(Voltage2set));
                VoltageLimitUpDown.Value = (Decimal)Convert.ToInt16(VDK_6_V_limit);
                CurrentLimitUpDown.Value = (Decimal)Convert.ToDouble(Format(VDK_6_I_limit));
            }
            catch (Exception) { return; }
        }

        private void S6_name_Click(object sender, EventArgs e)
        {
            /// обработка клика по ГДК-6
            ///

            AllControlsGroupBox.Enabled = true; // вкл. видимость элементов управления источником при выборе
            SaveCfg.Enabled = true;             // вкл. видимость кнопки Сохранить конфигурацию

            S6_name.Font = new Font(S6_name.Font, FontStyle.Bold);  // жирный шрифт, видимость клика
            VoltageUpDown.ForeColor = Color.Black;                  // показываем числа
            this.Refresh();     // обновляем форму                                 
            Thread.Sleep(50);   // даем пользователю увидеть
            S6_name.Font = new Font(S6_name.Font, FontStyle.Regular | FontStyle.Underline); // возвращ. старые парам.

            SelectedSourceId = 6;           // сохраняем id текущего источника
            SourceId.Text = S6_name.Text;   // показываем имя текущего источника
            try
            {
                Voltage2set = GDK_6_voltBox.Text;  // выводим напряжение
            }
            catch (Exception)
            { return; }

            try
            {
                VoltageUpDown.Value = (Decimal)Convert.ToDouble(Format(Voltage2set));
                VoltageLimitUpDown.Value = (Decimal)Convert.ToInt16(GDK_6_V_limit);
                CurrentLimitUpDown.Value = (Decimal)Convert.ToDouble(Format(GDK_6_I_limit));
            }
            catch (Exception) { return; }
        }

        private void CurrentLimitUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка лимита по току для выбранного источника 
            /// 
            SrcId = SourceId.Text;

            I_limit = Convert.ToString(CurrentLimitUpDown.Value);
            I_limit = I_limit.Replace(',', '.');
            //IdAndData2set.Add(SelectedSourceId, I_limit);
            //OnSetCurrentLimit(this, IdAndData2set);

        }

        private void VoltageLimitUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка лимита по напряжению для выбранного источника
            /// 

            SrcId = SourceId.Text;

            V_limit = Convert.ToString(VoltageLimitUpDown.Value);
            V2set = V_limit; 
            //VoltageUpDown.Maximum = VoltageLimitUpDown.Value; 

            //IdAndData2set.Add(SelectedSourceId, V_limit);
            //OnSetVoltageLimit(this, IdAndData2set);

         }

        private void VoltageUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка заданного напряжения для выбранного источника
            /// 

            SrcId = SourceId.Text;

            V2set = Convert.ToString(VoltageUpDown.Value);
            V2set = V2set.Replace(',', '.');
                //if (!SetCfg_flag)
                //{
            //OnSetVoltage(this, IdAndData2set);
                //}   
        }

        private void SetParameters_Click(object sender, EventArgs e)
        {
            /// Вызов события установки новых параметров выбранного источника

            List<String> Data2set = new List<string>();
            
            IdAndData2set.Clear();
            //V2set = V_limit;        // Лимит и текущ. значения равны по ТЗ 
            Data2set.Add(V2set);
            Data2set.Add(I_limit);
            Data2set.Add(V_limit);

            IdAndData2set.Add(SelectedSourceId, Data2set);

            OnSetParam(this, IdAndData2set);
        }

        private void GDK_6_currBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void VDK_6_currBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void GDK_1_currBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void VDK_1_currBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void GDK_FI_currBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void VDK_FI_currBox_TextChanged(object sender, EventArgs e)
        {

        }

     }
 }
