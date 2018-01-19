using System;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;
using System.Collections.Generic;
using System.IO.IsolatedStorage;
using System.Text;
using System.IO;
using System.Windows.Input;

namespace LU20_correctors_ctrl
{
  
    /// <summary>
    /// сохранение значений для формы с настройками
    /// </summary>
    static public class settings_data
    {
        static string _VDK_FI_Vmax = "";    // уровень ограничения 1
        static string _GDK_FI_Vmax = "";    // уровень ограничения 2
        static string _VDK_1_Vmax = "";    // уровень ограничения 3
        static string _GDK_1_Vmax = "";    // уровень ограничения 4
        static string _VDK_6_Vmax = "";    // уровень ограничения 5
        static string _GDK_6_Vmax = "";    // уровень ограничения 6

        static string _IP = "";
        static int _port = 0;
        // Specify a name for your filename
        static private string _storage_name = "LU_20_correctors_settings.txt";

        static public string storage_name
        {
            get { return _storage_name; }
            set { _storage_name = value; }
        }
        static public string VDK_FI_Vmax
        {
            get { return _VDK_FI_Vmax; }
            set { _VDK_FI_Vmax = value; }
        }
        static public string GDK_FI_Vmax
        {
            get { return _GDK_FI_Vmax; }
            set { _GDK_FI_Vmax = value; }
        }
        static public string VDK_1_Vmax
        {
            get { return _VDK_1_Vmax; }
            set { _VDK_1_Vmax = value; }
        }
        static public string GDK_1_Vmax
        {
            get { return _GDK_1_Vmax; }
            set { _GDK_1_Vmax = value; }
        }
        static public string VDK_6_Vmax
        {
            get { return _VDK_6_Vmax; }
            set { _VDK_6_Vmax = value; }
        }
        static public string GDK_6_Vmax
        {
            get { return _GDK_6_Vmax; }
            set { _GDK_6_Vmax = value; }
        }
        static public string IP
        {
            get { return _IP; }
            set { _IP= value; }
        }
        static public int port
        {
            get { return _port; }
            set { _port = value; }
        }
    }


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        WSettings taskWindow;
        public MainWindow()
        {

        }

        public void Starter()
        {
            Task task_monitoring = Task.Factory.StartNew(StartMonitor);
            while (true)
            {
                if (task_monitoring.Status == TaskStatus.Faulted || task_monitoring.Status == TaskStatus.RanToCompletion)
                {
                    task_monitoring = Task.Factory.StartNew(StartMonitor);
                }
                Thread.Sleep(2 * 1000);

            }
        }

        public void StartMonitor()
        {
            while (true)
            {
                QueueElement queue = new QueueElementR(67, 1000, 20);
                modbus_transport.getInstance().GetMsgFromDevice(queue);
                Thread.Sleep(1000);
            }
        }

        private string FormatOutputDetectorH(int b)
        {
            var b_str = Math.Abs(b).ToString();
            var zeros = "";
            for (int i = b_str.ToString().Length; i < 4; i++)
                zeros += "0";

            return zeros + b_str;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            InitializeComponent();
            // прячем картинку высокого - опасность проверится позже
            DeviceManager.getInstance().CreateDevices(this);
            string[] settings = new string[2];

            try
            {
                // Read all lines from the file in isolated storage.
                IsolatedStorageFile isoStore =
                    IsolatedStorageFile.GetStore(IsolatedStorageScope.User
                    | IsolatedStorageScope.Assembly, null, null);

                IsolatedStorageFileStream iStream =
                  new IsolatedStorageFileStream(settings_data.storage_name,
                  FileMode.Open, isoStore);

                StreamReader reader = new StreamReader(iStream);

                settings[0] = reader.ReadLine();
                settings[1] = reader.ReadLine();
            }
            catch (FileNotFoundException ex)
            {
                settings[0] = "192.168.127.254";
                settings[1] = "4001";
            }


            // восстанавливаем IP из настроек
            if (settings[0] != null) settings_data.IP = settings[0];
            else settings_data.IP = "192.168.127.254";

            // восстанавливаем порт
            if (settings[1] != null) settings_data.port =Convert.ToInt32(settings[1]);
            else settings_data.port = 4001;

            DeviceManager.getInstance().StartConnection(settings_data.IP, settings_data.port);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            DeviceManager.getInstance().SaveState();
            Environment.Exit(Environment.ExitCode);
        }

        private void SettingsB_Click(object sender, RoutedEventArgs e)
        {
            if (taskWindow != null && taskWindow.IsLoaded == true)
            {
                return;
            }
            taskWindow = new WSettings();
            //Теперь MainWindow главное окно для taskWindow
            taskWindow.Owner = this;
            taskWindow.Show();
        }

        private void Group_OFF_click(object sender, RoutedEventArgs e)
        {
            // групповое выкл. выхода
            Set_out_common(0);
        }

        private void Group_ON_click(object sender, RoutedEventArgs e)
        {
            // групповое вкл. выхода
            Set_out_common(1);
        }

        private void Set_out_common(int state)
        {
            QueueElement qe = new QueueElementW(61, 1004, state);
            modbus_transport.getInstance().GetMsgFromDevice(qe);

            qe = new QueueElementW(62, 1004, state);
            modbus_transport.getInstance().GetMsgFromDevice(qe);

            qe = new QueueElementW(63, 1004, state);
            modbus_transport.getInstance().GetMsgFromDevice(qe);

            qe = new QueueElementW(64, 1004, state);
            modbus_transport.getInstance().GetMsgFromDevice(qe);

            qe = new QueueElementW(65, 1004, state);
            modbus_transport.getInstance().GetMsgFromDevice(qe);

            qe = new QueueElementW(66, 1004, state);
            modbus_transport.getInstance().GetMsgFromDevice(qe);

        }
    }
}
