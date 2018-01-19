using System;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;
using System.Collections.Generic;
using System.IO.IsolatedStorage;
using System.IO;
using System.Configuration;
using System.Linq;

namespace extract_system
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
        static string _DCHV_V = "";           // уровень напряжения БФВН вывода
        static string _q_extr_time = "";      // длительность быстр. вывода
        static string _IP = "";
        static int _port = 0;
        static string _ion_cool_voltage = ""; // уровень напряжения модулятора ион. охл.

        // Specify a name for your filename
        static private string _storage_name = "krion_ex_pgm_settings.txt";

        static public string storage_name
        {
            get { return _storage_name; }
            set { _storage_name = value; }
        }

        static public string DCHV_V
        {
            get { return _DCHV_V; }
            set { _DCHV_V = value; }
        }

        static public string q_extr_time
        {
            get { return _q_extr_time; }
            set { _q_extr_time = value; }
        }

        static public string ion_cool_V
        {
            get { return _ion_cool_voltage; }
            set { _ion_cool_voltage = value; }
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

        void GroupHVcontrol(int state)
        {
            /// групповое управление высоким напряжением блоков 
            /// 
            if (state > 1 || state < 0) return;

            var devices = DeviceManager.getInstance().devices;
            QueueElement queue_el;

            foreach (var device in devices.Where(dev => dev.Value.IsEnabled == true))
            {   // Только для усройств формирующих высокое
                if (device.Value.Type == "DCHV" || device.Value.Type == "PBF")
                {
                    // всех устройств
                    queue_el = new QueueElementW(Convert.ToInt32(device.Key), 1009, state);
                    modbus_transport.getInstance().GetMsgFromDevice(queue_el);
                }
            }

        }

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
                QueueElement queue2 = new QueueElementR(2, 1000, 20);
                modbus_transport.getInstance().GetMsgFromDevice(queue2);
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
            HV_image.Visibility = Visibility.Hidden;

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
            hv_status.danger_lvl = 50;   // уровень V при котором устройство добавляется в список опасных
            hv_status.OnListChange += Update_HV_list;
        }

        private void Update_HV_list(object sender, List<string> dev_list)
        {
            // обносвление списка устройств с высоким напряжением

            dangerList.Content = "";

            if(dev_list.Count > 0)
                HV_image.Visibility = Visibility.Visible;
            else
                HV_image.Visibility = Visibility.Hidden;

            for (int i = 0; i < dev_list.Count; i++)
            {
                dangerList.Content += dev_list[i];
                dangerList.Content += System.Environment.NewLine;
            }

           

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

        private void Group_HV_OFF_click(object sender, RoutedEventArgs e)
        {
            GroupHVcontrol(0);
        }

        private void Group_HV_ON_click(object sender, RoutedEventArgs e)
        {
            // групповое вкл. высокого напряжения

            GroupHVcontrol(1);
        }

        //var btn = sender as Button;
        //if (btn == null) return;

        //// Background - нажатой кнопки
        //btn.Background = new SolidColorBrush(Color.FromArgb(100, 145, 243, 243));

        //foreach (var button in mypanel.Children.OfType<Button>().Where(button => button.Content != btn.Content))
        //{
        //    // Background - остальных кнопок, находящиеся на mypanel
        //    button.Background = new SolidColorBrush(Color.FromArgb(100, 245, 243, 243));
        //}
    }
}
