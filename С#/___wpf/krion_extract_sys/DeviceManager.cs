using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;
using System.Threading;
using System.Windows.Threading;
using System.Windows.Controls.Primitives;


namespace extract_system
{
    class DeviceManager
    {
        MainWindow _form;
        StatusBar mainStatusBar;
        StatusBarItem connect_status;
        StatusBarItem error_status;

        public Dictionary<string, Device> devices;
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

            string id = "1";
            int shift = 0;
            int shift_vert = 4;

            var device_0 = new DevicePBF(id, shift, shift_vert, "C2", SendMessage);
            device_0.CreateControls(_form);
            devices.Add(id, device_0);

            id = "2";
            shift_vert = 24;

            var device_1 = new DevicePBF(id, shift, shift_vert, "C6", SendMessage);
            device_1.CreateControls(_form);
            devices.Add(id, device_1);

            id = "3";
            shift_vert = 44;

            var device_2 = new DevicePBF(id, shift, shift_vert, "C24", SendMessage);
            device_2.CreateControls(_form);
            devices.Add(id, device_2);

            id = "21";
            shift_vert = 68;
            // блок уст. потенциала структуры
            var device_6 = new DevicePBF(id, shift, shift_vert, "U с.", SendMessage);
            device_6.CreateControls(_form);
            devices.Add(id, device_6);


            id = "23";
            shift = 10;
            shift_vert = 68;
            //// L1
            //var device_7 = new DevicePBF(id, shift, shift_vert, "L1", SendMessage);
            //device_7.CreateControls(_form);
            //devices.Add(id, device_7);

            //id = "7";
            //shift = 10;
            //shift_vert = 90;
            //// Модулятор
            //var device_8 = new DevicePBF(id, shift, shift_vert, "Мод", SendMessage);
            //device_8.CreateControls(_form);
            //devices.Add(id, device_8);

            id = "20";
            shift = 20;
            shift_vert = 1;

            var device_3 = new DeviceDCHV(id, shift, shift_vert, "Вывод", SendMessage);
            device_3.CreateControls(_form);
            devices.Add(id, device_3);

            id = "30";
            shift = 1;
            shift_vert = 1;

            var device_4 = new DeviceExtModule(id, shift, shift_vert, SendMessage);
            device_4.CreateControls(_form);
            devices.Add(id, device_4);

            id = "40";              // первый ключ делителя, было 40 для ИО
            shift = 10;
            //shift_vert = 5;
            List<string> R_list = new List<string>() { "200 R", "1 k", "2 k" };  // список резисторов для коммутации

            var device_5 = new DeviceDividerKey(id, shift, shift_vert, SendMessage, "С2", "C6", "C24", R_list); // было С22 для ИО
            device_5.CreateControls(_form);
            devices.Add(id, device_5);

            device_4._slow_mode_on += device_5.EventSlowModeOn;

            // ion cooling devices..////////////////////////////////////////////////////////////////////////////
            //id = "26";          // C26
            //shift = 20;
            //shift_vert = 68;

            //var device_9 = new DevicePBF(id, shift, shift_vert, "C26", SendMessage);
            //device_9.CreateControls(_form);
            //devices.Add(id, device_9);

            //id = "24";          // БФВН модулятора ИО
            //shift = 44;
            //shift_vert = 1;
            //var device_10 = new DeviceDCHV(id, shift, shift_vert, "C25", SendMessage);
            //device_10.CreateControls(_form);
            //devices.Add(id, device_10);

            //id = "31";          // Модулятор ИО
            //shift = 22;
            //shift_vert = 1;
            //var device_11 = new DeviceModIonCool(id, shift, shift_vert, SendMessage);
            //device_11.CreateControls(_form);
            //devices.Add(id, device_11);


            //id = "42";         // второй ключ делителя
            //shift = 22;
            //R_list = new List<string>() { "1 k", "30 k", "82 k" };  // список резисторов для коммутации

            //var device_12 = new DeviceDividerKey(id, shift, shift_vert, SendMessage, "С23", "C25", "C26", R_list);
            //device_12.CreateControls(_form);
            //devices.Add(id, device_12);

            // ------ 
            CreateStatusBar(_form);

            LoadState();
        }

        public static DeviceManager getInstance()
        {
            if (instance == null)
                instance = new DeviceManager();
            return instance;
        }

        public void SendMessage(object sender, QueueElement msg)
        {
            modbus_transport.getInstance().GetMsgFromDevice(msg);
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
                    devices[device_id].GetMsgFromDevice(this, msg);
                }
           
                _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
                (ThreadStart)delegate ()
                {
                    if (error_src.Count > 0)
                    {
                        error_status.Content = error_msg;

                        foreach (string str in error_src)
                        {
                            error_status.Content += "  ID" + str;
                        }
                        error_status.Background = Brushes.Coral;
                    }
                    else
                    {
                        error_status.Content = "Работа в штатном режиме";
                        error_status.Background = Brushes.LimeGreen;
                    }
                });

            
            //catch (Exception)
            //{
            //    MessageBox.Show("Не корректно подключены или настроены устройства");
            //    return;
            //}
        }

        public void StartConnection(string IP, int port)
        {
            var modbus_transport_instance = modbus_transport.getInstance();

            modbus_transport_instance.IpAdress = IP;
            modbus_transport_instance.Port = port;
            //modbus_transport_instance.dequeue_period = 20;

            modbus_transport_instance.OnRwComplete = GetMsgFrom_modbus_transport;
            modbus_transport_instance.OnEmptyQueue = modbus_queue_empty;
            modbus_transport_instance.Start();

            modbus_transport_instance.OnChangeConnectionStatus += ChangeStatusConnect;
            modbus_transport_instance.OnException += ChangeStatusError;

            modbus_queue_empty(this, "tmp");
        }

        public void ChangeStatusConnect(object sender, bool status_connection)
        {

            _form.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
            (ThreadStart)delegate ()
            {
                connect_status.Content = (status_connection) ? "Соединение установлено" : "Нет связи, попытка установить связь";
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
            mainStatusBar.Background = new SolidColorBrush(Colors.LightGray);
            mainStatusBar.VerticalAlignment = VerticalAlignment.Bottom;


            connect_status = new StatusBarItem();
            connect_status.Content = "Connect";
            connect_status.HorizontalAlignment = HorizontalAlignment.Right;
            connect_status.HorizontalContentAlignment = HorizontalAlignment.Center;

            connect_status.Width = _form.MainGrid.ActualWidth / 2;
            mainStatusBar.Items.Add(connect_status);


            var sep = new Separator();
            sep.HorizontalAlignment = HorizontalAlignment.Center;
            mainStatusBar.Items.Add(sep);

            error_status = new StatusBarItem();
            //error_status.Content = "Error";
            error_status.HorizontalAlignment = HorizontalAlignment.Right;
            error_status.HorizontalContentAlignment = HorizontalAlignment.Center;

            error_status.Width = _form.MainGrid.ActualWidth / 2;
            mainStatusBar.Items.Add(error_status);


            _form.MainGrid.Children.Add(mainStatusBar);
        }

        public void modbus_queue_empty(object sender, string msg)
        {
            foreach(var device in devices.Where(dev => dev.Value.IsEnabled == true))
            {
                   // чтение 13 регистров всех устройств
                    QueueElement queue = new QueueElementR(Convert.ToInt32(device.Key), 1000, 19);
                    modbus_transport.getInstance().GetMsgFromDevice(queue);
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
