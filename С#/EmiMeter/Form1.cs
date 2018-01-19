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
using System.IO.Ports;
using ZedGraph;
using System.Drawing.Imaging;

namespace EmiMeterSln
{   /// Программа визуализации профиля пучка
    public partial class Form1 : Form
    {
        Form_intensChart Form2_intens_chart;
        FormBarGraph Form3_X_profile_bar;
        FormBarGraph Form4_Y_profile_bar;

        double[] X_profile_data = new double[21];
        double[] Y_profile_data = new double[21];
        double[] ADCchNoise = new double[48];
        double sum_charge = 0;
        double detector_beam_V = 0;
        double detector_beam_I = 0;
        double detector_beam_Q = 0;
        double IVC_Cint = 100.00e-12;   // емкость ОС интегратора IVC102
        
        bool read_status = false;
        private int ADC_scale = 0;
        double SumI_float = 0;
        int  T_integr = 300; // время интегрирования по умолчанию,мкс
        bool T_integr_set_flag = false;
        bool Scale_set_flag = false;
        bool Trig_mode_flag = false;
        bool Cont_mode_flag = false;
        string read_buf = "";                     // буфер первочначального чтения
        double[] ADCsChDataNum = new double[48];   // массив данных каналов АЦП
        string[] ADCsChDataStr = new string[48];   // массив данных каналов АЦП
        double[] InputConnPin = new double[48];   // массив данных для сопоставления контактов разъема ножкам АЦП
        double[] DetectorStripX = new double[22]; // массив данных для сопоставления контактов разъема стрипам детектора
        double[] DetectorStripY = new double[22]; // массив данных для сопоставления контактов разъема стрипам детектора
        bool ZeroSetFl = false;              // флаг установки нуля

        private NetworkStream ns; // сеть
        private StreamReader sr;
        private Socket server;
        IPEndPoint IpAndPort;

        TextWriter tw;                 // сохр. в файл
        StringBuilder Data2Save;       // флаг новых измерений
        string path = @"C:\BPM_V1_42"; // path to programm folder
        private Action ConstReadDelegate;

        private Dictionary <string, double[]> XY_Bar_DataDict = new Dictionary <string,double[]>(); // контейнер хранения данных профиля пучка по Х и Y

        public static event EventHandler <double>   OnIntensRead;                                   // создаем событие чтения АЦП, интенсивность
        public static event EventHandler <Dictionary <string,double[]>> OnChargeRead;               // создаем событие чтения АЦП, интенсивность

        TcpClient client; // Creates a TCP Client
        byte[] datalength = new byte[4]; // creates a new byte with length 4 ( used for receivng data's lenght)
        int k;

        private String GetCurrTime()
        {
            /// Получаем текущие дату и время 

            String CurrentTime;

            CurrentTime = DateTime.Now.TimeOfDay.ToString();
            CurrentTime = CurrentTime.Substring(0, 8);
            return ("_" + CurrentTime);
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
            CurrentTime = CurrentTime.Replace(":","_");

            return (CurrentDate + "_" + "_" + CurrentTime);
        }

        public bool Connect2server(IPEndPoint IpAndPort)
        {


            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            server.ReceiveTimeout = 500;
            try
            {
                //IAsyncResult result = server.BeginConnect(IpAndPort, null, null);
                server.Connect(IpAndPort);
                //bool success = result.AsyncWaitHandle.WaitOne(100, true);
                //if (!success)
                //{
                //    server.Close();
                //    return false;
                //}

            }
            catch (Exception)
            {
                server.Close();
                return false;
            }
            //
            try
            {
                if (server.Connected)
                {
                    ns = new NetworkStream(server);
                    ns.ReadTimeout = 500;
                    sr = new StreamReader(ns);
                    sr.BaseStream.ReadTimeout = 500;
                    return true;
                }
                return false;
            }
            catch (Exception)
            {
                ns.Close();
                sr.Close();
                server.Close();
                return false;
            }
        }


        /// <summary>
        /// Отключение от сервера
        /// </summary>
        public void DisconnectServer()
        {
            /// отключение от сервера и закрытие всех потоков
            /// 
            try
            {
                if (server.Connected)
                {
                    server.Shutdown(SocketShutdown.Both);
                    server.Disconnect(true);
                }
                ns.Close();
                sr.Close();
                server.Close();
            }
            catch (Exception)
            { return; }
        }

        private byte crc8(byte data, byte crc)
        {
            // расчет контрольной суммы
            byte CRC8POLY = 0x18;
 
            byte bit_counter;
            byte feedback_bit;

            bit_counter = 8;

            do
            {
                feedback_bit = (byte)((crc ^ data) & 0x01);
                if (feedback_bit == 0x01) crc = (byte)(crc ^ CRC8POLY);
                crc = (byte)((crc >> 1) & 0x7F);
                if (feedback_bit == 0x01) crc = (byte)(crc | 0x80);
                data = (byte)(data >> 1);
                bit_counter--;
            } while (bit_counter > 0);

            return crc;
        }

        public void RefreshData()
        {
 
            int count = 0;  // переменная искусственного таймаута чтения
            byte CRC = 0;
            byte[] CmdBuf = new byte[8]; // буфер команды для отправки
            string RdBuf = "";
            byte T_integr_msb = 0;
            byte T_integr_lsb = 0;

            try
            {
                if (Connect2server(IpAndPort))
                { 
                    if (T_integr_set_flag) // уст. времени интегрирования
                    {
                        T_integr_set_flag = false;

                        T_integr_msb = (byte)(T_integr >> 8);       // Ст разряд переменной Т интегрирования
                        T_integr_lsb = (byte)((T_integr & 0x00ff)); // Мл разряд переменной Т интегрирования

                        CmdBuf[0] = (byte)'T';
                        CmdBuf[1] = T_integr_lsb;
                        CmdBuf[2] = T_integr_msb;
                        CmdBuf[3] = 0; CmdBuf[4] = 0; CmdBuf[5] = 0; CmdBuf[6] = 0; CmdBuf[7] = 0;
                        ns.Write(CmdBuf, 0, 8);  // запись команды в прибор
                        
                        while (!ns.DataAvailable)                   // ждем данные
                        {
                            if (count >= 20) { break; } count++; Thread.Sleep(1); // искусственный таймаут чтения...
                        }
                        RdBuf = sr.ReadLine();
                        L1.Invoke(new Action<string>((s) => L1.Text = s), RdBuf); // делегат для обращения к элементу из др. потока
                    }

                    if (Scale_set_flag) // уст. значения шкалы АЦП
                    {
                        Scale_set_flag = false;

                        CmdBuf[0] = (byte)'Q';
                        CmdBuf[1] = (byte)ADC_scale; // '0' - 3 pC, '1' - 6 pC, '2' - 12 pC
                        CmdBuf[2] = 0;
                        CmdBuf[3] = 0; CmdBuf[4] = 0; CmdBuf[5] = 0; CmdBuf[6] = 0; CmdBuf[7] = 0;
                        ns.Write(CmdBuf, 0, 8);  // запись команды в прибор

                        while (!ns.DataAvailable)                   // ждем данные
                        {
                            if (count >= 20) { break; } count++; Thread.Sleep(1); // искусственный таймаут чтения...
                        }
                        RdBuf = sr.ReadLine();
                        L1.Invoke(new Action<string>((s) => L1.Text = s), RdBuf); // делегат для обращения к элементу из др. потока
                    }

                    if (Trig_mode_flag)
                    {   
                        Trig_mode_flag = false;
                        CmdBuf[0] = (byte)'M';
                        CmdBuf[1] = 0x01;
                        CmdBuf[2] = 0;
                        CmdBuf[3] = 0; CmdBuf[4] = 0; CmdBuf[5] = 0; CmdBuf[6] = 0; CmdBuf[7] = 0;
                        ns.Write(CmdBuf, 0, 8);  // запись команды в прибор

                        while (!ns.DataAvailable)                   // ждем данные
                        {
                            if (count >= 20) { break; } count++; Thread.Sleep(1); // искусственный таймаут чтения...
                        }
                        RdBuf = sr.ReadLine();
                        Modelb.Invoke(new Action<string>((s) => Modelb.Text = s), RdBuf); // делегат для обращения к элементу из др. потока
                    }

                    if (Cont_mode_flag)
                    {
                        Cont_mode_flag = false;
                        CmdBuf[0] = (byte)'M';
                        CmdBuf[1] = 0x00;
                        CmdBuf[2] = 0;
                        CmdBuf[3] = 0; CmdBuf[4] = 0; CmdBuf[5] = 0; CmdBuf[6] = 0; CmdBuf[7] = 0;
                        ns.Write(CmdBuf, 0, 8);  // запись команды в прибор

                        while (!ns.DataAvailable)                   // ждем данные
                        {
                            if (count >= 20) { break; } count++; Thread.Sleep(1); // искусственный таймаут чтения...
                        }
                        RdBuf = sr.ReadLine();
                        Modelb.Invoke(new Action<string>((s) => Modelb.Text = s), RdBuf); // делегат для обращения к элементу из др. потока
                        
                    }


                    if (ContModeRb.Checked == true)
                    {
                        CmdBuf[0] = (byte)('C');
                        CmdBuf[1] = 0; CmdBuf[2] = 0; CmdBuf[3] = 0; CmdBuf[4] = 0; CmdBuf[5] = 0; CmdBuf[6] = 0; CmdBuf[7] = 0;

                        ns.Write(CmdBuf, 0, 8); // отсылка команды в прибор
                    }

                        while (!ns.DataAvailable)  // ждем данные
                        {
                            if (count >= 20) { break; } count++; Thread.Sleep(1); // искусственный таймаут чтения...
                        }

                        read_buf = sr.ReadLine();               // читаем 

                        if (read_buf.Contains("E"))             // проверка, все ли считано до конца?
                        {
                            read_status = true;                    // поднимаем флаг успешного чтения
                            ADCsChDataStr = read_buf.Split(';');   // распределяем данные по каналам
                            for (int i = 0; i < 48; i++)
                            {   // заполняем массив полученными данными
                                ADCsChDataNum[i] = Convert.ToDouble(ADCsChDataStr[i]);
                            }

                            if (ZeroSetFl)
                            { // запоминаем шум
                                for (int i = 0; i < 48; i++)
                                {
                                    ZeroSetFl = false;
                                    ADCchNoise[i] = ADCsChDataNum[i];
                                }
                            }

                            for (int i = 0; i < 48; i++)
                                ADCsChDataNum[i] -= ADCchNoise[i]; // убираем шум

                            // таблица соответствия пинов разъема входам АЦП
                            #region Input connector <-> ADCs channel <-> Profilometer channels

                            InputConnPin[1] = ADCsChDataNum[6];   // Вход 7 АЦП
                            InputConnPin[2] = ADCsChDataNum[12];  // Вход 13 АЦП
                            InputConnPin[3] = ADCsChDataNum[4];   // Вход 5 АЦП
                            InputConnPin[4] = ADCsChDataNum[5];   // Вход 6 АЦП
                            InputConnPin[5] = ADCsChDataNum[14];  // Вход 15 АЦП
                            InputConnPin[6] = ADCsChDataNum[15];  // Вход 16 АЦП
                            InputConnPin[7] = ADCsChDataNum[23];  // Вход 24 АЦП
                            InputConnPin[8] = ADCsChDataNum[26];  // Вход 27 АЦП
                            InputConnPin[9] = ADCsChDataNum[19];  // Вход 20 АЦП
                            InputConnPin[10] = ADCsChDataNum[20]; // Вход 21 АЦП
                            InputConnPin[11] = ADCsChDataNum[43]; // Вход 43 АЦП
                            InputConnPin[12] = ADCsChDataNum[40]; // Вход 40 АЦП
                            InputConnPin[13] = ADCsChDataNum[42]; // Вход 42 АЦП
                            InputConnPin[14] = ADCsChDataNum[38]; // Вход 35 АЦП
                            InputConnPin[15] = ADCsChDataNum[46]; // Вход 47 АЦП

                            InputConnPin[16] = ADCsChDataNum[2];  // Вход 3 АЦП
                            InputConnPin[17] = ADCsChDataNum[8];  // Вход 9 АЦП
                            InputConnPin[18] = ADCsChDataNum[11]; // Вход 12 АЦП
                            InputConnPin[19] = ADCsChDataNum[10]; // Вход 11 АЦП
                            InputConnPin[20] = ADCsChDataNum[7];  // Вход 8 АЦП
                            InputConnPin[21] = ADCsChDataNum[13]; // Вход 14 АЦП
                            InputConnPin[22] = ADCsChDataNum[31]; // Вход 32 АЦП
                            InputConnPin[23] = ADCsChDataNum[21]; // Вход 22 АЦП
                            InputConnPin[24] = ADCsChDataNum[25]; // Вход 26 АЦП
                            InputConnPin[25] = ADCsChDataNum[29]; // Вход 30 АЦП
                            InputConnPin[26] = ADCsChDataNum[30]; // Вход 31 АЦП
                            InputConnPin[27] = ADCsChDataNum[37]; // Вход 34 АЦП
                            InputConnPin[28] = ADCsChDataNum[39]; // Вход 41 АЦП
                            InputConnPin[29] = ADCsChDataNum[36]; // Вход 37 АЦП
                            InputConnPin[30] = ADCsChDataNum[47]; // Вход 47 АЦП

                            InputConnPin[31] = ADCsChDataNum[0];  // Вход 1 АЦП
                            InputConnPin[32] = ADCsChDataNum[3];  // Вход 4 АЦП
                            InputConnPin[33] = ADCsChDataNum[9];  // Вход 10 АЦП
                            InputConnPin[34] = ADCsChDataNum[1];  // Вход 2 АЦП
                            InputConnPin[35] = ADCsChDataNum[16]; // Вход 17 АЦП
                            InputConnPin[36] = ADCsChDataNum[18]; // Вход 19 АЦП
                            InputConnPin[37] = ADCsChDataNum[24]; // Вход 25 АЦП
                            InputConnPin[38] = ADCsChDataNum[27]; // Вход 28 АЦП
                            InputConnPin[39] = ADCsChDataNum[28]; // Вход 29 АЦП
                            InputConnPin[40] = ADCsChDataNum[17]; // Вход 18 АЦП
                            InputConnPin[41] = ADCsChDataNum[22]; // Вход 23 АЦП
                            InputConnPin[42] = ADCsChDataNum[44]; // Вход 44 АЦП

                            /////-- стрипы детектора <-> пины разъема DHR
                            ///// X-PROFILE
                            DetectorStripX[1] = InputConnPin[17];
                            DetectorStripX[2] = InputConnPin[27];
                            DetectorStripX[3] = InputConnPin[16];
                            DetectorStripX[4] = InputConnPin[12];
                            DetectorStripX[5] = InputConnPin[24];
                            DetectorStripX[6] = InputConnPin[2];
                            DetectorStripX[7] = InputConnPin[39];
                            DetectorStripX[8] = InputConnPin[29];
                            DetectorStripX[9] = InputConnPin[37];
                            DetectorStripX[10] = InputConnPin[7];
                            DetectorStripX[11] = InputConnPin[32];
                            DetectorStripX[12] = InputConnPin[11];
                            DetectorStripX[13] = InputConnPin[42];
                            DetectorStripX[14] = InputConnPin[26];
                            DetectorStripX[15] = InputConnPin[20];
                            DetectorStripX[16] = InputConnPin[5];
                            DetectorStripX[17] = InputConnPin[22];
                            DetectorStripX[18] = InputConnPin[1];
                            DetectorStripX[19] = InputConnPin[41];
                            DetectorStripX[20] = InputConnPin[14];
                            DetectorStripX[21] = InputConnPin[18];

                            ///// Y-PROFILE
                            DetectorStripY[1] = InputConnPin[25];
                            DetectorStripY[2] = InputConnPin[23];
                            DetectorStripY[3] = InputConnPin[8];
                            DetectorStripY[4] = InputConnPin[35];
                            DetectorStripY[5] = InputConnPin[3];
                            DetectorStripY[6] = InputConnPin[38];
                            DetectorStripY[7] = InputConnPin[28];
                            DetectorStripY[8] = InputConnPin[34];
                            DetectorStripY[9] = InputConnPin[13];
                            DetectorStripY[10] = InputConnPin[21];
                            DetectorStripY[11] = InputConnPin[9];
                            DetectorStripY[12] = InputConnPin[19];
                            DetectorStripY[13] = InputConnPin[30];
                            DetectorStripY[14] = InputConnPin[36];
                            DetectorStripY[15] = InputConnPin[10];
                            DetectorStripY[16] = InputConnPin[31];
                            DetectorStripY[17] = InputConnPin[15];
                            DetectorStripY[18] = InputConnPin[33];
                            DetectorStripY[19] = InputConnPin[4];
                            DetectorStripY[20] = InputConnPin[40];
                            DetectorStripY[21] = InputConnPin[6];


                            #endregion  // region
                        }

                    if (TrigModeRb.Checked == true)
                    {



                    }
                } // if connected

                else
                {
                    read_status = false; //  данные не были прочитаны, уходим на следующий цикл запроса данных
                    StatusBox.Invoke(new Action<string>((s) => StatusBox.Text = s), "Reading error..."); // ошибка чтения
                }
                DisconnectServer();       //  отключаемся от конечной точки

                if (read_status)          // если считать удалось
                {
                    for (int i = 0; i < 21; i++)
                    {                                                // индекс !!!!!!
                        X_profile_data[i] = Convert.ToDouble(DetectorStripX[i+1]) / 10;  // сохр. данные профиля Х в формате: "7.4 pC"
                        Y_profile_data[i] = Convert.ToDouble(DetectorStripY[i+1]) / 10;  // сохр. данные профиля Y в формате: "7.4 pC"
                        sum_charge = X_profile_data.Sum() + Y_profile_data.Sum(); // считаем полный заряд в pC
                    }
                    detector_beam_V = Convert.ToDouble(ADCsChDataStr[48]) / 100000; // в Вольтах
                    detector_beam_I = (detector_beam_V / (((double)T_integr * 0.000001) / IVC_Cint)); /// 10E+5); // в микроамперах
                    detector_beam_Q = (detector_beam_I * ((double)T_integr * 0.000001)); // пКл

                    sum_charge *= 1.00e-12;        // приведение к Кулонам
                    sum_charge += detector_beam_Q; // суммируем все заряды
                    
                    SumI_float = sum_charge / ((double)T_integr * 10E-7);  // общий ток
 
                    // делегат для обращения к элементу из др. потока
                    BeamQ.Invoke(new Action<string>((s) => BeamQ.Text = s), detector_beam_Q.ToString("0.00E0")); // ток коллектора
                    // делегат для обращения к элементу из др. потока
                    TargetI.Invoke(new Action<string>((s) => TargetI.Text = s), detector_beam_I.ToString("0.00E0")); // ток коллектора

                    SumQlb.Invoke(new Action<string>((s) => SumQlb.Text = s), "ΣQ:" + sum_charge.ToString("0.00E0")); // в Кулонах
                    SumIlb.Invoke(new Action<string>((s) => SumIlb.Text = s), "ΣI:" + SumI_float.ToString("0.00E0")); // в Амперах

                    XY_Bar_DataDict.Clear();                          // очищаем словарь данных с профилями пучка

                    //if(Form3_X_profile_bar.Visible)
                        XY_Bar_DataDict.Add("X profile", X_profile_data); // добавляем новые данные профиля X в словарь

                    //if (Form4_Y_profile_bar.Visible)
                        XY_Bar_DataDict.Add("Y profile", Y_profile_data); // добавляем новые данные профиля Y в словарь
                    
                    OnChargeRead(this, XY_Bar_DataDict);              // вызываем событие обновления гистограмм профилей X и Y
                    
                    //if (Form2_intens_chart.Visible)
                    SumI_float *= 1000000;
                    OnIntensRead(this, SumI_float);                   // вызываем событие обновления графика интенсивности
                    StatusBox.Invoke(new Action<string>((s) => StatusBox.Text = s), "Updated " + GetCurrTime());
                }
                
           } // try

           catch (Exception ex)
            {
                StatusBox.Invoke(new Action<string>((s) => StatusBox.Text = s), "Reading error..."); // ошибка чтения
                MessageBox.Show(ex.Message);
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            IpAndPort = new IPEndPoint(IPAddress.Parse(IP_adr_textbox.Text), // текущий IP
                                         Convert.ToInt32(Port_texbox.Text)); // Port 
           

            Form2_intens_chart = new Form_intensChart();
            Form2_intens_chart.Show();
            Form2_intens_chart.Hide();

            Form3_X_profile_bar = new FormBarGraph();
            Form3_X_profile_bar.G_Name = "X profile";
            Form3_X_profile_bar.Title = "X profile";
            //Form3_X_profile_bar.Text = "График распределения заряда по X-стрипам коллектора";
            Form3_X_profile_bar.Show();
            Form3_X_profile_bar.Hide();

            Form4_Y_profile_bar = new FormBarGraph();
            Form4_Y_profile_bar.G_Name = "Y profile";
            Form4_Y_profile_bar.Title = "Y profile";
            //Form4_Y_profile_bar.Text = "График распределения заряда по Y-стрипам коллектора";
            Form4_Y_profile_bar.Show();
            Form4_Y_profile_bar.Hide();

            // Начало измерений
            ConstReadDelegate = new Action(RefreshData);
            RefreshTimer.Start();
             //ClientReceive();
               
  
//RefreshTimer.Start();
     //System.Environment.NewLine       
            

        }

        public void ClientReceive()
        {

            ns = client.GetStream(); //Gets The Stream of The Connection
           // new Thread(() => // Thread (like Timer)
           // {
                while ((k = ns.Read(datalength, 0, 4)) != 0)//Keeps Trying to Receive the Size of the Message or Data
                {
                    // how to make a byte E.X byte[] examlpe = new byte[the size of the byte here] , i used BitConverter.ToInt32(datalength,0) cuz i received the length of the data in byte called datalength :D
                    byte[] data = new byte[BitConverter.ToInt32(datalength, 0)]; // Creates a Byte for the data to be Received On
                    ns.Read(data, 0, data.Length); //Receives The Real Data not the Size

                    this.Invoke((MethodInvoker)delegate // To Write the Received data
                    {
                        Testlb.Text = Encoding.Default.GetString(data);
                    });
                    //Thread.Sleep(10);
                }
           // }).Start(); // Start the Thread
        }
  
        private void RefreshTimer_Tick(object sender, EventArgs e)
        {
            // обновление пользовательского интерфейса
            RefreshData();
            //ConstReadDelegate.BeginInvoke(null, null);
        }

        private void ScreenShotB_Click(object sender, EventArgs e)
        {    // saving screenshot        

            int screenLeft = SystemInformation.VirtualScreen.Left;
            int screenTop = SystemInformation.VirtualScreen.Top;
            int screenWidth = SystemInformation.VirtualScreen.Width;
            int screenHeight = SystemInformation.VirtualScreen.Height;

            string imageName = GetTimeAndData(); // saving current date and time
            // creating director if doesnt exist
            if (!Directory.Exists(path)) Directory.CreateDirectory(path);

            try
            {
                using (Bitmap bmp = new Bitmap(screenWidth, screenHeight))
                {
                    // Draw the screenshot into our bitmap.
                    using (Graphics g = Graphics.FromImage(bmp))
                    {
                        g.CopyFromScreen(screenLeft, screenTop, 0, 0, bmp.Size);
                    }
                    // Do something with the Bitmap here, like save it to a file:
                    bmp.Save(path + "\\" + imageName + "_" + CommentTb.Text + "_" + ".jpg", ImageFormat.Jpeg);
                }
                StatusBox.Text = "Done, " + path + "\\" + "_" + CommentTb.Text + "_" + ".jpg";
            }
            catch (Exception ex)
            {
                StatusBox.Text = "Error..";
            }
        }

        private void Save2fileB_Click(object sender, EventArgs e)
        {
            /// сохранение данных в текстовый файл
            /// 
            string fileName = GetTimeAndData(); // saving current date and time                    
            Data2Save = new StringBuilder();
            
            try
            {          

                if (!Directory.Exists(path)) Directory.CreateDirectory(path);
                tw = new StreamWriter(File.Create(path + "\\" + fileName + ".txt"));
                Data2Save.Append(GetTimeAndData() + "\n\r");   // вставляем текущ. дату и время
                Data2Save.Append(CommentTb.Text + "\n\r");     // вставляем комментарий
                //--
                Data2Save.Append("X profile, pC" + "\n");
                for (int i = 0; i < 21; i++)
                    Data2Save.Append(X_profile_data[i] + "\n");

                Data2Save.Append("Y profile, pC" + "\n");
                for (int i = 0; i < 21; i++)
                    Data2Save.Append(Y_profile_data[i] + "\n");

                Data2Save.Append("Beam Q = " + detector_beam_Q + " pC" + "\n");
                Data2Save.Append("Sum I = " + SumI_float + " uA" + "\n");
                Data2Save.Append("T int = " + T_integr + " us" + "\n" + "----" + "\n");

                // запись в файл
                tw.Write(Data2Save);
                Data2Save.Clear();
                tw.Close();
                StatusBox.Text = "Done, " + path + "\\" + fileName + "_" + CommentTb.Text + ".txt";
            }
            catch (Exception ex)
            {
                StatusBox.Text = "File saving error...";
            }

        }

        private void AutoReadPeriod_ValueChanged(object sender, EventArgs e)
        {   
            /// Устанавливаем период обновления данных при постоянных измерениях
            /// 

            RefreshTimer.Interval = (int)AutoReadPeriod.Value;

        }

        private void IntensShowB_Click(object sender, EventArgs e)
        {
            Form2_intens_chart.Show();
        }

        private void XprofileShowB_Click(object sender, EventArgs e)
        {
            Form3_X_profile_bar.Show();
        }

        private void YprofileShowB_Click(object sender, EventArgs e)
        {
            Form4_Y_profile_bar.Show();
        }

        private void ZeroSetB_Click(object sender, EventArgs e)
        {
            /// поднятие флага уст. 0
            /// 
            ZeroSetFl = true;
        }

        private void Tint_UpDown_ValueChanged(object sender, EventArgs e)
        {   // уст. значения времени интегрирования
            T_integr = (int)Tint_UpDown.Value;
            T_integr_set_flag = true;
        }

        private void ADCscaleComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {  
            /// сохр. значения шкалы АЦП, поднятие флага установки шкалы 
            /// 

            ADC_scale = ADCscaleComboBox.SelectedIndex;
            switch (ADC_scale)
            {
                case 0: 
                    Form3_X_profile_bar.Ymax = 4;
                    Form4_Y_profile_bar.Ymax = 4;
                break;

                case 1:
                    Form3_X_profile_bar.Ymax = 7;
                    Form4_Y_profile_bar.Ymax = 7;
                break;

                case 2:
                    Form3_X_profile_bar.Ymax = 13;
                    Form4_Y_profile_bar.Ymax = 13;
                break;
            
            }
            
            Scale_set_flag = true;

        }

        private void ContModeRb_CheckedChanged(object sender, EventArgs e)
        { 
            /// вкл. режим непрерывных измерений
            /// 
            if (ContModeRb.Checked == true)
            {
                //Cont_mode_flag = true;
                //RefreshTimer.Start();
                AutoReadPeriod.Enabled = true;
                RefreshTimer.Interval = (int)AutoReadPeriod.Value;
            }
        }

        private void TrigModeRb_CheckedChanged(object sender, EventArgs e)
        {
            /// вкл. режим импульсных измерений
            /// 

            if(TrigModeRb.Checked == true)
            { 
                Trig_mode_flag = true;
            //RefreshTimer.Stop();
            AutoReadPeriod.Enabled = false;
            RefreshTimer.Interval = 20;
            }

        }
    }
}
