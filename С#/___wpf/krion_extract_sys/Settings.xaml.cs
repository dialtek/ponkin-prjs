using System;
using System.Windows;
using System.Threading;
using System.IO.IsolatedStorage;
using System.IO;


namespace extract_system
{

    /// <summary>
    /// Interaction logic for Settings.xaml
    /// </summary>
    public partial class WSettings : Window
    {
        public WSettings()
        {
            InitializeComponent();
        }

        private void button_extr_voltage_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            try
            {
                send_msg = (int)extract_volt.Value;
                register = 1000;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(Convert.ToInt32(20), register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_fast_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            try
            {
                send_msg = (int)qe_time.Value;
                register = 1012;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(Convert.ToInt32(30), register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_IPandPort_Click(object sender, RoutedEventArgs e)
        {
            

            // write the settings file
            // Check if the file already exists in isolated storage.
            IsolatedStorageFile isoStore =
              IsolatedStorageFile.GetStore(IsolatedStorageScope.User
              | IsolatedStorageScope.Assembly, null, null);

            string[] fileNames = isoStore.GetFileNames(settings_data.storage_name);

            settings_data.IP = IP.Text;
            settings_data.port = Convert.ToInt32(port.Text);

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
                writer.Close();
            }
            catch (Exception)
            {

            }

            var modbus_transport_instance = modbus_transport.getInstance();

            modbus_transport_instance.Stop();
     
            modbus_transport_instance.IpAdress = settings_data.IP;
            modbus_transport_instance.Port = settings_data.port;
            modbus_transport_instance.Start();
        }

        private void window_setting_Loaded(object sender, RoutedEventArgs e)
        {
            extract_volt.Text = settings_data.DCHV_V; // уст. значения напряжения БФВН вывода
            qe_time.Text = settings_data.q_extr_time; // уст. время быстрого вывода
            IP.Text = settings_data.IP;
            port.Text = settings_data.port.ToString();
            //ion_cool_voltage.Text = settings_data.ion_cool_V;
        }

        private void button_ion_cool_voltage_Click(object sender, RoutedEventArgs e)
        {
            // уст. напряжения БФВН для модулятора ион. охлаждения
            int send_msg = 0;
            int register = 0;
            try
            {
                send_msg = (int)ion_cool_voltage.Value;
                register = 1000;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(Convert.ToInt32(24), register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);

        }
    }
}
