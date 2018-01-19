using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace MDR32FL
{
    enum MCU
    {   // команды обмена данными по UART
        cmd_baud = 0x42, // 'B'
        cmd_load = 0x4C, // 'L'
        cmd_cr   = 0x0D,
        cmd_vfy  = 0x59, // 'Y'
        cmd_run  = 0x52  // 'R'
    };
    
    public partial class Form1 : Form
    {
        int x=0;
        int y=1;
        bool rs_fl = false;
        int BaudRate = 9600;
        static string rx_buf = "          ";
        System.IO.Ports.SerialPort rs_port;
        char[] txdbuf = new char[25];                                                      // массив из 25 байта для обмена с МК  
        byte[] comand_data = new byte[5];
        int ReadCounter = 0;
        UInt32 Uadr, Udata;
        Int64 Sadr, Sdata;
        byte RxData;
        byte[] RxDataArr = new byte[10];
        int iterator = 0;
        

    public Form1()
    {
        InitializeComponent();
        timer1.Interval = 800;

        //for (int i = 0; i < 25; i++) { txdbuf[i] = 0x00; }

        Program_btn.Enabled = true;
        port_close.Enabled = true;
        search_hex_btn.Enabled = true;

        PortList.DataSource = System.IO.Ports.SerialPort.GetPortNames();

        if (PortList.Items.Count == 0) { StatusBox.Text = "Нет активных COM-портов"; }

        else
        {

            rs_port = new System.IO.Ports.SerialPort(PortList.Text, BaudRate,
                System.IO.Ports.Parity.None,
                8,
                 System.IO.Ports.StopBits.One);
            //rs_port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);    // создаем событие получения байт
        }
    }

   
   public void InitRs()                           
   {
        if (rs_port.IsOpen == true)
             rs_port.Close();
        rs_port.Open();
        rs_port.DiscardInBuffer();
        rs_port.DataReceived += rs_port_DataReceived;
        //timer1.Start();
    }

   void rs_port_DataReceived(object sender, SerialDataReceivedEventArgs e)
   {  
       //rx_buf = rs_port.Readexisting();
       RxData = (byte)rs_port.ReadByte();
   }

   //public void DataReceivedHandler( object sender,SerialDataReceivedEventArgs e)
   //{
   //    // событие возникает каждый раз при появлении байта в буфере чтения rs_port

   //    Port_read_text.Text = "есть " + rs_port.ReadExisting();

   //}

    private void port_open_Click(object sender, EventArgs e)
    {
     
    }

    private void port_close_Click(object sender, EventArgs e)
    {
        //rs_port.DiscardOutBuffer();
        rs_port.Close();
        timer1.Stop();
        Program_btn.Enabled = false;
        port_close.Enabled = false;
        search_hex_btn.Enabled = true;
        status_pic.Image = status_pic.ErrorImage;
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
        
        //if (y == 1) y = 2;
       // else y = 1;

       // rs_port.Write(Convert.ToString(y));
       // Port_text2send.Text = Convert.ToString(y);
       // System.Threading.Thread.Sleep(2);

      //  if (rs_port.bytesToRead > 0)
      //  {
       //     Port_read_text.Text = rs_port.ReadExisting();
       //     rs_port.DiscardOutBuffer();
       // }

       // x++;
      
    }

    private void Form1_FormClosed(object sender, FormClosedEventArgs e)
    {
        if (PortList.Items.Count != 0)
        {
            if (rs_port.IsOpen == true) rs_port.Close();
        }
    }

    private void Program_btn_Click(object sender, EventArgs e)
    {
 /*----------------------------------------------------------------------------*/ // синхронизация       
        InitRs();                                                               // инициализация COM-порта
        Program_btn.Enabled = true;
        if (rs_port.IsOpen == true)
        {
            StatusBox.Text = PortList.Text + " готов!";
            status_pic.Image = status_pic.InitialImage;
            port_close.Enabled = true;
            search_hex_btn.Enabled = true;        
            
            for (int i = 0; i < 512; i++) { rs_port.Write(txdbuf,0,1); }        // запись 512 байт в порт для синхронизации тактовой частоты обмена
            while (RxDataArr[2] != '>')// чтение ответа МК
            {
                RxDataArr[iterator] = RxData;
                ReadCounter++;
                Thread.Sleep(1);
                iterator++;
                MessageBox.Show(RxData.ToString());
                //if (ReadCounter > 20) break;
                
            }
            //MessageBox.Show(iterator.ToString());
            ReadCounter = 0;

            //if (rx_buf.Length > 2 && rx_buf[2] == '>')
            if ((char)RxDataArr[2] == '>')
                    {
                     Port_read_text.Text = RxDataArr[0].ToString() + RxDataArr[1].ToString() + RxDataArr[2].ToString();;
                     StatusBox.Text = "Успешная синхронизация с МК!";
                     //rs_fl = true;                                                        // установка флага успешной синхронизации
                    }
                 else 
            {
                StatusBox.Text = "Ошибка синхронизации"; 
            } 
                
                    //for (int i = 0; i < 512; i++) { rs_port.Write(txdbuf, 0, 1); }     // запись 512 байт в порт для синхронизации тактовой частоты обмена
                    //while (rx_buf.Length != 3)// чтение ответа МК
                    //{
                    //    ReadCounter++;
                    //    Thread.Sleep(1);
                    //    if (ReadCounter > 20) break;

                    //}
                    //ReadCounter = 0;

                    //if (rx_buf.Length > 2 && rx_buf[2] == '>')
                    //  {
                    //      Port_read_text.Text = rx_buf;
                    //      StatusBox.Text = "Успешная синхронизация с МК!";
                    //      rs_fl = true;                                                    // установка флага успешной синхронизации
                    //  }
                      //else { StatusBox.Text = "Ошибка синхронизации..."; }
                      //}                   
            
           
        }

        //else { StatusBox.Text = "Ошибка открытия порта"; }
/*----------------------------------------------------------------------------*/ // синхронизация    

/*----------------------------------------------------------------------------*/ // уст. скорости обмена    
        if (rs_fl == true) // соед. с мк установлено
        {   
            rs_fl = false;
            comand_data[0] = (byte)MCU.cmd_baud;
            comand_data[1] = 0x00;
            comand_data[2] = 0xc2;
            comand_data[3] = 0x01;
            comand_data[4] = 0x00;
            rs_port.Write(comand_data, 0, 5);
            while (rx_buf.Length != 1)
            {
                ReadCounter++;
                Thread.Sleep(1);
                if (ReadCounter > 20) break;

            }
            ReadCounter = 0;

            rs_port.BaudRate = 115200;
            comand_data[0] = (byte)MCU.cmd_cr;
            rs_port.Write(comand_data, 0, 1);
            while (rx_buf.Length != 3) 
            {
                ReadCounter++;
                Thread.Sleep(1);
                if (ReadCounter > 20) break;
            
            }
            ReadCounter = 0;

            if (rx_buf.Length > 2 && rx_buf[2] == '>')
                       
            { Port_read_text.Text = rx_buf;
            StatusBox.Text = "Успешная синхронизация!";
                rs_fl = true;                                                    // установка флага успешной синхронизации
            }



            comand_data[0] = (byte)MCU.cmd_cr;
            rs_port.Write(comand_data, 0, 1);
            while (rx_buf.Length != 3)
            {
                ReadCounter++;
                Thread.Sleep(1);
                if (ReadCounter > 20) break;

            }
            ReadCounter = 0;

            comand_data[0] = (byte)'E';
            rs_port.Write(comand_data, 0, 1);
            Thread.Sleep(1000);
            while (rx_buf.Length != 9) 
            {
                ReadCounter++;
                Thread.Sleep(1);
                if (ReadCounter > 10) break;
            
            }
            byte a,b,c,d;

            if ((rx_buf.Length > 8) && (rx_buf[0] == 'E'))
            { 
            a = (byte)rx_buf[1];
            b = (byte)rx_buf[2];
            c = (byte)rx_buf[3];
            d = (byte)rx_buf[4];
                StatusBox.Text = "ок";
            }
            else StatusBox.Text = "error l=" + rx_buf.Length.ToString() ;
   
                //Sadr = rx_buf[1] + ((rx_buf[2]) << 8) + ((rx_buf[3]) << 16) + ((rx_buf[4]) << 24);
                //data = (byte)rx_buf[5] + (((byte)rx_buf[6]) << 8) + (((byte)rx_buf[7]) << 16) + (((byte)rx_buf[8]) << 24);
                //Uadr = Convert.ToUInt32(Sadr);
            //if (Uadr == 0x08020000) //&& (data == 0xffffffff))
           // {
           //     StatusBox.Text = "Память очищена";
           // }
            Port_read_text.Text = rx_buf + "z";
        }
       }
    }

}

