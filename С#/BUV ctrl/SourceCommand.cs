using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BUV_ctrl
{
    /// <summary>
    /// Команды для обращения к источнику питания ИП 701С
    /// </summary>
    /// 
    class SourceCommand
    {
        private byte[] CmdBuf = new byte[10]; // буфер команды для отправки

        private int count = 0;

        /// <summary>
        /// Задать предварительное значение напряжения, В
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <param name="VoltageHexValue"></param>
        /// <returns></returns>
        public string SetVoltage(NetworkStream ns, StreamReader sr, string V2set)
        {
            char[] SourceAnswer = new char[10];
            CmdBuf[0] = 0x72;          // 'r'
            count = 0;
            double V2setNum;
            try
            {
                V2setNum = Convert.ToInt32(V2set);
            }
            catch (Exception e)
            {
                V2setNum = 0;
            }

            V2setNum = V2setNum / 0.125;  // приводим к отсчетам АЦП
            V2set = V2setNum.ToString();

            int mLenght = V2set.Length;

            switch (mLenght)
            {
                case 1: V2set = "000" + V2set; break;
                case 2: V2set = "00"  + V2set; break;
                case 3: V2set = "0"   + V2set; break;
                case 4: break;
            }

            CmdBuf[1] = (byte)V2set[0];
            CmdBuf[2] = (byte)V2set[1];
            CmdBuf[3] = (byte)V2set[2];
            CmdBuf[4] = (byte)V2set[3];

            try
            {
         
                ns.Write(CmdBuf, 0, 5); // отсылка команды в источник  
  
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 300) { break; }
                    count++;
                    Thread.Sleep(1);
                }

            }
            catch (Exception)
            {
                // действие при ошибке записи
                SourceAnswer[0] = 'W';
                MessageBox.Show("");
            }
            //try 
            //{   // чтение ответа источника
            //    sr.Read(SourceAnswer, 0, 2);  
            //}
            //catch (System.IO.IOException)
            //{
            //    // действие при ошибке чтения ответа
            //    SourceAnswer[0] = 'X';
            //}
           
            string status = new string(SourceAnswer);
            return status;
        }

        /// <summary>
        /// Чтение тока
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string GetCurrent(NetworkStream ns)
        {
            byte[] SourceAns = new byte[4];
            string retValue;
            string Result = "";
            double RdValueNum;
            byte cmd = 0x69; // "i";
            count = 0;

            StreamReader sr = new StreamReader(ns, Encoding.ASCII, true);
            sr.BaseStream.ReadTimeout = 300;

            try
            {
                ns.WriteByte(cmd); // отсылка команды в источник  
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 300) { break; }
                    count++;
                    Thread.Sleep(1);
                }
            }
            catch (Exception)
            {
                // действие при ошибке записи
               SourceAns[0] = 65;
            }
            try
            {   // чтение ответа источника
                Result = sr.ReadLine();

                RdValueNum = Convert.ToDouble(Result);
                RdValueNum = RdValueNum / 10;
                retValue = String.Format("{0:000.0}", RdValueNum);

            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
            }

            return retValue;

        }

        /// <summary>
        /// Чтение напряжения
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string GetVoltage(NetworkStream ns)
        {
            byte[] SourceAns = new byte[4];
            string retValue;
            string Result = "";
            double RdValueNum;
            byte cmd = 0x75; // "u";
            count = 0;

            StreamReader sr = new StreamReader(ns, Encoding.ASCII, true);
            sr.BaseStream.ReadTimeout = 300;

            try
            {
                ns.WriteByte(cmd); // отсылка команды в источник  
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 300) { break; }
                    count++;
                    Thread.Sleep(1);
                }

            }
            catch (Exception)
            {
                // действие при ошибке записи
                SourceAns[0] = 65;
            }
            try
            {   // чтение ответа источника
                Result = sr.ReadLine();

                RdValueNum = Convert.ToDouble(Result);
                RdValueNum = RdValueNum / 10;
                retValue = String.Format("{0:000.0}", RdValueNum);
            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
                //MessageBox.Show(ex.Message);
            }

            return retValue;

        }

        public string GetStatus(NetworkStream ns)
        {
            byte[] SourceAns = new byte[4];
            int retValInt;
            byte cmd = 0x73; // "s";
            string retValue = "";
            count = 0;

            StreamReader sr = new StreamReader(ns, Encoding.ASCII, true);
            sr.BaseStream.ReadTimeout = 300;

            try
            {
                ns.WriteByte(cmd); // отсылка команды в источник  
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 300) { break; }
                    count++;
                    Thread.Sleep(1);
                }

            }
            catch (Exception)
            {
                // действие при ошибке записи
                retValue = "********";
            }
            try
            {   // чтение ответа источника
                retValue = sr.ReadLine();
                retValInt = Convert.ToInt32(retValue);
                retValue = Convert.ToString(retValInt, 2).PadLeft(8, '0');
            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "--------";
            }
            return retValue;

        }

        /// <summary>
        /// Формирование команды для заряда конденсаторов
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string ChargeON(NetworkStream ns, StreamReader sr)
        {
            char[] SourceAnswer = new char[10];

            string retValue;
            count = 0;
            byte cmd = 0x61; //"a"

            try
            {
                ns.WriteByte(cmd); // отсылка команды в источник  
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 300) { break; }
                    count++;
                    Thread.Sleep(1);
                }
            }
            catch (Exception)
            {
                // действие при ошибке записи
                SourceAnswer[0] = 'A';
            }
            try
            {   // чтение ответа источника
                sr.Read(SourceAnswer, 0, 2);

                retValue = new string(SourceAnswer);
            }
            catch (Exception)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
            }
            return retValue;
        }

        /// <summary>
        /// Формирование команды для разряда конденсаторов
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string ChargeOFF(NetworkStream ns, StreamReader sr)
        {
            char[] SourceAnswer = new char[10];

            string retValue;
            count = 0;
            byte cmd = 0x62; //"b"

            try
            {
                ns.WriteByte(cmd); // отсылка команды в источник  
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 300) { break; }
                    count++;
                    Thread.Sleep(1);
                }
            }
            catch (Exception)
            {
                // действие при ошибке записи
                SourceAnswer[0] = 'A';
            }
            try
            {   // чтение ответа источника
                sr.Read(SourceAnswer, 0, 2);

                retValue = new string(SourceAnswer);
            }
            catch (Exception)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
            }
            return retValue;
        }
    
    }
}
