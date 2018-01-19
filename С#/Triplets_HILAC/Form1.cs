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

namespace _701C_src_PGM
{

    /// <summary>
    /// MAIN CLASS
    /// </summary> 
    public partial class Form1 : Form
    {

        private NetworkStream ns;
        private StreamReader sr;
        private Socket server;

        private byte[] CmdBuf = new byte[10];

        // контейнер с ID и парам. для уст.
        private Dictionary<int, string> IdAndV2set = new Dictionary<int, string>();

        UInt16 U2setInDEC_full = 0;
        private string L1_SetVСmdStatus = "";
        private string L2_SetVСmdStatus = "";
        private string L3_SetVСmdStatus = "";

        // массив элементов ListViewItem для динамического заполнения таблицы данными об источниках питания 
        public static ListViewItem[] Src_data = new ListViewItem[50];
        private AsyncRdTimer[] Src = new AsyncRdTimer[50]; // Инстанциирование класса асинхр. работы с ист.1
        private string[] SrcReadVoltage = new string[50];
        private string[] SrcSetVoltage = new string[50];
        private string[] SrcStatusByte = new string[50];

        public static int NumberOfSources = 4;  // переменная количества источников
        public static int SelSourceNumber = -1; // переменная количества источников

        public static List<string> IPadrList = new List<string>(); // лист для хранения всех IP адресов источников
        public static List<string> PortList = new List<string>(); // лист для хранения всех портов источников
        public static List<string> SrcNames = new List<string>();  // лист для хранения всех имен источников

        string L_hexValue = "";
        //-------------------------------------------------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        //public static event EventHandler<String> OnSrcOutputCtrl;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetParam;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetFileСfg;

        //---------------------------------  Методы ------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        public static event EventHandler<Dictionary<int, String>> OnSetVoltage;
        public static event EventHandler<String> OnSrcChargeCtrl;

        // Specify a name for your top-level folder.
        //string path = @"c:\Лог Т1 RFQ";
        const string ISOLATED_FILE_NAME = "HILAC_triplets_cfq.txt";


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

            Src[0] = new AsyncRdTimer();
            Src[0].Interval = 300;
            Src[0].IpAdress = "172.16.21.142";
            Src[0].Port = 4001;
            Src[0].ID = 0;
            Src[0].Init();
            Src[0].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[0].Start();

            Src[1] = new AsyncRdTimer();
            Src[1].Interval = 300;
            Src[1].IpAdress = "172.16.21.143";
            Src[1].Port = 4001;
            Src[1].ID = 1;
            Src[1].Init();
            Src[1].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[1].Start();

            Src[2] = new AsyncRdTimer();
            Src[2].Interval = 300;
            Src[2].IpAdress = "172.16.21.144";
            Src[2].Port = 4001;
            Src[2].ID = 2;
            Src[2].Init();
            Src[2].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[2].Start();


            Src[3] = new AsyncRdTimer();
            Src[3].Interval = 300;
            Src[3].IpAdress = "172.16.21.145";
            Src[3].Port = 4001;
            Src[3].ID = 3;
            Src[3].Init();
            Src[3].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[3].Start();

            PGM_IP.Text = "QT1.1-1.3  " + Src[0].IpAdress + "    " + "QT1.2  " + Src[1].IpAdress + "    " +
                          "QT2.1-2.3  " + Src[2].IpAdress + "    " + "QT2.2  " + Src[3].IpAdress;
            NumberOfSources = 4;

            AddNewSource_B.Enabled = false;

            try
            {   // загрузка последней конфигурации
                LoadSettings();
            }
            catch (Exception)
            {   // если не нашелся файл конфигурации
                //return;
            }

            Update_timer.Start();

        }

        void OnSrcRdComplete(object sender, EventArgs e)
        {
            /// Чтение 

            string[] SRC_data = new string[5];  // Массив строк для чтения показаний источника

            for (int i = 0; i < NumberOfSources; i++)
            {
                SRC_data = Src[i].GetSrcData;   // читаем показания
                SrcReadVoltage[i] = SRC_data[1];// сохраняем U
                SrcStatusByte[i] = SRC_data[4];

                //if ((SRC_data[3] == "1") && (i < 1))
                //{
                //    L1_SetVСmdStatus = SRC_data[2]; // L1
                //    //MessageBox.Show("");
                //}
                //if ((SRC_data[3] == "1") && (i > 1))
                //{
                //    L2_SetVСmdStatus = SRC_data[2]; // L2
                //}
                //else { L1_SetVСmdStatus = "NoCmd"; L2_SetVСmdStatus = "NoCmd"; }
            }
        }

        private void U2setB_Click(object sender, EventArgs e)
        {
            /// Вызов события установки новых параметров источника L1
            /// 
            try
            {
                U2setInDEC_full = Convert.ToUInt16(D11_U2setUpDown.Value);
                L_hexValue = U2setInDEC_full.ToString("X4");
                IdAndV2set.Clear();

                IdAndV2set.Add(0, L_hexValue);
                OnSetVoltage(this, IdAndV2set);
            }
            catch (Exception) { return; }
        }

        private void Update_timer_Tick(object sender, EventArgs e)
        {
            try
            {
                D11_Uread.Text = SrcReadVoltage[0];
                if (D11_Uread.Text == "-")
                {   // если источник не отвечает...
                    D11_ChargeOn_B.Enabled = false;
                    D11_ChargeOff_B.Enabled = false;
                    D11_OutState.BackColor = Color.LightGray;
                    D11_Loc_status_lb.Text = "NC";
                    D11_Loc_status_lb.BackColor = Color.LightGray;
                }


                D12_Uread.Text = SrcReadVoltage[1];
                if (D12_Uread.Text == "-")
                {   // если источник не отвечает...
                    D12_ChargeOn_B.Enabled = false;
                    D12_ChargeOff_B.Enabled = false;
                    D12_OutState.BackColor = Color.LightGray;
                    D12_Loc_status_lb.Text = "NC";
                    D12_Loc_status_lb.BackColor = Color.LightGray;
                }

                D21_Uread.Text = SrcReadVoltage[2];
                if (D21_Uread.Text == "-")
                {   // если источник не отвечает...
                    D21_ChargeOn_B.Enabled = false;
                    D21_ChargeOff_B.Enabled = false;
                    D21_OutState.BackColor = Color.LightGray;
                    D21_Loc_status_lb.Text = "NC";
                    D21_Loc_status_lb.BackColor = Color.LightGray;
                }

                D22_Uread.Text = SrcReadVoltage[3];
                if (D22_Uread.Text == "-")
                {   // если источник не отвечает...
                    D22_ChargeOn_B.Enabled = false;
                    D22_ChargeOff_B.Enabled = false;
                    D22_OutState.BackColor = Color.LightGray;
                    D22_Loc_status_lb.Text = "NC";
                    D22_Loc_status_lb.BackColor = Color.LightGray;
                }





                /*
                                if (L1_SetVСmdStatus != "NoCmd")
                                {
                                    switch (L1_SetVСmdStatus)
                                    {
                                        case "-1": StatusBox.Text = "Ошибка соединения с источником Q1"; break;
                                        case "1": StatusBox.Text = "U = " + L1_U2setUpDown.Value.ToString() + " В на Q1 установлено успешно"; break;
                                        case "0": StatusBox.Text = "Ошибка установки напряжения на источнике Q1"; break;
                                    }

                                }
                                if (L2_SetVСmdStatus != "NoCmd")
                                {
                                    switch (L2_SetVСmdStatus)
                                    {
                                        case "-1": StatusBox.Text = "Ошибка соединения с источником Q2"; break;
                                        case "1": StatusBox.Text = "U = " + L2_U2setUpDown.Value.ToString() + " В на Q2 установлено успешно"; break;
                                        case "0": StatusBox.Text = "Ошибка установки напряжения на источнике Q2"; break;
                                    }

                                }
                                if (L3_SetVСmdStatus != "NoCmd")
                                {
                                    switch (L3_SetVСmdStatus)
                                    {
                                        case "-1": StatusBox.Text = "Ошибка соединения с источником Q3"; break;
                                        case "1": StatusBox.Text = "U = " + L3_U2setUpDown.Value.ToString() + " В на Q3 установлено успешно"; break;
                                        case "0": StatusBox.Text = "Ошибка установки напряжения на источнике Q3"; break;
                                    }

                                }
                */


                // обработка байтов ошибок и информации
                if (SrcStatusByte[0].Length == 17)
                {
                    if (SrcStatusByte[0][6] == '1')
                    {
                        D11_ChargeOn_B.Enabled = false;
                        D11_ChargeOff_B.Enabled = true;
                        D11_OutState.BackColor = Color.LimeGreen;
                    }
                    else
                    {
                        D11_ChargeOn_B.Enabled = true;
                        D11_ChargeOff_B.Enabled = false;
                        D11_OutState.BackColor = Color.White;
                    }

                    if (SrcStatusByte[0][10] == '1')
                    {
                        D11_Loc_status_lb.Text = "interlock error";
                        D11_Loc_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D11_Loc_status_lb.Text = "interlock Ok";
                        D11_Loc_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[0][13] == '1')
                    {
                        D11_Load_status_lb.Text = "load break";
                        D11_Load_status_lb.BackColor = Color.Red;
                    }
                    else if (SrcStatusByte[0][14] == '1')
                    {
                        D11_Load_status_lb.Text = "short circuit";
                        D11_Load_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D11_Load_status_lb.Text = "";
                        D11_Load_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[0][16] == '1')
                    {
                        D11_OverHeat_lb.Text = "ПЕРЕГРЕВ!";
                        D11_OverHeat_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D11_OverHeat_lb.Text = "";
                        D11_OverHeat_lb.BackColor = Color.LimeGreen;
                    }
                }

                //-- D12

                if (SrcStatusByte[1].Length == 17)
                {
                    if (SrcStatusByte[1][6] == '1')
                    {
                        D12_ChargeOn_B.Enabled = false;
                        D12_ChargeOff_B.Enabled = true;
                        D12_OutState.BackColor = Color.LimeGreen;
                    }
                    else
                    {
                        D12_ChargeOn_B.Enabled = true;
                        D12_ChargeOff_B.Enabled = false;
                        D12_OutState.BackColor = Color.White;
                    }

                    if (SrcStatusByte[1][10] == '1')
                    {
                        D12_Loc_status_lb.Text = "interlock error";
                        D12_Loc_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D12_Loc_status_lb.Text = "interlock Ok";
                        D12_Loc_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[1][13] == '1')
                    {
                        D12_Load_status_lb.Text = "load break";
                        D12_Load_status_lb.BackColor = Color.Red;
                    }
                    else if (SrcStatusByte[1][14] == '1')
                    {
                        D12_Load_status_lb.Text = "short circuit";
                        D12_Load_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D12_Load_status_lb.Text = "";
                        D12_Load_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[1][16] == '1')
                    {
                        D12_OverHeat_lb.Text = "overheat";
                        D12_OverHeat_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D12_OverHeat_lb.Text = "";
                        D12_OverHeat_lb.BackColor = Color.LimeGreen;
                    }
                }

                //-- D21

                if (SrcStatusByte[2].Length == 17)
                {
                    if (SrcStatusByte[2][6] == '1')
                    {
                        D21_ChargeOn_B.Enabled = false;
                        D21_ChargeOff_B.Enabled = true;
                        D21_OutState.BackColor = Color.LimeGreen;
                    }
                    else
                    {
                        D21_ChargeOn_B.Enabled = true;
                        D21_ChargeOff_B.Enabled = false;
                        D21_OutState.BackColor = Color.White;
                    }

                    if (SrcStatusByte[2][10] == '1')
                    {
                        D21_Loc_status_lb.Text = "interlock error";
                        D21_Loc_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D21_Loc_status_lb.Text = "interlock Ok";
                        D21_Loc_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[2][13] == '1')
                    {
                        D21_Load_status_lb.Text = "load break";
                        D21_Load_status_lb.BackColor = Color.Red;
                    }
                    else if (SrcStatusByte[2][14] == '1')
                    {
                        D21_Load_status_lb.Text = "short circuit";
                        D21_Load_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D21_Load_status_lb.Text = "";
                        D21_Load_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[2][16] == '1')
                    {
                        D21_OverHeat_lb.Text = "overheat";
                        D21_OverHeat_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D21_OverHeat_lb.Text = "";
                        D21_OverHeat_lb.BackColor = Color.LimeGreen;
                    }
                }

                //-- D22

                if (SrcStatusByte[3].Length == 17)
                {
                    if (SrcStatusByte[3][6] == '1')
                    {
                        D22_ChargeOn_B.Enabled = false;
                        D22_ChargeOff_B.Enabled = true;
                        D22_OutState.BackColor = Color.LimeGreen;
                    }
                    else
                    {
                        D22_ChargeOn_B.Enabled = true;
                        D22_ChargeOff_B.Enabled = false;
                        D22_OutState.BackColor = Color.White;
                    }

                    if (SrcStatusByte[3][10] == '1')
                    {
                        D22_Loc_status_lb.Text = "interlock error";
                        D22_Loc_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D22_Loc_status_lb.Text = "interlock Ok";
                        D22_Loc_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[3][13] == '1')
                    {
                        D22_Load_status_lb.Text = "load break";
                        D22_Load_status_lb.BackColor = Color.Red;
                    }
                    else if (SrcStatusByte[3][14] == '1')
                    {
                        D22_Load_status_lb.Text = "short circuit";
                        D22_Load_status_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D22_Load_status_lb.Text = "";
                        D22_Load_status_lb.BackColor = Color.LimeGreen;
                    }
                    if (SrcStatusByte[3][16] == '1')
                    {
                        D22_OverHeat_lb.Text = "overheat";
                        D22_OverHeat_lb.BackColor = Color.Red;
                    }
                    else
                    {
                        D22_OverHeat_lb.Text = "";
                        D22_OverHeat_lb.BackColor = Color.LimeGreen;
                    }
                }
                
            } // try

            catch (Exception exp)
            {
                return;
            }
        }

        private void Charge_B_Click(object sender, EventArgs e)
        {
            string ID = "0"; // № выбранного источника - L1

            //if (GDK_FI_OutStatus == "─") // - знак необычный, внимательнее
            try
            {
                OnSrcChargeCtrl(this, ID + "ON");
            }
            catch (Exception) { return; }
        }

        private void DisCharge_B_Click(object sender, EventArgs e)
        {
            string ID = "0"; // № выбранного источника - L2
            try
            {
                //if (GDK_FI_OutStatus == "─") // - знак необычный, внимательнее
                OnSrcChargeCtrl(this, ID + "OFF");
            }
            catch (Exception) { return; }
            // else
            //{
            //    OnSrcOutputCtrl(this, ID + "OFF");
            // }
        }

        public class DoubleBufferedListView : ListView
        {
            public DoubleBufferedListView()
            {
                // свой класс листвью с добавление свойства даблбуфер - для устранения мерцания при обновл.
                SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint, true);
            }
        }

        private void NewSource_B_Click(object sender, EventArgs e)
        {
            /// Добавление нового истоника
            /// 

            Update_timer.Stop();
            Form2_config ConfigForm = new Form2_config();
            ConfigForm.ShowDialog();


            for (int i = 0; i < Form2_config.numberOfNewSouces; i++)
            {
                Src[NumberOfSources] = new AsyncRdTimer();

                Src[NumberOfSources].Interval = 100;
                Src[NumberOfSources].IpAdress = IPadrList[NumberOfSources];
                Src[NumberOfSources].Port = Convert.ToInt32(PortList[NumberOfSources]);
                Src[NumberOfSources].ID = NumberOfSources;
                Src[NumberOfSources].Init();
                Src[NumberOfSources].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
                Src[NumberOfSources].Start();

                Src_data[NumberOfSources] = new ListViewItem();
                NumberOfSources++;
            }
            Form2_config.numberOfNewSouces = 0;
            Update_timer.Start();
        }

        private void U2setUpDown_ValueChanged(object sender, EventArgs e)
        {
            U2setInDEC_full = Convert.ToUInt16(D11_U2setUpDown.Value);
            L_hexValue = U2setInDEC_full.ToString("X4");
        }

        private void L1_MouseEnter(object sender, EventArgs e)
        {
            L1.ForeColor = Color.DarkBlue;
        }

        private void L2_MouseEnter(object sender, EventArgs e)
        {
            L2.ForeColor = Color.DarkBlue;
        }
        private void L3_MouseEnter(object sender, EventArgs e)
        {
            L3.ForeColor = Color.DarkBlue;

        }
        private void L1_MouseLeave(object sender, EventArgs e)
        {
            L1.ForeColor = Color.Black;
        }

        private void L2_MouseLeave(object sender, EventArgs e)
        {
            L2.ForeColor = Color.Black;
        }

        private void L3_MouseLeave(object sender, EventArgs e)
        {
            L3.ForeColor = Color.Black;
        }

        private void L2_U2setB_Click(object sender, EventArgs e)
        {
            /// Вызов события установки новых параметров источника L2
            /// 
            try
            {
                U2setInDEC_full = Convert.ToUInt16(D12_U2setUpDown.Value);
                L_hexValue = U2setInDEC_full.ToString("X4");
                IdAndV2set.Clear();

                IdAndV2set.Add(1, L_hexValue);
                OnSetVoltage(this, IdAndV2set);
            }
            catch (Exception) { return; }
        }

        private void L2_ChargeOn_B_Click(object sender, EventArgs e)
        {
            string ID = "1"; // № выбранного источника - L2

            //if (GDK_FI_OutStatus == "─") // - знак необычный, внимательнее
            try
            {
                OnSrcChargeCtrl(this, ID + "ON");
            }
            catch (Exception) { return; }
        }

        private void L2_ChargeOff_B_Click(object sender, EventArgs e)
        {
            string ID = "1"; // № выбранного источника - L2

            try
            {
                OnSrcChargeCtrl(this, ID + "OFF");
            }
            catch (Exception) { return; }
        }

        private void L3_ChargeOn_B_Click(object sender, EventArgs e)
        {
            string ID = "2"; // № выбранного источника - L3

            try
            {
                OnSrcChargeCtrl(this, ID + "ON");
            }
            catch (Exception) { return; }
        }

        private void L3_ChargeOff_B_Click(object sender, EventArgs e)
        {
            string ID = "2"; // № выбранного источника - L3

            try
            {
                OnSrcChargeCtrl(this, ID + "OFF");
            }
            catch (Exception) { return; }
        }

        private void L3_U2setB_Click(object sender, EventArgs e)
        {
            /// Вызов события установки новых параметров источника D21
            /// 
            try
            {
                U2setInDEC_full = Convert.ToUInt16(D21_U2setUpDown.Value);
                L_hexValue = U2setInDEC_full.ToString("X4");
                IdAndV2set.Clear();

                IdAndV2set.Add(2, L_hexValue);
                OnSetVoltage(this, IdAndV2set);
            }
            catch (Exception) { return; }

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
            string[] settings = new string[4];

            settings[0] = reader.ReadLine();
            settings[1] = reader.ReadLine();
            settings[2] = reader.ReadLine();
            settings[3] = reader.ReadLine();

            cfg_buf = Convert.ToInt32(settings[0]);
            D11_U2setUpDown.Value = Convert.ToDecimal(cfg_buf);

            cfg_buf = Convert.ToInt32(settings[1]);
            D12_U2setUpDown.Value = Convert.ToDecimal(cfg_buf);

            cfg_buf = Convert.ToInt32(settings[2]);
            D21_U2setUpDown.Value = Convert.ToDecimal(cfg_buf);

            cfg_buf = Convert.ToInt32(settings[3]);
            D22_U2setUpDown.Value = Convert.ToDecimal(cfg_buf);

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

            writer.WriteLine(D11_U2setUpDown.Value.ToString()); // D11 voltage ctrl value
            writer.WriteLine(D12_U2setUpDown.Value.ToString()); // D12 voltage ctrl value
            writer.WriteLine(D21_U2setUpDown.Value.ToString()); // D21 voltage ctrl value
            writer.WriteLine(D22_U2setUpDown.Value.ToString()); // D22 voltage ctrl value

            writer.Close();
        }

        private void D22_U2setB_Click(object sender, EventArgs e)
        {
            /// Вызов события установки новых параметров источника D22
            /// 
            try
            {
                U2setInDEC_full = Convert.ToUInt16(D22_U2setUpDown.Value);
                L_hexValue = U2setInDEC_full.ToString("X4");
                IdAndV2set.Clear();

                IdAndV2set.Add(3, L_hexValue);
                OnSetVoltage(this, IdAndV2set);
            }
            catch (Exception) { return; }
        }

        private void D22_ChargeOn_B_Click(object sender, EventArgs e)
        {
            string ID = "3"; // № выбранного источника - D22

            try
            {
                OnSrcChargeCtrl(this, ID + "ON");
            }
            catch (Exception) { return; }
        }

        private void D22_ChargeOff_B_Click(object sender, EventArgs e)
        {
            string ID = "3"; // № выбранного источника - D22

            try
            {
                OnSrcChargeCtrl(this, ID + "OFF");
            }
            catch (Exception) { return; }
        }


    }
}