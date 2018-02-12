using System;
using System.Windows;
using System.IO.IsolatedStorage;
using System.IO;


namespace LXM_ctrl
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

        private void button_reg_addr_Click(object sender, RoutedEventArgs e)
        {
            settings_data.reg_addr = reg_addr.Text; // сохр. адр. регистра
        }

        private void button_IPandPort_Click(object sender, RoutedEventArgs e)
        {
            settings_data.IP = IP.Text;
            settings_data.port = Convert.ToInt32(port.Text);

            var modbus_transport_instance = modbus_transport.getInstance();

            modbus_transport_instance.Stop();
     
            modbus_transport_instance.IpAdress = settings_data.IP;
            modbus_transport_instance.Port = settings_data.port;
            modbus_transport_instance.Start();
        }

        private void window_setting_Loaded(object sender, RoutedEventArgs e)
        {

            default_label.Visibility = Visibility.Hidden;
            try
            {
                IP.Text = settings_data.IP;
                port.Text = settings_data.port.ToString();
                reg_addr.Text = settings_data.reg_addr;
            }
            catch (Exception)
            {
                default_label.Visibility = Visibility.Visible;
            }
            
        }


    }
}
