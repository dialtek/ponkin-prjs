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

namespace Insitek_src
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
        private Dictionary<byte, ushort> IdAndV2set = new Dictionary<byte, ushort>();

        private UInt16 U2set_num = 0;
        private string U2set_str = "";
        private string SetVСmdStatus;

        // массив элементов ListViewItem для динамического заполнения таблицы данными об источниках питания 
        public static ListViewItem[] Src_data = new ListViewItem[50];
        private AsyncRdTimer[] Src = new AsyncRdTimer[50]; // Инстанциирование класса асинхр. работы с ист.1
        private string[] SrcReadVoltage = new string[50];
        private string[] SrcReadCurrent = new string[50];
        private string[] SrcSetVoltage = new string[50];
        private string[] SrcOutStatus = new string[50];

        public static int NumberOfSources = 0; // переменная количества источников
        int SelSourceNumber = -1; // переменная номера выбранного источника

        public static List<string> IPadrList = new List<string>(); // лист для хранения всех IP адресов источников
        public static List<string> PortList  = new List<string>(); // лист для хранения всех портов источников
        public static List<string> SrcNames  = new List<string>();  // лист для хранения всех имен источников

         public static DoubleBufferedListView ListView1 = new DoubleBufferedListView();
         byte SrcModbusAddr = 100;
         bool SetVflag = false; 
        //-------------------------------------------------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        public static event EventHandler<String> OnSrcOutputCtrl;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetParam;
        //public static event EventHandler<Dictionary<int, List<String>>> OnSetFileСfg;

        //---------------------------------  Методы ------------------------------------------------------------------//

        // Создание публичных событий для передачи в др. класс
        public static event EventHandler<Dictionary<byte, ushort>> OnSetVoltage;
        public static event EventHandler<String> OnSrcChargeCtrl;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SrcOutStatus[0] = "               ";
            SrcOutStatus[1] = "               ";
            ListView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.SrcNumberC,
            this.SrcIpC,
            this.PortC,
            this.SetVoltageC,
            this.ReadVoltageC,
            this.ReadCurrentC,
            this.OutStateC });

            this.SrcNumberC.Text = "№";
            this.SrcNumberC.Width = 50;

            this.PortC.Width = 0;

            this.SrcIpC.Width = 150;
            this.SrcIpC.Text = "Имя источника";
            this.SetVoltageC.Width = 150;
            this.SetVoltageC.Text = "U заданное, кВ";
            this.ReadVoltageC.Width = 200;
            this.ReadVoltageC.Text = "U измеренное, кВ";
            this.ReadVoltageC.TextAlign = HorizontalAlignment.Center;

            this.ReadCurrentC.Width = 150;
            this.ReadCurrentC.Text = "I измер., мA";
            this.ReadCurrentC.TextAlign = HorizontalAlignment.Center;

            this.OutStateC.Width = 90;
            this.OutStateC.Text = "Выход";
            this.OutStateC.TextAlign = HorizontalAlignment.Center;
        
            this.SetVoltageC.TextAlign = HorizontalAlignment.Center;
            this.SrcNumberC.TextAlign = HorizontalAlignment.Center;
            ListView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            ListView1.GridLines = true;
            ListView1.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            ListView1.Location = new System.Drawing.Point(12, 188);
            ListView1.Name = "ListView1";
            ListView1.Scrollable = false;
            ListView1.Size = new System.Drawing.Size(790, 88);
            ListView1.TabIndex = 4;
            ListView1.UseCompatibleStateImageBehavior = false;
            ListView1.View = System.Windows.Forms.View.Details;
            ListView1.ItemSelectionChanged += ListView1_ItemSelectionChanged;
            ListView1.FullRowSelect = true;
            //Controls.Add(ListView1);

            Src[0] = new AsyncRdTimer();

            Src[0].Interval = 200;
            Src[0].IpAdress = "172.16.21.125";//"172.16.21.70";    //IPadrList[NumberOfSources];
            Src[0].Port = 4001;                     //Convert.ToInt32(PortList[NumberOfSources]);
            Src[0].ID = 10;                         //NumberOfSources;
            Src[0].Init();
            Src[0].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            Src[0].Start();
            Src_data[0] = new ListViewItem();
            Src_data[1] = new ListViewItem();
            PGM_IP.Text = "MOXA IP " + Src[0].IpAdress;
 
            Update_timer.Start();
        }

        void ListView1_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            ListViewItem LVI_temp = new ListViewItem();
            try
            {
                if (ListView1.SelectedIndices.Count > 0)
                {

                    LVI_temp = ListView1.SelectedItems[0];   // вытаскиваем номер выбранного источника
                    SelSourceNumber = LVI_temp.Index;        // запоминаем номер выбранного источника
                    U2set_str = LVI_temp.SubItems[4].Text;   // вытаскиваем текущ. U       
                    U2set_str = U2set_str.Replace(".", ",");
                    IPV30_VoltUpDown.Value = Convert.ToDecimal(U2set_str); // записываем в UpDown

                    if (SrcModbusAddr == 10) IPV30_VoltUpDown.Maximum = 30;
                    else if (SrcModbusAddr == 247) IPV30_VoltUpDown.Maximum = 120;
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        void OnSrcRdComplete(object sender, EventArgs e)
        {
            /// Чтение 
            string current_ID = "";
            string[] SRC_data = new string[3];  // Массив строк для чтения показаний источника
          
            SRC_data = Src[0].GetSrcData;   // читаем показания

            if (SRC_data[0].Contains(";"))
            {

                current_ID = SRC_data[0].Split(';')[1];

                if (current_ID == "10")
                {

                    SrcReadCurrent[0] = SRC_data[0].Split(';')[0];// сохраняем I
                    SrcReadVoltage[0] = SRC_data[1].Split(';')[0];// сохраняем U
                    SrcOutStatus[0] = SRC_data[2];  // сохраняем сост. выхода
                }
                else if (current_ID == "247")
                {
                    SrcReadCurrent[1] = SRC_data[0].Split(';')[0];// сохраняем I;
                    SrcReadVoltage[1] = SRC_data[1].Split(';')[0];// сохраняем U;
                    SrcOutStatus[1] = SRC_data[2];  // сохраняем сост. выхода
                }


            }
            if (SetVflag)
            {
                OnSetVoltage(this, IdAndV2set);
                SetVflag = false;
            }
            else
            {
                if (Src[0].ID == 10)
                    Src[0].ID = 247;
                else Src[0].ID = 10;
            }


        }

        private void U2setB_Click(object sender, EventArgs e)
        {
            /// Вызов события установки напряжения на ист. ипв 30
            ///  
           
            string buf;
            buf = IPV30_VoltUpDown.Value.ToString();
            U2set_str = buf;
            buf = buf.Replace(";", "");
            buf = buf.Replace(",", "");
            U2set_num = Convert.ToUInt16(buf);
            //MessageBox.Show(U2set_num.ToString());
            IdAndV2set.Clear();

            SetVflag = true;
            IdAndV2set.Add(10, U2set_num);
                       
        }

        private void Update_timer_Tick(object sender, EventArgs e)
        {
            
            Uread_1.Text = SrcReadVoltage[0];
            Uread_2.Text = SrcReadVoltage[1];

            Iread_1.Text = SrcReadCurrent[0];
            Iread_2.Text = SrcReadCurrent[1];

            //for (int i = 0; i < 2; i++) //NumberOfSources
            //{
            //    ListView1.BeginUpdate();

            //    ListView1.Items.Remove(Src_data[i]);
            //    Src_data[i].SubItems.Clear();
            //    Src_data[i].Text = (i + 1).ToString();
            //    if (i == 0)
            //        curr_src_name = "ИПВ 30";
            //    else curr_src_name = "ИПВ 120";
            //    Src_data[i].SubItems.Add(curr_src_name);
            //    Src_data[i].SubItems.Add("4001");
            //    Src_data[i].SubItems.Add(SrcSetVoltage[i]);
            //    Src_data[i].SubItems.Add(SrcReadVoltage[i]);
            //    Src_data[i].SubItems.Add(SrcReadCurrent[i]);

            //    Src_data[i].SubItems.Add("");
            //    ListView1.Items.Add(Src_data[i]);

            //    ListView1.Items[i].UseItemStyleForSubItems = false;
                //ListView1.Items[i].SubItems[4].BackColor = Color.PaleGreen;

                // делаем жирнее шрифт столбцов с считанными током и напряжением источников
                //Src_data[i].SubItems[4].Font = new Font("Microsoft Sans Serif", 18F,
                //    Src_data[i].SubItems[4].Font.Style | FontStyle.Bold);

                //Src_data[i].SubItems[5].Font = new Font("Microsoft Sans Serif", 18F,
                //    Src_data[i].SubItems[5].Font.Style | FontStyle.Bold);

                if (SrcOutStatus[0][2] == '1') // состояние выхода
                     OutState_1.BackColor = Color.LimeGreen;
                else OutState_1.BackColor = Color.LightGray;

                if (SrcOutStatus[1][2] == '1') // состояние выхода
                     OutState_2.BackColor = Color.LimeGreen;
                else OutState_2.BackColor = Color.LightGray;

                //if (SrcOutStatus[0][11] == '1') // перегрев источника
                //    ErrorLabel.Text = "ПЕРЕГРЕВ ИСТОЧНИКА ИПВ 30";
                //if (SrcOutStatus[1][11] == '1') // перегрев источника
                //    ErrorLabel.Text = "ПЕРЕГРЕВ ИСТОЧНИКА ИПВ 120";

                //if (SrcOutStatus[0][12] == '1') // возникновение дуги
                //    ErrorLabel.Text = "ВОЗНИКНОВЕНИЕ ДУГИ НА ИПВ 30";
                //if (SrcOutStatus[1][12] == '1') // возникновение дуги
                //    ErrorLabel.Text = "ВОЗНИКНОВЕНИЕ ДУГИ НА ИПВ 120";

                //else if (SrcOutStatus[i][13] == '1') // возникновение дуги
                //    ErrorLabel.Text = "ОТКЛ. ИСТЧНИКА" + curr_src_name + " ИЗЗА ДУГИ";
                //else ErrorLabel.Text = "";
                //ListView1.EndUpdate();

            }



            //if (SetVСmdStatus != "NoCmd")
            //    {
            //        switch (SetVСmdStatus)
            //        {
            //            case "-1": StatusBox.Text = "Ошибка соединения с источником" 
            //                       + (SelSourceNumber+1).ToString(); break;
            //            case "1": StatusBox.Text = "Напряжение "  + "В на источнике № " 
            //                       + (SelSourceNumber+1).ToString() + " установлено успешно";  break;
            //            case "0": StatusBox.Text = "Ошибка установки напряжения на источнике"
            //                       + (SelSourceNumber + 1).ToString(); break;
            //        }
                    
                //}

            //if (NumberOfSources > 0 && SelSourceNumber != -1)
            //     lbl2.Text = SrcStatusByte[SelSourceNumber];//NumberOfSources.ToString();

        //}

        private void Charge_B_Click(object sender, EventArgs e)
        {
            // ИПВ30 
            OnSrcChargeCtrl(this, "10" +";"+ "ON");

        }

        private void DisCharge_B_Click(object sender, EventArgs e)
        {
            // ИПВ30 
            OnSrcChargeCtrl(this, "10" + ";" + "OFF");
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

            //Update_timer.Stop();
            //Form2_config ConfigForm = new Form2_config();
            //ConfigForm.ShowDialog();


            //for (int i = 0; i < Form2_config.numberOfNewSouces; i++)
            //{
            //    Src[NumberOfSources] = new AsyncRdTimer();

            //    Src[NumberOfSources].Interval = 100;
            //    Src[NumberOfSources].IpAdress = IPadrList[NumberOfSources];
            //    Src[NumberOfSources].Port = Convert.ToInt32(PortList[NumberOfSources]);
           //    Src[NumberOfSources].ID = 10;//NumberOfSources;
            //    Src[NumberOfSources].Init();
            //    Src[NumberOfSources].OnSrcRdComplete += new EventHandler(OnSrcRdComplete);
            //    Src[NumberOfSources].Start();

            //    Src_data[NumberOfSources] = new ListViewItem();
            //    NumberOfSources++;
            //}
            //Form2_config.numberOfNewSouces = 0;
            //Update_timer.Start();

        }

        //private void ListView1_B_SelectedIndexChanged(object sender, EventArgs e)
        //{

        //    ListViewItem LVI_temp = new ListViewItem();

        //    if (ListView1.SelectedIndices.Count > 0)
        //    {

        //        LVI_temp = ListView1.SelectedItems[0];   // вытаскиваем номер выбранного источника
        //        SelSourceNumber = LVI_temp.Index;        // запоминаем номер выбранного источника
        //        StatusBox.Text = "Выбран источник № " + (SelSourceNumber + 1).ToString();

        //        U2set_str = LVI_temp.SubItems[4].Text;   // вытаскиваем текущ. U       
        //        U2set_str = U2set_str.Replace(".", ",");
        //        VoltageUpDown.Value = Convert.ToDecimal(U2set_str); // записываем в UpDown

        //        if (SelSourceNumber == 0)
        //            SrcModbusAddr = 10;
        //        else if (SelSourceNumber == 1)
        //            SrcModbusAddr = 247;
        //        else StatusBox.Text = "Выберите источник";
        //    }

        //}

        private void IPV30_MouseEnter(object sender, EventArgs e)
        {
            IPV30.ForeColor = Color.DarkBlue;
        }

        private void IPV120_MouseEnter(object sender, EventArgs e)
        {
            IPV120.ForeColor = Color.DarkBlue;
        }

        private void IPV30_MouseLeave(object sender, EventArgs e)
        {
            IPV30.ForeColor = Color.Black;
        }

        private void IPV120_MouseLeave(object sender, EventArgs e)
        {
            IPV120.ForeColor = Color.Black;
        }

        private void IPV120_ChargeOn_B_Click(object sender, EventArgs e)
        {
            // ИПВ120 
            OnSrcChargeCtrl(this, "247" + ";" + "ON");
        }

        private void IPV120_ChargeOff_B_Click(object sender, EventArgs e)
        {
            // ИПВ120 
            OnSrcChargeCtrl(this, "247" + ";" + "OFF");
        }

        private void IPV120_UsetB_Click(object sender, EventArgs e)
        {
            // уст. U на ипв120
            /// Вызов события установки напряжения на ист. ипв 120
            ///  
            string buf;
            buf = IPV120_VoltUpDown.Value.ToString();
            U2set_str = buf;
            buf = buf.Replace(";", "");
            buf = buf.Replace(",", "");
            U2set_num = Convert.ToUInt16(buf);
            //U2set_num *= 10;

            IdAndV2set.Clear();

            SetVflag = true;
            IdAndV2set.Add(247, U2set_num);
        }

    }
}