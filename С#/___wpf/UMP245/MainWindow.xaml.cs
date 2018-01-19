using System;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;
using System.Collections.Generic;
using System.IO.IsolatedStorage;
using System.Text;
using System.IO;

namespace UMP245
{
    /// <summary>
    /// отображение источников на выходе которых есть высокое
    /// </summary>
    static public  class hv_status
    {
        static private List<string> names = new List<string>();
        static private event EventHandler<List<string>> _OnListChange;
        static private int _HV_danger_lvl = 50;  // уровень V при котором устройство добавляется в список опасных

        /// <summary>
        /// изменения списка устройств
        /// </summary>
        static public EventHandler<List<string>> OnListChange
        {
            get { return _OnListChange; }
            set { _OnListChange += value; }
        }

        // уровень V при котором устройство добавляется в список опасных 
        static public int danger_lvl
        {
            get { return _HV_danger_lvl; }
            set { _HV_danger_lvl = value; }
        }

        static public  void add_element(string s)
        {
            if (names.Contains(s)) return;
            names.Add(s);
            OnListChange(null,names);

        }

        static public  void del_element(string s)
        {
            if (names.Contains(s))
            {
                names.Remove(s);
                OnListChange(null, names);
            }
            else return;
        }       
    }

    /// <summary>
    /// сохранение значений для формы с настройками
    /// </summary>
    static public class settings_data
    {
        static string _rf_delay = "";   // задержка ВЧ
        static string _rf_with = "";    // длительность ВЧ
        static string _rf_level = "";   // уровень срабатывания индикации 
        static string _IP = "";
        static int _port = 0;

        // Specify a name for your filename
        static private string _storage_name = "ump245_settings.txt";

        static public string storage_name
        {
            get { return _storage_name; }
            set { _storage_name = value; }
        }

        static public string rf_delay
        {
            get { return _rf_delay; }
            set { _rf_delay = value; }
        }

        static public string rf_with
        {
            get { return _rf_with; }
            set { _rf_with = value; }
        }

        static public string rf_level
        {
            get { return _rf_level; }
            set { _rf_level = value; }
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
            
            
            //Task.Factory.StartNew(Starter);
            //DeviceManager.getInstance().

            //for (int i = 0; i < 800; i++) modbus_transport_instance.push_queue(queue);
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
                QueueElement queue = new QueueElementR(7, 1000, 20);
                modbus_transport.getInstance().GetMsgFromDevice(queue);
                Thread.Sleep(600);
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
            catch (FileNotFoundException)
            {
                settings[0] = "192.168.127.252";
                settings[1] = "4001";
            }


            // восстанавливаем IP из настроек
            if (settings[0] != null) settings_data.IP = settings[0];
            else settings_data.IP = "192.168.127.252";

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
    }
}
