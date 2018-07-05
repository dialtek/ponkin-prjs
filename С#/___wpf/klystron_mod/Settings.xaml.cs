using System;
using System.Windows;
using System.IO.IsolatedStorage;
using System.IO;


namespace klystron_mod
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

        private int textbox_format(string s)
        {
            int send_msg = 0;
            int hundreds = 0;
            int tens = 0;
            string[] buf;
            string temp = s;

            try
            {
                if (temp.Contains(",")) temp = temp.Replace(',', '.');

                if (temp.Contains("."))
                {
                    buf = temp.Split('.');
                    hundreds = Convert.ToInt32(buf[0]);
                    tens = Convert.ToInt32(buf[1]);
                    if (tens.ToString().Length > 1)
                        tens = Convert.ToInt32(tens.ToString().Substring(0, 1));

                    send_msg = (hundreds * 10) + tens;
                }
                else send_msg = (temp == "") ? Convert.ToInt32("error") : Convert.ToInt32(temp)*10;
            }
            catch
            {
                send_msg = -1;   
            }
            return send_msg;
        }

        private void button_delay_Click(object sender, RoutedEventArgs e)
        {
            int send_msg;
            int register = 1009;

            send_msg = textbox_format(rf_delay_tb.Text);
            if (send_msg == -1) MessageBox.Show("ошибка ввода");
            else
            {
                send_msg = (send_msg >= 500) ? 500 : send_msg;
                send_msg = (send_msg <= 0) ? 0 : send_msg;

                QueueElement msg_ = new QueueElementW(Convert.ToInt32(8), register, send_msg);
                modbus_transport.getInstance().GetMsgFromDevice(msg_);
            }
        }

        private void button_with_Click(object sender, RoutedEventArgs e)
        {
            int send_msg;
            int register = 1010;

            send_msg = textbox_format(rf_with_tb.Text);
            if (send_msg == -1) MessageBox.Show("ошибка ввода");
            else
            {
                send_msg = (send_msg >= 500) ? 500 : send_msg;
                send_msg = (send_msg <= 0) ? 0 : send_msg;

                QueueElement msg_ = new QueueElementW(Convert.ToInt32(8), register, send_msg);
                modbus_transport.getInstance().GetMsgFromDevice(msg_);
            }
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
            string delay = "";
            string with = "";

            int hundreds = 0;
            int tens = 0;

            default_label.Visibility = Visibility.Hidden;
            try
            {
                hundreds = Convert.ToInt32(settings_data.rf_delay) / 10;           // уст. значения задержки
                tens = Convert.ToInt32(settings_data.rf_delay) - hundreds*10;      // уст. длит.
                delay = hundreds.ToString() + "." + tens.ToString();                // приводим к формату 0.0

                hundreds = Convert.ToInt32(settings_data.rf_with) / 10;            // уст. значения длит.
                tens = Convert.ToInt32(settings_data.rf_with) - hundreds*10;       // уст. длит.
                with = hundreds.ToString() + "." + tens.ToString();                 // приводим к формату 0.0
            }
            catch (Exception)
            {
                default_label.Visibility = Visibility.Visible;
                delay = "20";
                with = "10";
            }
            rf_delay_tb.Text = delay;
            rf_with_tb.Text = with;
            rf_level_tb.Text = settings_data.rf_level;
            IP.Text = settings_data.IP;
            port.Text = settings_data.port.ToString();
        }

        private void button_rf_lvl_Click(object sender, RoutedEventArgs e)
        {
            // установка порга срабатывания индикации выхода СВЧ

            int send_msg = 0;
            int register = 1014;
            try
            {
                send_msg = (rf_level_tb.Text == "") ? Convert.ToInt32("error") : Convert.ToInt32(rf_level_tb.Text);
                send_msg = (send_msg >= 1000) ? 1000 : send_msg;
                send_msg = (send_msg <= 50) ? 50 : send_msg;
            }
            catch
            {
                MessageBox.Show("ошибка ввода");
                return;
            }

            QueueElement msg_ = new QueueElementW(Convert.ToInt32(8), register, send_msg);
            modbus_transport.getInstance().GetMsgFromDevice(msg_);
        }
    }
}
