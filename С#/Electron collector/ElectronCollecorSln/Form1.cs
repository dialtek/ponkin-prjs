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

namespace ElectronCollecorSln
{
    public partial class Form1 : Form
    {

        int BaudRate = 115200;
        int watchDogCounter = 0;
        int AverLoopCounter = 0;

        bool NewMeasFlag;                    // флаг новых измерений
        bool MDR32InIdle;
        bool ZeroSetFl = false;              // флаг установки нуля

        double[] StripCurrentNum = new double[65];
        float[] StripCurrentAverVal = new float[65];
        double[] StripNoiseNum = new double[65]; // инициал. нулями..!!!!!!!!!!
        double SumI = 0;                        
        double AverSumI = 0;                           

        SerialPort rs_port;
        string ReceivedData = "";
        string[] StripCurrentStr;
        string LastUpdateTime = " -";
        TextWriter tw;
        SaveFileDialog save;
        StringBuilder Data2Save;

        MovingAverCalc AverageCalc;          // калькулятор скользящего среднего 
        int AverageBufSize = 5;              // начальный размер буфера усреднения

        private List<List<int>> AverOfStrip = new List<List<int>>(); //          
        

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

        public void InitRs()
        {
            // открытие порта

            if (rs_port.IsOpen == true)
                rs_port.Close();
            rs_port.Open();
            rs_port.DiscardInBuffer();
        }

        public void RefreshData()
        {
            // обновляем показания
            SumI = 0;

            watchDogCounter++;  

            if (ReceivedData.Length > 60)
            {
                //AverLoopCounter++;

                Chart.Series["StripsCurrent"].Points.Clear();
                try
                {
                    StripCurrentStr = ReceivedData.Split(';');                        
                    
                    if (ZeroSetFl)
                        {
                            for (int i = 0; i < 65; i++)
                            {
                                ZeroSetFl = false;
                                StripNoiseNum[i] = Convert.ToDouble(StripCurrentStr[i]);
                            }
                        }

                        for (int i = 0; i < 65; i++)
                        {
                            StripCurrentNum[i] = Convert.ToDouble(StripCurrentStr[i]);
                            StripCurrentNum[i] -= StripNoiseNum[i];                            
                            if (StripCurrentNum[i] < 0)
                            {
                                StripCurrentNum[i] = 0;
                            }
                            StripCurrentAverVal[i] = AverageCalc.NextValue((float)StripCurrentNum[i]);
                            Chart.Series["StripsCurrent"].Points.AddXY(i + 1, StripCurrentAverVal[i]);

                            SumI += StripCurrentNum[i]; // расчет суммарного тока
                            AverSumI = AverageCalc.NextValue((float)SumI);
                        }

                        //AverSumI = AverageCalc.NextValue((float)SumI);

                        //if (AverLoopCounter > AverageBufSize)
                        //{
                        //    AverLoopCounter = 0;
                        //    for (int i = 0; i < 65; i++)
                        //    {

                        //    }
                           TotalCurrentL.Text = " " + AverSumI.ToString();
                        //}

                        

                    if (Convert.ToDouble(StripCurrentStr[65]) > 40)
                    {
                        StatusBox.Text = "ВНИМАНИЕ! Температура платы выше 40 °C";
                        StatusBox.BackColor = Color.Red;
                        StatusBox.ForeColor = Color.Yellow;
                    }
                    else if (Convert.ToDouble(StripCurrentStr[65]) < -20)
                    {
                        StatusBox.Text = "ВНИМАНИЕ! Температура платы ниже -20 °C";
                        StatusBox.BackColor = Color.Red;
                        StatusBox.ForeColor = Color.Yellow;

                    }
                    else
                    {
                        StatusBox.Text = "";
                        StatusBox.BackColor = Color.White;
                        StatusBox.ForeColor = Color.Black;
                    }

                    PCBtemper.Text = StripCurrentStr[65] + "°C";
                    LastUpdateTime = GetCurrTime();
                    ReceivedData = "";
                }

                catch (Exception)
                {
                    StatusBox.Text = "Ошибка чтения";
                }
            }

            else 
            {

                MDR32InIdle = ReceivedData.Contains("Z");

                if (MDR32InIdle)
                {
                    MDR32InIdle = false;
                    StatusBox.Text = "Подключен. Данные обновлены:" + LastUpdateTime;
                }

                if (watchDogCounter >= 10)
                {
                    StatusBox.Text = "Ошибка соединения";
                }
            }

        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            PortList.DataSource = System.IO.Ports.SerialPort.GetPortNames();
            YaxisLabel.Text = "Tок\n[мкA]";     // angle to rotate
            YaxisLabel.Visible  = false;
            XaxisLabel.Visible  = false;
            PCBtemper.Visible   = false;

            PortList.Enabled    = true;
            StartRdB.Enabled    = true;
            StopRdB.Enabled     = false;
            ScreenShotB.Enabled = false;
            Save2fileB.Enabled  = false;
            ZeroSetB.Enabled    = false;
            Σlabel.Enabled      = false;

            if (PortList.Items.Count == 0) { StatusBox.Text = "Нет активных COM-портов"; }
            else
            {
                using (rs_port = new SerialPort(PortList.Text, BaudRate, Parity.None, 8, StopBits.One))
                { }
            }
        }

        void rs_port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // обработчик события получения байт портом

            watchDogCounter = 0; // сброс сторожевого счетчика

            try
            {
                ReceivedData = rs_port.ReadTo("E");
            }
            catch (Exception)
            {
                //StatusBox.Text = "Ошибка чтения";
            }

        }

        private void StartRdB_Click(object sender, EventArgs e)
        {
            // Начало измерений
            AverageCalc = new MovingAverCalc(AverageBufSize);
           
            InitRs();
            rs_port.DataReceived += rs_port_DataReceived; // подписываемся на событие получения байт порта

            RefreshTimer.Start();
            YaxisLabel.Visible = true;
            XaxisLabel.Visible = true;
            PCBtemper.Visible  = true;
            PortList.Enabled   = false;
            StartRdB.Enabled   = false;
            StopRdB.Enabled    = true;
            ScreenShotB.Enabled = true;
            Save2fileB.Enabled = true;
            ZeroSetB.Enabled = true;
            Σlabel.Enabled = true;
            NewMeasFlag        = true;   // новый цикл измерений
        }

        private void RefreshTimer_Tick(object sender, EventArgs e)
        {
            // обновление пользовательского интерфейса
            RefreshData();
        }

        private void StopRdB_Click(object sender, EventArgs e)
        {
            // Конец измерений

            rs_port.DataReceived -= rs_port_DataReceived; // отписываемся от события получения байт порта
            rs_port.Close();
            RefreshTimer.Stop();
            Chart.Series["StripsCurrent"].Points.Clear();
            TotalCurrentL.Text = "";
            YaxisLabel.Visible = false;
            XaxisLabel.Visible = false;
            PCBtemper.Visible  = false;
            PortList.Enabled = true;
            StartRdB.Enabled = true;
            StopRdB.Enabled = false;
            ScreenShotB.Enabled = false;
            Save2fileB.Enabled = false;
            ZeroSetB.Enabled = false;
            Σlabel.Enabled = false;

            try
            {
                tw.Close(); // закрытие файла 
            }
            catch (Exception ex)
            { return; }
                
        }

        private void ScreenShotB_Click(object sender, EventArgs e)
        {            
            SaveFileDialog ScreenShotSaveDial = new SaveFileDialog();
            var frm = Form.ActiveForm;

            ScreenShotSaveDial.Title = "Сохранение скриншота программы...";
            ScreenShotSaveDial.Filter = "Снимок | *.png";

            if (ScreenShotSaveDial.ShowDialog() == DialogResult.OK)
            {
            using (var bmp = new Bitmap(frm.Width, frm.Height))
            {
                frm.DrawToBitmap(bmp, new Rectangle(0, 0, bmp.Width, bmp.Height));
                bmp.Save(ScreenShotSaveDial.FileName);
            }
            }
        }

        private void Save2fileB_Click(object sender, EventArgs e)
        {
            /// сохранение данных в текстовый файл
            /// 

            if (NewMeasFlag)
            {   // создается новый файл - новый цикл измерений

                save = new SaveFileDialog();
                Data2Save = new StringBuilder();

                save.Title = "Сохранение конфигурационного данных";
                save.Filter = "Файл | *.txt";            
                try
                {   // вызываем диалог, просим указать путь
                    if (save.ShowDialog() == DialogResult.OK)
                       tw = new StreamWriter(File.Create(save.FileName));
                       Data2Save.Append(save.FileName + "\n\r");
                       Data2Save.Append(GetTimeAndData() + "\n\r");   // вставляем текущ. дату и время
                }
                 catch (Exception ex)
                {
                     StatusBox.Text = "Ошибка сохранения файла";
                }    

                NewMeasFlag = false; // сброс флага новых измерений
             }
                Data2Save.Append(PowerTb.Text + "\t");       // 1ый эл. строки - мощность
                Data2Save.Append(TotalCurrentL.Text + "\t"); // 2ый эл. строки - суммарный ток
                for (int i = 0; i < 65; i++)
                {
                     Data2Save.Append(StripCurrentStr[i] + "\t");
                }
                // добавляем U нагрева и U уск. и комментарий
                Data2Save.Append(HeatingVoltTb.Text + "\t" + AccelUTb.Text + "\t" + ComCommentTb.Text + "\n");
                //PowerTb.Text = "";          // сбрасываем комментарии для новой строки измерений
                //HeatingVoltTb.Text = "";
                //AccelUTb.Text = "";
                //ComCommentTb.Text = "";
                 // запись в файл
                 tw.Write(Data2Save);
                 Data2Save.Clear();
                 
            }

        private void ZeroSetB_Click(object sender, EventArgs e)
        {
            ZeroSetFl = true;
        }

        private void AverageNumUpDown_ValueChanged(object sender, EventArgs e)
        {
         
            AverageBufSize = Convert.ToInt32(AverageNumUpDown.Value);

            AverageCalc = new MovingAverCalc(AverageBufSize);
        }
      }
    }
