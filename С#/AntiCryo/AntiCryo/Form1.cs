using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace AntiCryo
{
    public partial class Form1 : Form
    {

        private NetworkStream ns;
        private StreamReader sr;
        private Socket server;

        string Temperature = "Z";
        string path;

        int TimeAxisHours = 0;
        int TimeAxisMinutes = 1;
        int TimeAxisSeconds = 30;

        int YaxMaxAddititon = 10;
        int YaxMinAddititon = 10;
        int CurrTemperInt;
        int DateInsertCounter = 0;

        bool fileExistFlag;
        TextWriter tw;
        StringBuilder Data2Save;



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
                    path = Environment.CurrentDirectory + "/AntiCryo Logfile " + path + ".txt";
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
        }

        private void TCPconnectB_Click(object sender, EventArgs e)
        {
            /// Подключение к серверу
            /// 

            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            server.ReceiveTimeout = 200;

            string IpAdr;
            int Port;

           if (IPadress.Text.Length !=0 || LocalPort.Text.Length != 0)
           {
               IpAdr = IPadress.Text;
               Port = Convert.ToInt16(LocalPort.Text);
           
            try
            {
                IAsyncResult result = server.BeginConnect(IpAdr, Port, null, null);
                bool success = result.AsyncWaitHandle.WaitOne(200, true);

                if (!success)
                     StatusBox.Text = "Ошибка подключения";
                else StatusBox.Text = "Соединен";

            }
            catch (Exception ex)
            {
                StatusBox.Text = "Ошибка подключения";
            }
           
           }
           else StatusBox.Text = "Введите IP адрес и порт";

           try
           {
               if (server.Connected)
               {
                   ns = new NetworkStream(server);
                   ns.ReadTimeout = 2000;
                   sr = new StreamReader(ns);
                   sr.BaseStream.ReadTimeout = 2000;
                   TCPrdTimer.Start();

               }
           }
           catch (Exception ex)
           {
               ns.Close();
               sr.Close();
               server.Close();
               StatusBox.Text = "Ошибка чтения";
           }

           fileExistFlag = false; // установка флага для создания нового лог-файла 
        }

        private void TCPdisconnectB_Click(object sender, EventArgs e)
        {
            /// отключение от сервера и закрытие всех потоков
            /// 
            //try
            //{
                if (server.Connected)
                {
                    server.Shutdown(SocketShutdown.Both);
                    server.Disconnect(true);
                }
                //ns.Close();
                //sr.Close();
                server.Close();
                StatusBox.Text = "Отключен";
            //}
            //catch (Exception)
            //{ return; }
                TCPrdTimer.Stop();
                CurrentTemper.Text = "";
                //ChartUpdateTimer.Stop();
                fileExistFlag = false;
                tw.Close(); // закрытие файла 
        }

        private void TCPrdTimer_Tick(object sender, EventArgs e)
        {
            /// чтение данных сервера
            /// 

            if (ns.DataAvailable)
            {
                Temperature = sr.ReadLine(); //ReadLine(); 
            
            if (Temperature.Length >= 5) 
            {
                if (DateInsertCounter >= 1500)
                {   // 1500 - 30 мин
                    DateInsertCounter = 0;
                }
                DateInsertCounter++; // инкремент счетчика вставки даты в лог файл

                CurrentTemper.Text = Temperature + "°C";

                DateTime maxDate = DateTime.Now;
                DateTime minDate = DateTime.Now.Subtract(new TimeSpan(
                                   TimeAxisHours, TimeAxisMinutes, TimeAxisSeconds));

                
                TemperChart.ChartAreas[0].AxisX.Minimum = minDate.ToOADate();
                TemperChart.ChartAreas[0].AxisX.Maximum = maxDate.ToOADate();

                CurrTemperInt = Convert.ToInt32(CurrentTemper.Text.Split('.')[0]);
                if (AutoscaleCheckBox.Checked)
                {
                    TemperChart.ChartAreas[0].AxisY.Maximum = YaxMaxAddititon + CurrTemperInt;
                    TemperChart.ChartAreas[0].AxisY.Minimum = CurrTemperInt - YaxMinAddititon;
                }
                else
                {
                    YaxMinUpDown.Maximum = YaxMaxUpDown.Value - 1;
                    YaxMaxUpDown.Minimum = YaxMinUpDown.Value + 1;

                    TemperChart.ChartAreas[0].AxisY.Maximum = Convert.ToInt32(YaxMaxManualUpDown.Value);
                    TemperChart.ChartAreas[0].AxisY.Minimum = Convert.ToInt32(YaxMinManualUpDown.Value);
                }
                TemperChart.Series[0].Points.AddXY(DateTime.Now, Temperature); // новая точка на графике

                Save2file(fileExistFlag, Temperature, DateInsertCounter); // запись в файл
            }
            }
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

        private void YaxMaxUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка максимума оси У
            /// 

            YaxMaxAddititon = Convert.ToInt32(YaxMaxUpDown.Value);
            
        }

        private void YaxMinUpDown_ValueChanged(object sender, EventArgs e)
        {
            /// Установка минимума оси У
            /// 

            YaxMinAddititon = Convert.ToInt32(YaxMinUpDown.Value);
        }

        private void AutoscaleCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            /// скрываем ручные установки шкалы при вкл. автошкале
            /// 

            if (AutoscaleCheckBox.Checked)
            {
                YaxMaxManualUpDown.Enabled = false;
                YaxMinManualUpDown.Enabled = false;
            }
            else
            {
                YaxMaxManualUpDown.Enabled = true;
                YaxMinManualUpDown.Enabled = true;
            }

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
            if (server.Connected)
            {
                server.Shutdown(SocketShutdown.Both);
                server.Disconnect(true);            
                server.Dispose();
                server.Close();
            }

            tw.Dispose();
            tw.Close(); // закрытие файла
 
        }
    }
}
