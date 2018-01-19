using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using ObooltNet;

namespace TCP_read
{
    public partial class Form1 : Form
    {
        NetConnection oclient = new NetConnection();
        //Initialize the event driven client
        //EventDrivenTCPClient client = new EventDrivenTCPClient(IPAddress.Parse("192.168.127.254"),4001,true);
        //static TcpClient xport = new TcpClient();   // создаем новый класс икспорт - глобальная переменная

        public delegate void UpdateText(string str);

        //String xport_text;                   // строка
        //NetworkStream xport_rx_data;
        byte[] data = new byte[1024]; // Reads NetworkStream into a byte buffer.

        private void ChangeTextBox(string txt)
        {
            if (richTextBox.InvokeRequired)
            {
                Invoke(new UpdateText(ChangeTextBox), new object[] { txt });
            }
            else
            {

                richTextBox.Text += txt + Environment.NewLine;
            }
        }


        public Form1()
        {
            InitializeComponent();
            statusbox.Text = "";

        }

        public void Form1_Load(object sender, EventArgs e)
        {
            //Initialize the events


            oclient.OnDataReceived += oclient_OnDataReceived;
            //client.DataReceived += new EventDrivenTCPClient.delDataReceived(client_DataReceived); ;
            //client.ConnectionStatusChanged += new EventDrivenTCPClient.delConnectionStatusChanged(client_ConnectionStatusChanged);
        }

        void oclient_OnDataReceived(object sender, NetConnection connection, byte[] e)
        {
           
        }

        void client_ConnectionStatusChanged(EventDrivenTCPClient sender, EventDrivenTCPClient.ConnectionStatus status)
        {//Check if this event was fired on a different thread, if it is then we must invoke it on the UI thread

            ChangeTextBox(status.ToString());
        }

        void client_DataReceived(EventDrivenTCPClient sender, object data)
        {
            ChangeTextBox(data.ToString());
        }


        public void button1_Click(object sender, EventArgs e)
        {
           // client.ReceiveTimeout = 100;
            //client.SendTimeout = 100;
            //client.Connect();
        }

        public void Disconnect_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[8];
            cmd[0] = 0x4D; 
            cmd[1] = 0x01; 
            cmd[2] = 0x00; 
            cmd[3] = 0x00;
            cmd[4] = 0x00; 
            cmd[5] = 0x00;
            cmd[6] = 0x00; 
            cmd[7] = 0x00;

            string str = Encoding.Default.GetString(cmd);

            client.Send(cmd);

        }

        private void ConStateB_Click(object sender, EventArgs e)
        {
           // richTextBox.Text += client.ConnStatusReal.ToString() + Environment.NewLine;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
