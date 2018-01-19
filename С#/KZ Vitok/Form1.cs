using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.IO.IsolatedStorage;
using System.Net;
using System.Net.Sockets;
//uuu
namespace KZ_vitok
{
    public partial class Form1 : Form
    {

        //private NetworkStream ns;
        //private StreamReader sr;
        //private Socket server;

        private AsyncRdTimer DataUpdTimer = new AsyncRdTimer(); // Инстанциирование класса асинхр. работы с ВДК-ФИ

        string ADC_voltage = "Z";
        string path;
        string ReadBuf = "";
        string[] MagnetFieldStr = new string[2] {"",""}; // 1 эл. - целые, 2 - дробные
        string[] CurrentStr = new string[2] {"",""};

        int TimeAxisTotalSeconds = 0;
        int TimeAxisdx = 0;
        int TimeAxisHours = 0;
        int TimeAxisMinutes = 1;
        static int TimeAxisSeconds = 30;
        int PointsOnChart = 0;           // количество точек на графике
        TimeSpan ChartDataLenght;        // временной отрезок графика
        int ChartDataLenghtmSec = 0;     // временной отрезок графика

        int YaxMax = 2500;
        int YaxMin = -100;
        double MagnetField;
        double MagnetFieldNoise = 0;
        double Current;

        DateTime maxDate;
        DateTime minDate;

        bool fileExistFlag;
        TextWriter tw;
        StringBuilder Data2Save;

        Queue<string> RdDataQueue = new Queue<string>(2000);

        const string ISOLATED_FILE_NAME = "KZ_vitok_UserData.txt";

        private void LoadSettings()
        {
            // Read all lines from the file in isolated storage.
            IsolatedStorageFile isoStore =
            IsolatedStorageFile.GetStore(IsolatedStorageScope.User
            | IsolatedStorageScope.Assembly, null, null);

            IsolatedStorageFileStream iStream =
              new IsolatedStorageFileStream(ISOLATED_FILE_NAME,
              FileMode.Open, isoStore);

            StreamReader reader = new StreamReader(iStream);
            string[] settings = new string[2];

            settings[0] = reader.ReadLine();
            TimeAxisSeconds = Convert.ToInt32(settings[0]);
            XaxSecUpDown.Value = Convert.ToDecimal(TimeAxisSeconds); 
            reader.Close();
        }

        private void SaveSettings()
        {
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

            writer.WriteLine(IPadress.Text);                         // ip 
            writer.WriteLine(LocalPort.ToString());                  // порт 
            writer.WriteLine(XaxHoursUpDown.Value.ToString());       // часы 
            writer.WriteLine(XaxMinUpDown.Value.ToString());         // мин 
            writer.WriteLine(XaxSecUpDown.Value.ToString());         // секунды 
            writer.WriteLine(YaxMaxManualUpDown.Value.ToString());   // max.Y
            writer.WriteLine(YaxMinManualUpDown.Value.ToString());   // min.Y 
            writer.WriteLine(YaxIntUpDown.Value.ToString());         // интервал Y
            writer.WriteLine(XaxIntUpDown.Value.ToString());         // интервал X 


            //writer.WriteLine("This is second line.");
            writer.Close();

        }

        private void Save2file(bool fileExist, string text2save, int DateInsertCnt)
        {
            /// запись данных в файл, расположенный в директории программы 
            /// 

            try
            {
                Data2Save = new StringBuilder();

                if (!fileExist)
                {
                    DateTime currentDate = DateTime.Now;
                    

                    //Здесь можешь указать нужный формат
                    path = currentDate.ToString("dd_MM_yyyy_HHч_mmм");
                    path = Environment.CurrentDirectory + "/KZ vitok log-file" + path + ".txt";
                    tw = new StreamWriter(File.Create(path));
                    fileExistFlag = true; // инверсный сброс флага нового файла 
                }

                if (DateInsertCnt >= 1500)
                {
                    Data2Save.Append("----- " + DateTime.Now + " -----");              
                }
                // запись в файл
                Data2Save.Append(text2save);
                tw.WriteLine(Data2Save);

            }
            catch (Exception ex)
            {
                StatusBox.Text = "Ошибка при сохранении лог-файла";
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            TemperChart.ChartAreas[0].AxisX.LabelStyle.Format = "HH:mm:ss";
            TemperChart.ChartAreas[0].CursorX.IsUserEnabled = false;
            TemperChart.ChartAreas[0].CursorX.IsUserSelectionEnabled = false;
            TemperChart.ChartAreas[0].AxisX.ScaleView.Zoomable = false;
            TemperChart.ChartAreas[0].AxisX.ScrollBar.IsPositionedInside = false;

            YaxMaxUpDown.Visible = false;
            YaxMinUpDown.Visible = false;
            YaxMaxManualUpDown.Enabled = true;
            YaxMinManualUpDown.Enabled = true;
            XaxHoursUpDown.Enabled = false;

            DataUpdTimer.OnSrcRdComplete += DataUpdTimer_OnSrcRdComplete;
            Thread.CurrentThread.Priority = ThreadPriority.AboveNormal;

            DataUpdTimer.IpAdress = IPadress.Text;
            DataUpdTimer.Port = Convert.ToInt16(LocalPort.Text);

            DataUpdTimer.Init();
            DataUpdTimer.Start();
            GraphUpdTimer.Start();
            DataUpdTimer.Interval = 10;
            //LoadSettings();
        }

        void DataUpdTimer_OnSrcRdComplete(object sender, EventArgs e)
        {
            //ADC_voltage = DataUpdTimer.GetSrcData;  // читаем показания
            RdDataQueue.Enqueue(DataUpdTimer.GetSrcData);  // читаем показания
        }

        private void XaxHoursUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// изменяем значение часов интервала просмотра графика
            ///

            TimeAxisHours = Convert.ToInt32(XaxHoursUpDown.Value);
        }

        private void XaxMinUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// изменяем значение минут интервала просмотра графика
            /// 

            TimeAxisMinutes = Convert.ToInt32(XaxMinUpDown.Value);
        }

        private void XaxSecUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// изменяем значение секунд интервала просмотра графика
            ///
            TimeAxisSeconds = Convert.ToInt32(XaxSecUpDown.Value);
        }

        private void ScreenShotB_Click(object sender, EventArgs e)
        {
            /// скриншот экрана
            /// 

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

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //if (server.Connected)
            //{
            //    server.Shutdown(SocketShutdown.Both);
            //    server.Disconnect(true);            
            //    server.Dispose();
            //    server.Close();
            //    tw.Dispose();
            //    tw.Close(); // закрытие файла
            //}
            //SaveSettings();
        }

        private void GraphUpdTimer_Tick(object sender, EventArgs e)
        {
            Thread.CurrentThread.Priority = ThreadPriority.AboveNormal;

            try
            {   label10.Text = RdDataQueue.Count.ToString();
                ADC_voltage = RdDataQueue.Dequeue();
                
            }
            catch (System.InvalidOperationException ex)
            {
                if (RdDataQueue.Count > 1999)
                { RdDataQueue.Clear(); }
                return;
            }

            if (ADC_voltage == "-")
                StatusBox.Text = "Ошибка чтения";
            else if (ADC_voltage == "*")
                StatusBox.Text = "Ошибка подключения";
            else
            {
                try
                {

                    DataUpdTimer.IpAdress = IPadress.Text;
                    DataUpdTimer.Port = Convert.ToInt16(LocalPort.Text);

                    MagnetField = ((Convert.ToDouble(ADC_voltage) - MagnetFieldNoise)
                        * (1 / 0.885)); // расчет магнитного поля из напряжения АЦП 
                    Current = MagnetField * 0.333;                             // расчет тока кз витка из МП

                    ReadBuf = MagnetField.ToString();
                    if (ReadBuf.Contains(","))
                    {
                        MagnetFieldStr[0] = ReadBuf.Split(',')[0];
                        MagnetFieldStr[1] = ReadBuf.Split(',')[1];
                        MagnFieldLb.Text = MagnetFieldStr[0] + "," + MagnetFieldStr[1].Substring(0, 1);
                    }
                    else MagnFieldLb.Text = ReadBuf + " Гс";

                    ReadBuf = Current.ToString();
                    if (ReadBuf.Contains(","))
                    {
                        CurrentStr[0] = ReadBuf.Split(',')[0];
                        CurrentStr[1] = ReadBuf.Split(',')[1];
                        CurrentLb.Text = CurrentStr[0] + "," + CurrentStr[1].Substring(0, 1);
                    }
                    else CurrentLb.Text = ReadBuf + " А";
                    StatusBox.Text = "";
                    TemperChart.Series[0].Color = Color.GreenYellow;


                    ////////////// работа с графиком

                    // всего секунд в отрезке времени
                    TimeAxisTotalSeconds = (int)XaxHoursUpDown.Value * 3600 + (int)XaxMinUpDown.Value * 60 + (int)XaxSecUpDown.Value;
                    //if(TimeAxisTotalSeconds > )
                    // сдвиг отрисовки графика по оси х
                    TimeAxisdx = TimeAxisTotalSeconds / 5;

                    maxDate = DateTime.Now.AddSeconds(TimeAxisdx);
                    minDate = DateTime.Now.Subtract(new TimeSpan(
                                       TimeAxisHours, TimeAxisMinutes, TimeAxisSeconds));

                    YaxMax = Convert.ToInt32(YaxMaxManualUpDown.Value);
                    YaxMin = Convert.ToInt32(YaxMinManualUpDown.Value);

                    TemperChart.ChartAreas[0].AxisY.Interval = Convert.ToInt32(YaxIntUpDown.Value);
                    TemperChart.ChartAreas[0].AxisX.Interval = Convert.ToInt32(XaxIntUpDown.Value);

                    if (YaxMax > YaxMin)
                    {
                        TemperChart.ChartAreas[0].AxisY.Maximum = YaxMax;
                    }

                    if (YaxMin < YaxMax)
                    {
                        TemperChart.ChartAreas[0].AxisY.Minimum = YaxMin;
                    }
                    TemperChart.ChartAreas[0].AxisX.Minimum = minDate.ToOADate();
                    TemperChart.ChartAreas[0].AxisX.Maximum = maxDate.ToOADate();

                    PointsOnChart = TemperChart.Series[0].Points.Count; // запоминаем кол-во точек на графике
                    ChartDataLenght = maxDate - minDate;
                    ChartDataLenghtmSec = Convert.ToInt32(ChartDataLenght.TotalMilliseconds);

                    TemperChart.Series[0].Points.AddXY(DateTime.Now, Current); // новая точка на графике
                    label11.Text = PointsOnChart.ToString();
                    //if ((PointsOnChart * 45) > (TimeAxisTotalSeconds*1000))
                    if (PointsOnChart > 1499)
                    {
                        TemperChart.Series[0].Points.RemoveAt(0);
                    }

                }
                catch (Exception ex)
                {
                    StatusBox.Text = "Другая ошибка";
                    CurrentLb.Text = "";
                    MagnFieldLb.Text = "";
                    TemperChart.Series[0].Color = Color.Red;
                }
            }
           }

        private void ZeroSetB_Click(object sender, EventArgs e)
        {
            try
            {
                if (ManualZeroSet.Checked)
                {
                    MagnetFieldNoise = Convert.ToDouble(ManualZero.Text);
                }
                else 
                { 
                    MagnetFieldNoise = (Convert.ToDouble(ADC_voltage));
                }
                
                TemperChart.Series[0].Points.Clear();
            }
            catch (Exception ex)
            {
                MagnetFieldNoise = 0;
            }
        }

        private void ManualZeroSet_CheckedChanged(object sender, EventArgs e)
        {
            // вкл. возможность задать смещение нуля вручную 

            ManualZero.Enabled = ManualZeroSet.Checked;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TemperChart.Series[0].Points.Clear();
        }
        }
    }