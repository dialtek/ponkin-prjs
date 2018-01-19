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
        private string SetVСmdStatus;

        // массив элементов ListViewItem для динамического заполнения таблицы данными об источниках питания 
        public static ListViewItem[] Src_data = new ListViewItem[50];
        private AsyncRdTimer[] Src = new AsyncRdTimer[50]; // Инстанциирование класса асинхр. работы с ист.1
        private string[] SrcReadVoltage = new string[50];
        private string[] SrcSetVoltage = new string[50];
        private string[] SrcStatusByte = new string[50];

        public static int NumberOfSources = 0; // переменная количества источников
        int SelSourceNumber = -1; // переменная номера выбранного источника

        public static List<string> IPadrList = new List<string>(); // лист для хранения всех IP адресов источников
        public static List<string> PortList  = new List<string>(); // лист для хранения всех портов источников
        public static List<string> SrcNames  = new List<string>();  // лист для хранения всех имен источников

         public static DoubleBufferedListView ListView1 = new DoubleBufferedListView();

        //-------------------------------------------------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        //public static event EventHandler<String> OnSrcOutputCtrl;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetParam;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetFileСfg;

        //---------------------------------  Методы ------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        public static event EventHandler<Dictionary<int, String>> OnSetVoltage;
        public static event EventHandler<String> OnSrcChargeCtrl;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            ListView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.SrcNumberC,
            this.SrcIpC,
            this.PortC,
            this.SetVoltageC,
            this.ReadVoltageC});

            this.SrcNumberC.Text = "№";
            this.SrcNumberC.Width = 50;

            this.PortC.Width = 0;

            this.SrcIpC.Width = 150;
            this.SrcIpC.Text = "Имя источника";
            this.SetVoltageC.Width = 150;
            this.SetVoltageC.Text = "U заданное, В";
            this.ReadVoltageC.Width = 215;
            this.ReadVoltageC.Text = "U на конденсаторах, В";
            this.ReadVoltageC.TextAlign = HorizontalAlignment.Center;
            this.SetVoltageC.TextAlign = HorizontalAlignment.Center;
            this.SrcNumberC.TextAlign = HorizontalAlignment.Center;
            ListView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            ListView1.GridLines = true;
            ListView1.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            ListView1.Location = new System.Drawing.Point(12, 188);
            ListView1.Name = "ListView1";
            ListView1.Scrollable = false;
            ListView1.Size = new System.Drawing.Size(630, 145);
            ListView1.TabIndex = 4;
            ListView1.UseCompatibleStateImageBehavior = false;
            ListView1.View = System.Windows.Forms.View.Details;
            ListView1.Click += new System.EventHandler(this.ListView1_B_Click);
            ListView1.FullRowSelect = true;
            Controls.Add(ListView1);

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
                if ((SRC_data[3] == "1") && (SRC_data[0] == SelSourceNumber.ToString()))
                {
                    SetVСmdStatus = SRC_data[2];
                }
                else SetVСmdStatus = "NoCmd";
            }
        }


        private void U2setB_Click(object sender, EventArgs e)
        {
            /// Вызов события установки новых параметров выбранного источника
            /// 

            U2setInDEC_full = Convert.ToUInt16(U2setVal.Text);
            string hexValue = U2setInDEC_full.ToString("X4");
            IdAndV2set.Clear();
            if (SelSourceNumber >= 0)
            {
                IdAndV2set.Add(SelSourceNumber, hexValue);
                SrcSetVoltage[SelSourceNumber] = U2setVal.Text;
                OnSetVoltage(this, IdAndV2set);

            }
            else StatusBox.Text = "Выберите источник";           
        }

        private void Update_timer_Tick(object sender, EventArgs e)
        {
            ListView1.Items.Clear();

            for (int i = 0; i < NumberOfSources; i++)
            {
                ListView1.BeginUpdate();

                ListView1.Items.Remove(Src_data[i]);
                Src_data[i].SubItems.Clear();
                Src_data[i].Text = (i + 1).ToString();
                Src_data[i].SubItems.Add(SrcNames[i]);
                Src_data[i].SubItems.Add(PortList[i]);
                Src_data[i].SubItems.Add(SrcSetVoltage[i]);
                Src_data[i].SubItems.Add(SrcReadVoltage[i]);
                ListView1.Items.Add(Src_data[i]);
               
                ListView1.Items[i].UseItemStyleForSubItems = false;
                //ListView1.Items[i].SubItems[4].BackColor = Color.PaleGreen;

                Src_data[i].SubItems[4].Font = new Font("Microsoft Sans Serif", 18F, 
                    Src_data[i].SubItems[4].Font.Style | FontStyle.Bold);


                ListView1.EndUpdate();     
            }                
            
            if (SetVСmdStatus != "NoCmd")
                {
                    switch (SetVСmdStatus)
                    {
                        case "-1": StatusBox.Text = "Ошибка соединения с источником" 
                                   + (SelSourceNumber+1).ToString(); break;
                        case "1": StatusBox.Text = "Напряжение " + U2setVal.Text + "В на источнике № " 
                                   + (SelSourceNumber+1).ToString() + " установлено успешно";  break;
                        case "0": StatusBox.Text = "Ошибка установки напряжения на источнике"
                                   + (SelSourceNumber + 1).ToString(); break;
                    }
                    
                }

            if (NumberOfSources > 0 && SelSourceNumber != -1)
                 lbl2.Text = SrcStatusByte[SelSourceNumber];//NumberOfSources.ToString();

        }

        private void Charge_B_Click(object sender, EventArgs e)
        {
            string ID = SelSourceNumber.ToString(); // № выбранного источника

            //if (GDK_FI_OutStatus == "─") // - знак необычный, внимательнее
            OnSrcChargeCtrl(this, ID + "ON");
            // else
            //{
            //    OnSrcOutputCtrl(this, ID + "OFF");
            // } 

        }

        private void DisCharge_B_Click(object sender, EventArgs e)
        {
            string ID = SelSourceNumber.ToString(); // № выбранного источника

            //if (GDK_FI_OutStatus == "─") // - знак необычный, внимательнее
            OnSrcChargeCtrl(this, ID + "OFF");
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

        private void ListView1_B_Click(object sender, EventArgs e)
        {

            ListViewItem LVI_temp = new ListViewItem();

            if (ListView1.SelectedIndices.Count > 0)
            {
                LVI_temp = ListView1.SelectedItems[0];   // вытаскиваем номер выбранного источника
                SelSourceNumber = LVI_temp.Index;      // запоминаем номер выбранного источника
                StatusBox.Text = "Выбран источник № " + (SelSourceNumber + 1).ToString();
            }
        }
    }
}