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

        private String VDK_FI_voltage = "", VDK_FI_current = "", VDK_FI_OutStatus = "", // переменные источника ВДК-ФИ
                       VDK_FI_I_limit = "", VDK_FI_V_limit = "", VDK_FI_OutState = "-";

        private String V2set = "", Voltage2set = "", V_limit = "", I_limit = "";
 
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
        //private AsyncRdTimer GDK_FI_RwTimer = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ГДК-ФИ
        //private AsyncRdTimer VDK_1_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ВДК-1
        //private AsyncRdTimer GDK_1_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ГДК-1
        //private AsyncRdTimer VDK_6_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ВДК-6
        //private AsyncRdTimer GDK_6_RwTimer  = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ГДК-6

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
            VDK_FI_RwTimer.Interval = 300;
            VDK_FI_RwTimer.SrcId = 1;
            VDK_FI_RwTimer.IpAdress = "10.10.10.70";
            VDK_FI_RwTimer.Port = 4001;
            VDK_FI_RwTimer.Init();
            VDK_FI_RwTimer.OnSrcRdComplete += new EventHandler(SrcReadTimer_OnVDK_FIdataRd);

            VoltageUpDown.DecimalPlaces = 2;
            VoltageUpDown.Increment = 0.01M;

            CurrentLimitUpDown.DecimalPlaces = 2;
            CurrentLimitUpDown.Increment = 0.01M;
            SelectedSourceId = 1;

            VDK_FI_RwTimer.Start();
   
            DataUpdateTimer.Start();
        }

        private void VDK_FI_OutputBoff_Click(object sender, EventArgs e)
        {
            string ID = "1"; // ID источника ВДК-ФИ

            OnSrcOutputCtrl(this, ID + "Выкл."); // команда вкл
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

        public void VDK_FI_OutputB_Click(object sender, EventArgs e)
        {
            /// ВКЛ/ВЫКЛ нагрузки ВДК-ФИ
            /// 

            string ID = "1"; // ID источника ВДК-ФИ

            //if (VDK_FI_OutStatus == "Выкл.") // - знак необычный, внимательнее
            OnSrcOutputCtrl(this, ID + "Вкл."); // команда вкл
            //else
            // {
            //     OnSrcOutputCtrl(this, ID + "OFF"); // команда выкл. если сейчас вкл. 
            // } 
                
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
            //VDK_FI_OutputBoN.Text = VDK_FI_OutStatus;

            if (VDK_FI_OutStatus == "Вкл.")
            {
                VDK_FI_OutputBoN.Enabled = false;
                VDK_FI_OutputBoff.Enabled =true;
                OutStatusLb.Text = "Ток включен";
                OutStatusLb.BackColor = Color.LimeGreen;
            }
            if (VDK_FI_OutStatus == "Выкл.")
            {
                VDK_FI_OutputBoN.Enabled = true;
                VDK_FI_OutputBoff.Enabled = false;
                OutStatusLb.Text = "Ток выключен";
                OutStatusLb.BackColor = Color.LightGray;
            }


            if (VDK_FI_voltage == "*") PowErrContainer.Add("ВДК-ФИ", true);
            else PowErrContainer.Add("ВДК-ФИ", false);
            if (VDK_FI_voltage == "OFF") ConErrContainer.Add("ВДК-ФИ", true);
            else ConErrContainer.Add("ВДК-ФИ", false);
     
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
                ConErrMsg = "Источник выключен";
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

        //VoltageUpDown.Value      = (Decimal) Convert.ToDouble(Format(Voltage2set));
        //VoltageLimitUpDown.Value = (Decimal) Convert.ToInt16(VDK_FI_V_limit);
        //CurrentLimitUpDown.Value = (Decimal) Convert.ToDouble(Format(VDK_FI_I_limit));

        private void CurrentLimitUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка лимита по току для выбранного источника 
            /// 
            I_limit = Convert.ToString(CurrentLimitUpDown.Value);
            I_limit = I_limit.Replace(',', '.');
            //IdAndData2set.Add(SelectedSourceId, I_limit);
            //OnSetCurrentLimit(this, IdAndData2set);

        }

        private void VoltageLimitUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка лимита по напряжению для выбранного источника
            /// 

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
     }
 }
