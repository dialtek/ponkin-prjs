using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.IO;
using System.Collections.Generic;
using System.Linq;


namespace modbus_queue_test
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        void start_new_session()
        {
            var modbus_transport_instance = modbus_transport.getInstance();
            modbus_transport_instance.IpAdress = "192.168.127.254";
            modbus_transport_instance.Port = 4001;
            modbus_transport_instance.dequeue_period = 50;
            for (int i = 0; i < 2000; i++) modbus_transport_instance.push_queue(queue);
            modbus_transport_instance.OnRwComplete = GetMsgFrom_transport;
            modbus_transport_instance.OnEmptyQueue = modbus_queue_empty;
            modbus_transport_instance.OnChangeConnectionStatus = modbus_con_status;
            modbus_transport_instance.Start();  
        }
         QueueElement queue = new QueueElementR(3, 1000, 20);
        
        public MainWindow()
        {
            InitializeComponent();
        }
        //-----------------------------------------------------------------

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            start_new_session();
        }

        private void async_read_text(string text)
        {
            // делегат для обращения к элементу из др. потока

            this.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
            (ThreadStart)delegate ()
            { label.Content = text; });
        }

        private void async_write_text(string text)
        {
            // делегат для обращения к элементу из др. потока

            this.Dispatcher.BeginInvoke(DispatcherPriority.Normal,
            (ThreadStart)delegate()
            { label_Copy.Content = text; });
        }
        //----------
        private void button_Click(object sender, RoutedEventArgs e)
        {
            start_new_session();
            async_write_text("");
        }
        public void GetMsgFrom_transport(object sender, KeyValuePair<Dictionary<string, int>, List<string>> msg)
        {
            try
            {
                var modbus_transport_inst = modbus_transport.getInstance();
                async_read_text(msg.Value[5] + "  " + msg.Value[6] + "  " + modbus_transport_inst.queue_count.ToString() +
                    " " + modbus_transport_inst.connected.ToString() );
            }
            catch
            {
                MessageBox.Show("Не корректно подключены или настроены устройства 1");
                return;
            }
        }

        public void modbus_queue_empty(object sender, string msg)
        {
            try
            {
                async_write_text(msg);
                Thread.Sleep(1000);
                async_write_text("");
                var modbus_transport_ins = modbus_transport.getInstance();
                for (int i = 0; i < 100; i++) modbus_transport_ins.push_queue(queue);
            }
            catch
            {
                MessageBox.Show("Не корректно подключены или настроены устройства 2");
                return;
            }
        }

        public void modbus_con_status(object sender, bool status)
        {
            try
            {
                async_write_text(status.ToString());
                Thread.Sleep(1000);
                async_write_text("");
            }
            catch
            {
                MessageBox.Show("Не корректно подключены или настроены устройства 3");
                return;
            }
        }
        

    }
}
