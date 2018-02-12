using System;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;
using System.Collections.Generic;
using System.IO.IsolatedStorage;
using System.Text;
using System.IO;

namespace LXM_ctrl
{

    /// <summary>
    /// сохранение значений для формы с настройками
    /// </summary>
    static public class settings_data
    {
        static string _reg_addr = "";   // адрес регистра
        static string _format = "";     // формат
        static string _overlap = "";    // нахлест
        static string _IP = "";
        static int _port = 0;

        // Specify a name for your filename
        static private string _storage_name = "lxm_settings.txt";

        static public string storage_name
        {
            get { return _storage_name; }
            set { _storage_name = value; }
        }

        static public string reg_addr
        {
            get { return _reg_addr; }
            set { _reg_addr = value; }
        }

        static public string format
        {
            get { return _format; }
            set { _format = value; }
        }

        static public string overlap
        {
            get { return _overlap; }
            set { _overlap = value; }
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
                QueueElement queue = new QueueElementR(2, 9736, 2);
                modbus_transport.getInstance().GetMsgFromDevice(queue);
                Thread.Sleep(600);
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            InitializeComponent();
            // прячем картинку высокого - опасность проверится позже

            DeviceManager.getInstance().CreateDevices(this);
            string[] settings = new string[5];

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

                settings[0] = reader.ReadLine();  // ip
                settings[1] = reader.ReadLine();  // port 
                settings[2] = reader.ReadLine();  // reg addr
                settings[3] = reader.ReadLine();  // format
                settings[4] = reader.ReadLine();  // overlap
            }
            catch (FileNotFoundException)
            {
                settings[0] = "192.168.127.254";
                settings[1] = "4001";
                settings[2] = "9736"; // reg addr
                settings[3] = "620";  // format
                settings[4] = "1";    // overlap
            }

            // восстанавливаем IP из настроек
            if (settings[0] != null) settings_data.IP = settings[0];
            else settings_data.IP = "192.168.127.254";

            // восстанавливаем порт
            if (settings[1] != null) settings_data.port =Convert.ToInt32(settings[1]);
            else settings_data.port = 4001;

            // восстанавливаем адрес
            if (settings[2] != null) settings_data.reg_addr = settings[2];
            else settings_data.reg_addr = "9736";

            // восстанавливаем формат
            if (settings[3] != null) settings_data.format = settings[3];
            else settings_data.format = "620";

            // восстанавливаем формат
            if (settings[4] != null) settings_data.overlap = settings[4];
            else settings_data.overlap = "1";

            DeviceManager.getInstance().StartConnection(settings_data.IP, settings_data.port);
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //DeviceManager.getInstance().SaveState();
            // write the settings file
            // Check if the file already exists in isolated storage.
            IsolatedStorageFile isoStore =
              IsolatedStorageFile.GetStore(IsolatedStorageScope.User
              | IsolatedStorageScope.Assembly, null, null);

            string[] fileNames = isoStore.GetFileNames(settings_data.storage_name);

            try
            {
                foreach (string file in fileNames)
                {
                    if (file == settings_data.storage_name)
                        isoStore.DeleteFile(settings_data.storage_name);
                }

                // Write some text into the file in isolated storage.
                IsolatedStorageFileStream oStream =
                  new IsolatedStorageFileStream(settings_data.storage_name,
                  FileMode.Create, isoStore);

                StreamWriter writer = new StreamWriter(oStream);

                writer.WriteLine(settings_data.IP);              // saving IP
                writer.WriteLine(settings_data.port.ToString()); // saving port
                writer.WriteLine(settings_data.reg_addr);             
                writer.WriteLine(settings_data.format);
                writer.WriteLine(settings_data.overlap);

                writer.Close();
            }
            catch (Exception)
            {

            }
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
