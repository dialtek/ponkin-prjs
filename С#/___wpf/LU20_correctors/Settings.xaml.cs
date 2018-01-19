using System;
using System.Windows;
using System.Threading;
using System.IO.IsolatedStorage;
using System.IO;


namespace LU20_correctors_ctrl
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

        private void button_output_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            try
            {
                //send_msg = (int)extract_volt.Value;
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
            string[] s = new string[10];
            try
            {
                s[0] = settings_data.IP;
                s[1] = settings_data.port.ToString();
                s[2] = settings_data.VDK_FI_Vmax;
            }
            catch
            {

            }
            IP.Text = s[0];
            port.Text = s[1];
            //VDK_FI_U.Value = Convert.ToInt32(s[2]);
            //VDK_FI_U.Value = Convert.ToInt32(s[2]);
            //VDK_FI_U.Value = Convert.ToInt32(s[2]);
            //VDK_FI_U.Value = Convert.ToInt32(s[2]);
            //VDK_FI_U.Value = Convert.ToInt32(s[2]);
            //VDK_FI_U.Value = Convert.ToInt32(s[2]);
        }

        private void button_VDK_FI_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            int id = 61;
            try
            {
                send_msg = (int)VDK_FI_U.Value;
                register = 1008;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(id, register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_GDK_FI_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            int id = 62;
            try
            {
                send_msg = (int)GDK_FI_U.Value;
                register = 1008;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(id, register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_VDK_1_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            int id = 63;
            try
            {
                send_msg = (int)VDK_1_U.Value;
                register = 1008;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(id, register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_GDK_1_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            int id = 64;
            try
            {
                send_msg = (int)GDK_1_U.Value;
                register = 1008;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(id, register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_VDK_6_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            int id = 65;
            try
            {
                send_msg = (int)VDK_6_U.Value;
                register = 1008;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(id, register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }

        private void button_GDK_6_Click(object sender, RoutedEventArgs e)
        {
            int send_msg = 0;
            int register = 0;
            int id = 66;
            try
            {
                send_msg = (int)GDK_6_U.Value;
                register = 1008;
            }
            catch
            {
                MessageBox.Show("Ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(id, register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }
    }
}
