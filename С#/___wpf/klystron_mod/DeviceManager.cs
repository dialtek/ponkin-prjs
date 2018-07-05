using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;
using System.Threading;
using System.Windows.Threading;
using System.Windows.Controls.Primitives;


namespace klystron_mod
{
    class DeviceManager
    {
        MainWindow _form;
        StatusBar mainStatusBar;
        StatusBarItem connect_status;
        StatusBarItem error_status, IP_status;


        public Dictionary<string, Device> devices;
        public DeviceIP702 device_IP702C;
        public List<string> disabled_devices = new List<string>();
        
        private List<string> error_src = new List<string>();

        private static DeviceManager instance;

        private DeviceManager()
        {
            devices = new Dictionary<string, Device>();
            
        }

        public void CreateDevices(MainWindow form)
        {
            _form = form;

            // блоки запуска HV
            string id = "24"; // 7
            int shift = 0;
            int shift_vert = 3;

            var device_0 = new DevicePBF(id, shift, shift_vert, "U1", SendModbus_Msg);
            device_0.CreateControls(_form);
            devices.Add(id, device_0);

            id = "8";
            shift = 0;
            shift_vert = 13;

            var device_1 = new DevicePBF(id, shift, shift_vert, "U2", SendModbus_Msg);
            device_1.CreateControls(_form);
            devices.Add(id, device_1);

            // задержки
            id = "7";
            shift = 32;
            shift_vert = 8;

            var device_2 = new DeviceSync(id, shift, shift_vert, "sync", SendModbus_Msg);
            device_2.CreateControls(_form);
            devices.Add(id, device_2);

            shift = 4;
            shift_vert = 22;

            device_IP702C = new DeviceIP702(shift, shift_vert, "IP702C", SendIP702_Msg);
            device_IP702C.CreateControls(_form);

            CreateStatusBar(_form);

            LoadState();
        }

        public static DeviceManager getInstance()
        {
            if (instance == null)
                instance = new DeviceManager();
            return instance;
        }

        public void SendModbus_Msg(object sender, QueueElement msg)
        {
            modbus_transport.getInstance().GetMsgFromDevice(msg);
        }

        public void SendIP702_Msg(object sender, Dictionary<string, int> msg)
        {
            IP702_transport.getInstance().GetMsgFromDevice(msg);
        }

        public void GetMsgFrom_modbus_transport(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
                /// получен ответ
                var device_id = msg.Key["id"].ToString();
                string error_msg = "Нет связи: ";

                // ошибка чтения, пишем в статусную строку
                if (msg.Value[0] == "r/w error")
                {
                    if (!error_src.Contains(device_id)) error_src.Add(device_id);
                }
                else
                {
                    if (error_src.Contains(device_id))
                        error_src.Remove(device_id);
                    // передаем посылку устройствам если было прочитано более 12 регистров(как и было запрошено)
                    if(msg.Value.Count > 12) devices[device_id].GetMsgFromDevice(this, msg);
                }

                _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)delegate ()
                {
                    if (error_src.Count > 0)
                    {
                        error_status.Content = error_msg;

                        foreach (string str in error_src)
                        {
                            error_status.Content += "  ID " + str;
                        }
                        error_status.Background = Brushes.Coral;
                    }
                    else
                    {
                        error_status.Content = "Ок";
                        error_status.Background = Brushes.LimeGreen;
                    }
                });
            

            //catch(Exception)
           // {
               // MessageBox.Show("Не корректно подключены или настроены устройства");
           //     return;
           // }
        }

        public void GetMsgFrom_IP702_transport(object sender, string[] msg)
        {
            /// получен ответ
            
            string error_msg = "Нет связи: ";
            device_IP702C.GetMsgFromDevice(sender,msg);
        }

        public void StartConnection(string IP, int port)
        {
            // modbus instance
            var modbus_transport_instance = modbus_transport.getInstance();

            modbus_transport_instance.IpAdress = IP;
            modbus_transport_instance.Port = port;
            modbus_transport_instance.dequeue_period = 75;

            modbus_transport_instance.OnRwComplete = GetMsgFrom_modbus_transport;
            modbus_transport_instance.OnEmptyQueue = modbus_queue_empty;
            modbus_transport_instance.Start();

            modbus_transport_instance.OnChangeConnectionStatus += ChangeStatusConnect;
            modbus_transport_instance.OnException += ChangeStatusError;
            modbus_queue_empty(this, "tmp");
            // IP702 instance
            var IP702_transport_instance = IP702_transport.getInstance();
            IP702_transport_instance.IpAdress = "192.168.127.254";
            IP702_transport_instance.Port = 4001;
            IP702_transport_instance.read_period = 500;
            IP702_transport_instance.Start();

            IP702_transport_instance.OnRwComplete += GetMsgFrom_IP702_transport;
            IP702_transport_instance.OnChangeConnectionStatus += IP702_transport_con_status;
        }

        public void IP702_transport_con_status(object sender, bool status_connection)
        {
            _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
            (ThreadStart)delegate ()
            {
                IP_status.Content = (status_connection) ? "ИП702С подключен" : "Нет связи, попытка установить связь с ИП702С";
                if (status_connection)
                    IP_status.Background = Brushes.LimeGreen;
                else
                    IP_status.Background = Brushes.Coral;
            });
        }

        public void ChangeStatusConnect(object sender, bool status_connection)
        {

            _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
            (ThreadStart)delegate ()
            {
                connect_status.Content = (status_connection) ? "Modbus master подключен" : "Нет связи, попытка установить связь Modbus";
                if (status_connection)
                {
                    connect_status.Background = Brushes.LimeGreen;
                    //error_status.Visibility = Visibility.Visible; 
                }
                else
                {
                    connect_status.Background = Brushes.Coral;
                    error_status.Background = Brushes.Coral;
                    error_status.Content = "";
                    //error_status.Visibility = Visibility.Hidden;
                }
            });
            
            
            //mainStatusBar.Items.Add(connect_status);
            //_form.MainGrid.Children.Add(mainStatusBar);
        }

        public void ChangeStatusError(object sender, string msg)
        {
            _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
            (ThreadStart)delegate ()
            {
                //error_status.Content = msg;
            });
        }

        public void CreateStatusBar(MainWindow form)
        {
            mainStatusBar = new StatusBar();
            mainStatusBar.Height = 25;
            mainStatusBar.FontSize = 12;
            mainStatusBar.Background = new SolidColorBrush(Colors.LightGray);
            mainStatusBar.VerticalAlignment = VerticalAlignment.Bottom;


            connect_status = new StatusBarItem();
            connect_status.Content = "Connect";
            connect_status.HorizontalAlignment = HorizontalAlignment.Center;
            connect_status.HorizontalContentAlignment = HorizontalAlignment.Center;

            connect_status.Width = _form.MainGrid.ActualWidth / 3;
            mainStatusBar.Items.Add(connect_status);

            var sep = new Separator();
            sep.HorizontalAlignment = HorizontalAlignment.Center;
            mainStatusBar.Items.Add(sep);

            error_status = new StatusBarItem();
            //error_status.Content = "Error";
            error_status.HorizontalAlignment = HorizontalAlignment.Left;
            error_status.HorizontalContentAlignment = HorizontalAlignment.Center;

            error_status.Width = _form.MainGrid.ActualWidth / 3;
            mainStatusBar.Items.Add(error_status);

            //--- IP702C
            var IPsep = new Separator();
            sep.HorizontalAlignment = HorizontalAlignment.Right;
            mainStatusBar.Items.Add(IPsep);

            IP_status = new StatusBarItem();
            IP_status.HorizontalAlignment = HorizontalAlignment.Right;
            IP_status.HorizontalContentAlignment = HorizontalAlignment.Center;

            IP_status.Width = _form.MainGrid.ActualWidth / 3;
            mainStatusBar.Items.Add(IP_status);

            _form.MainGrid.Children.Add(mainStatusBar);
        }

        public void modbus_queue_empty(object sender, string msg)
        {
            foreach(var device in devices.Where(dev => dev.Value.IsEnabled == true))
            {
                //for (int i = 0; i < 1; i++)
                //{
                   // чтение 13 регистров всех устройств
                    QueueElement queue = new QueueElementR(Convert.ToInt32(device.Key), 1000, 15);
                    modbus_transport.getInstance().GetMsgFromDevice(queue);
                //}
            }
        }

        public void SaveState()
        {
            foreach (var device in devices)
            {
                //device.Value.SaveState();
            }
        }

        public void LoadState()
        {
            foreach (var device in devices)
            {
                //device.Value.LoadState();
            }
        }

    }
}
