using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _701C_src_PGM
{
    /// <summary>
    /// Команды для обращения к источнику питания ИП 701С
    /// </summary>
    /// 
    class SourceCommand
    {
        private byte[] CmdBuf = new byte[10]; // буфер команды для отправки
        private byte Cmd_StartByte = 0x23;    // '#' - преамбула любой посылки

        private int count = 0;

        /// <summary>
        /// Задать предварительное значение напряжения, В
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <param name="VoltageHexValue"></param>
        /// <returns></returns>
        public string SetVoltage (NetworkStream ns, StreamReader sr, string VoltageHexValue)
        {
            char[] SourceAnswer = new char[10];

            for (int i = 0; i < 10; i++) { CmdBuf[i] = 0; } // обнуление буфера посылки 

            CmdBuf[0] = Cmd_StartByte; // # преамбула
            CmdBuf[1] = 0x04;          // число байт команды
            CmdBuf[2] = 0x55;          // ID команды = "U"
            CmdBuf[3] = Convert.ToByte(VoltageHexValue.Substring(0, 2), 16); // msb
            CmdBuf[4] = Convert.ToByte(VoltageHexValue.Substring(2, 2), 16); // lsb

            // расчет CRC, простая сумма всех байт команды
            for (int i = 0; i < 5; i++) { CmdBuf[5] += CmdBuf[i]; }
            try
            {
                ns.Write(CmdBuf, 0, 6); // отсылка команды в источник  
                Thread.Sleep(100);       // !!!!!!!!!!!!!!!!!!
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 50) { break; }
                    count++;
                    Thread.Sleep(1);
                }

            }
            catch (Exception)
            {
                // действие при ошибке записи
                SourceAnswer[0] = 'W';
            }
            try 
            {   // чтение ответа источника
                sr.Read(SourceAnswer, 0, 10);  
            }
            catch (System.IO.IOException)
            {
                // действие при ошибке чтения ответа
                SourceAnswer[0] = 'X';
            }
           
            string status = new string(SourceAnswer);
            return status;
        }

        /// <summary>
        /// Чтение напряжения на конденсаторах 
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string GetVoltage(NetworkStream ns)//, StreamReader sr)
        {
            //char[] SourceAnswer = new char[8];
            byte[] SourceAns = new byte[8];
            for (int i = 0; i < 8; i++) { CmdBuf[i] = 0; } // обнуление буфера посылки 

            CmdBuf[0] = Cmd_StartByte; // # преамбула
            CmdBuf[1] = 0x02;          // число байт команды
            CmdBuf[2] = 0x41;          // ID команды = "U"
            CmdBuf[3] = 0x66;          // CRC текущей команды - статична

            byte SRC_ADC_val_msb = 0x00;        // msb отсчета АЦП источника
            byte SRC_ADC_val_lsb = 0x00;        // lsb отсчета АЦП источника
            ushort Result = 0x0000;            
            ushort CRC = 0x0000;                    // CRC
            byte[] ReadBufU8 = new byte[8];   // буфер для всех прочитанных байт
            string retValue;
            
            try
            {
                ns.Write(CmdBuf, 0, 4); // отсылка команды в источник  
                Thread.Sleep(150);       // !!!!!!!!!!!!!!!!!!
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 100) { break; }
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
 
                ns.Read(SourceAns, 0, 8); // читаем данные в буфер
                
                for (int i = 0; i < 7; i++)
                {
                    // вытаскиваем байты с отчетами АЦП, 
                    // формат ответа источника: '!' + '0x04' + 'A==65' + 'ADC_msb' + 'ADC_lsb' + crc

                    if (SourceAns[i] == 65)
                    {
                        CRC = (ushort)(SourceAns[i - 2] + SourceAns[i - 1]
                            + SourceAns[i] + SourceAns[i + 1] + SourceAns[i + 2]);
                        CRC = (ushort)(CRC << 8);
                        CRC = (ushort)(CRC >> 8);


                        //MessageBox.Show(SourceAns[i - 3].ToString() + SourceAns[i - 2].ToString() + " " + SourceAns[i - 1].ToString() + " "
                        //    + SourceAns[i].ToString() + " " + SourceAns[i + 1].ToString() + " " + SourceAns[i + 2]
                        //    + " crc red" + SourceAns[i + 3].ToString() + " calc " + CRC.ToString());

                        //MessageBox.Show(CRC.ToString() + " " + ReadBufU16[i + 3].ToString());

                        if (CRC == SourceAns[i + 3])
                        {
                        SRC_ADC_val_msb = SourceAns[i + 1]; // 'ADC_msb'
                        SRC_ADC_val_lsb = SourceAns[i + 2]; // 'ADC_lsb' 
                        Result = (ushort)((SRC_ADC_val_msb<<8) + SRC_ADC_val_lsb);
                            // 'ADC_msb' + 'ADC_lsb'
                        //MessageBox.Show(SRC_ADC_val_msb.ToString() + " " + SRC_ADC_val_lsb.ToString());
                            
                        }
                    }
                }
                retValue = Result.ToString();
            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
                //MessageBox.Show(ex.Message);
            }

            return retValue;

        }

        public string GetStatus(NetworkStream ns)//, StreamReader sr)
        {
            byte[] SourceAns = new byte[8];
            for (int i = 0; i < 8; i++) { CmdBuf[i] = 0; } // обнуление буфера посылки 

            CmdBuf[0] = Cmd_StartByte; // # преамбула
            CmdBuf[1] = 0x02;          // число байт команды
            CmdBuf[2] = 0x45;          // ID команды = "E"
            CmdBuf[3] = 0x6A;          // CRC текущей команды - статична

            byte statusByte = 0x00;        // msb отсчета АЦП источника
            byte errorByte = 0x00;         // lsb отсчета АЦП источника
            ushort CRC = 0x0000;              // CRC
            byte[] ReadBufU8 = new byte[8];   // буфер для всех прочитанных байт
            string retValue = "x";

            try
            {
                ns.Write(CmdBuf, 0, 4); // отсылка команды в источник  
                Thread.Sleep(150);       // !!!!!!
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 100) { break; }
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

                ns.Read(SourceAns, 0, 8); // читаем данные в буфер

                for (int i = 0; i < 7; i++)
                {
                    // вытаскиваем байты с отчетами АЦП, 
                    // формат ответа источника: '!' + '0x04' + 'E==69' + 'statyus byte' + 'error byte' + crc

                    if (SourceAns[i] == 69) // 'E'
                    {
                        //CRC = (ushort)(SourceAns[i - 2] + SourceAns[i - 1]
                        //    + SourceAns[i] + SourceAns[i + 1] + SourceAns[i + 2]);
                        //CRC = (ushort)(CRC << 8);
                        //CRC = (ushort)(CRC >> 8);


                        //MessageBox.Show(SourceAns[i - 3].ToString() + SourceAns[i - 2].ToString() + " " + SourceAns[i - 1].ToString() + " "
                        //    + SourceAns[i].ToString() + " " + SourceAns[i + 1].ToString() + " " + SourceAns[i + 2]
                        //    + " crc red" + SourceAns[i + 3].ToString() + " calc " + CRC.ToString());

                        //MessageBox.Show(CRC.ToString() + " " + ReadBufU16[i + 3].ToString());

                        //if (CRC == SourceAns[i + 3])
                        //{
                        statusByte = SourceAns[i + 1];
                        errorByte  = SourceAns[i + 2];

                        retValue = Convert.ToString(statusByte, 2).PadLeft(8, '0');
                        retValue += "_";
                        retValue += Convert.ToString(errorByte, 2).PadLeft(8, '0');
                            // 'ADC_msb' + 'ADC_lsb'
                            //MessageBox.Show(SRC_ADC_val_msb.ToString() + " " + SRC_ADC_val_lsb.ToString());

                        //}
                    }
                }
                //retValue = Result.ToString();
            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
                //MessageBox.Show(ex.Message);
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

            CmdBuf[0] = Cmd_StartByte; // # преамбула
            CmdBuf[1] = 0x02;          // число байт команды
            CmdBuf[2] = 0x43;          // ID команды = "C"
            CmdBuf[3] = 0x68;          // CRC текущей команды - статична
            string retValue;

            try
            {
                ns.Write(CmdBuf, 0, 4); // отсылка команды в источник  
                Thread.Sleep(150);       // !!!!!!!!!!!!!!!!!!
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 100) { break; }
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
                sr.Read(SourceAnswer, 0, 10);

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

            CmdBuf[0] = Cmd_StartByte; // # преамбула
            CmdBuf[1] = 0x02;          // число байт команды
            CmdBuf[2] = 0x44;          // ID команды = "C"
            CmdBuf[3] = 0x69;          // CRC текущей команды - статична
            string retValue;

            try
            {
                ns.Write(CmdBuf, 0, 4); // отсылка команды в источник  
                Thread.Sleep(150);       // !!!!!!!!!!!!!!!!!!
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 100) { break; }
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
                sr.Read(SourceAnswer, 0, 10);
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
