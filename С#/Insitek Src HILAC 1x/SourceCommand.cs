using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Insitek_src
{
    /// <summary>
    /// Команды для обращения к источнику питания Insitek
    /// </summary>
    /// 
    class SourceCommand
    {
            
        private byte Modbus_RHR_cmd = 0x03;    // modbus Read Holding Registers command 
        private byte Modbus_WSR_cmd = 0x06;    // modbus Write Sinhle Register command 
        private byte Modbus_WSС_cmd = 0x05;    // modbus Force Single Coil command 
        private byte Modbus_RCS_cmd = 0x01;     // modbus Read Coil Status command 

        private byte Rd_V_reg_addr = 38;    // адрес регистра для чтения U
        private byte Rd_I_reg_addr = 37;    // адрес регистра для чтения I
        private byte Wr_V_reg_addr = 54;    // адрес регистра для записи U
        private byte Rd_stat_reg_addr = 100;    // адрес регистра для чтения статуса
        private byte Rd_outState_coil_addr = 2;    // адрес регистра для чтения сост. выхода 

        private UInt16 crc16 = 0x0000;
        private byte crc16_msb = 0x00;
        private byte crc16_lsb = 0x00;
        private int count = 0;

        //-------crc16
        UInt16 ModRTU_CRC(byte[] buf, int len)
        {
            UInt16 crc = 0xFFFF;
            for (int pos = 0; pos < len; pos++)
            {
                crc ^= (UInt16)buf[pos];          // XOR byte into least sig. byte of crc

                for (int i = 8; i != 0; i--)
                {    // Loop over each bit
                    if ((crc & 0x0001) != 0)
                    {      // If the LSB is set
                        crc >>= 1;                    // Shift right and XOR 0xA001
                        crc ^= 0xA001;
                    }
                    else                            // Else LSB is not set
                        crc >>= 1;                    // Just shift right
                }
            }
            // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
            return crc;
        }
        //-------
        
        /// <summary>
        /// Формирование посылки байт для чтения одиночного регистра 
        /// </summary>
        /// <param name="Src_ID"></param>
        /// <param name="reg2read"></param>
        /// <returns></returns>
        private byte[] ModRTU_buildR_msg(byte Src_ID, byte reg2read)
        {
            byte[] WrCmdBuf = new byte[8]; // буфер команды для отправки

            for (int i = 0; i < 8; i++) { WrCmdBuf[i] = 0; } // обнуление буфера посылки 
        
            WrCmdBuf[0] = Src_ID;        // id источника /*Cmd_StartByte*/
            WrCmdBuf[1] = Modbus_RHR_cmd;// ReadHoldingRegister cmd
            WrCmdBuf[2] = 0x00;          // адрес регистра ст. байт
            WrCmdBuf[3] = reg2read;      // адрес регистра мл. байт - 38 чтение напряж., 37 - I
            WrCmdBuf[4] = 0x00;          // количество байт- ст.байт
            WrCmdBuf[5] = 0x01;          // количество байт- мл. байт

            crc16 = ModRTU_CRC(WrCmdBuf, 6);// crc текущей команды подсчет и сохранение 

            crc16_msb = (byte)(crc16 >> 8); //Ст разряд контрол суммы
            crc16 = (byte)(crc16 & 0x00ff);
            crc16_lsb = (byte)(crc16);

            WrCmdBuf[7] = crc16_msb;
            WrCmdBuf[6] = crc16_lsb;

            return WrCmdBuf;

        }

        /// <summary>
        /// Формирование посылки байт для записи одной команды
        /// </summary>
        /// <param name="Src_ID"></param>
        /// <param name="reg2write"></param>
        /// <param name="data2wr"></param>
        /// <returns></returns>
        private byte[] ModRTU_buildW_msg(byte Src_ID, byte reg2write, ushort data2wr)
        {
            byte[] RdCmdBuf = new byte[8]; // буфер команды для отправки

            for (int i = 0; i < 8; i++) { RdCmdBuf[i] = 0; } // обнуление буфера посылки 

            byte data2wr_msb = (byte)(data2wr >> 8); // сохр. Ст разряд данных
            data2wr = (byte)(data2wr & 0x00ff);
            byte data2wr_lsb = (byte)(data2wr);

            RdCmdBuf[0] = Src_ID;        // id источника /*Cmd_StartByte*/
            RdCmdBuf[1] = Modbus_WSR_cmd;// WriteSingleRegister cmd
            RdCmdBuf[2] = 0x00;          // адрес регистра ст. байт
            RdCmdBuf[3] = reg2write;     // адрес регистра мл. байт - 38 чтение напряж., 37 - I
            RdCmdBuf[4] = data2wr_msb;   // ст.байт данных
            RdCmdBuf[5] = data2wr_lsb;   // мл. байт данных

            crc16 = ModRTU_CRC(RdCmdBuf, 6);// crc текущей команды подсчет и сохранение 

            crc16_msb = (byte)(crc16 >> 8); //Ст разряд контрол суммы
            crc16 = (byte)(crc16 & 0x00ff);
            crc16_lsb = (byte)(crc16);

            RdCmdBuf[7] = crc16_msb;   
            RdCmdBuf[6] = crc16_lsb;

            return RdCmdBuf;

        }

        /// <summary>
        /// Формирование посылки байт для записи одного байта
        /// </summary>
        /// <param name="Src_ID"></param>
        /// <param name="reg2write"></param>
        /// <param name="data2wr"></param>
        /// <returns></returns>
        private byte[] ModRTU_buildWс_msg(byte Src_ID, byte reg2write, ushort data2wr)
        {
            byte[] RdCmdBuf = new byte[8]; // буфер команды для отправки

            for (int i = 0; i < 8; i++) { RdCmdBuf[i] = 0; } // обнуление буфера посылки 

            byte data2wr_msb = (byte)(data2wr >> 8); // сохр. Ст разряд данных
            data2wr = (byte)(data2wr & 0x00ff);
            byte data2wr_lsb = (byte)(data2wr);

            RdCmdBuf[0] = Src_ID;        // id источника /*Cmd_StartByte*/
            RdCmdBuf[1] = Modbus_WSС_cmd;// WriteSingleCoil cmd
            RdCmdBuf[2] = 0x00;          // адрес регистра ст. байт
            RdCmdBuf[3] = reg2write;     // адрес регистра мл. байт - 38 чтение напряж., 37 - I
            RdCmdBuf[4] = data2wr_msb;   // ст.байт данных
            RdCmdBuf[5] = data2wr_lsb;   // мл. байт данных

            crc16 = ModRTU_CRC(RdCmdBuf, 6);// crc текущей команды подсчет и сохранение 

            crc16_msb = (byte)(crc16 >> 8); //Ст разряд контрол суммы
            crc16 = (byte)(crc16 & 0x00ff);
            crc16_lsb = (byte)(crc16);

            RdCmdBuf[7] = crc16_msb;
            RdCmdBuf[6] = crc16_lsb;

            return RdCmdBuf;

        }

        /// <summary>
        /// Формирование посылки байт для чтения одного байта
        /// </summary>
        /// <param name="Src_ID"></param>
        /// <param name="reg2write"></param>
        /// <param name="data2wr"></param>
        /// <returns></returns>
        private byte[] ModRTU_buildRс_msg(byte Src_ID, byte Coil2read)
        {
            byte[] RdCmdBuf = new byte[8]; // буфер команды для отправки

            for (int i = 0; i < 8; i++) { RdCmdBuf[i] = 0; } // обнуление буфера посылки 

            RdCmdBuf[0] = Src_ID;        // id источника /*Cmd_StartByte*/
            RdCmdBuf[1] = Modbus_RCS_cmd;// ReadSingleCoil cmd
            RdCmdBuf[2] = 0x00;          // адрес регистра ст. байт
            RdCmdBuf[3] = Coil2read;      // адрес регистра мл. байт
            RdCmdBuf[4] = 0;   // Количество данных для считывания msb
            RdCmdBuf[5] = 1;   // Количество данных для считывания lsb

            crc16 = ModRTU_CRC(RdCmdBuf, 6);// crc текущей команды подсчет и сохранение 

            crc16_msb = (byte)(crc16 >> 8); //Ст разряд контрол суммы
            crc16 = (byte)(crc16 & 0x00ff);
            crc16_lsb = (byte)(crc16);

            RdCmdBuf[7] = crc16_msb;
            RdCmdBuf[6] = crc16_lsb;

            return RdCmdBuf;

        }

        public string SetID(byte SRC_ID, NetworkStream ns, StreamReader sr, ushort ID2set)
        {
            string status = "0";
            byte[] SourceCmd1 = new byte[8]; // буфер команды для отправки 1
            byte[] SourceCmd2 = new byte[8]; // буфер команды для отправки 2

            SourceCmd1 = ModRTU_buildW_msg(SRC_ID, 0x01, ID2set);
            SourceCmd2 = ModRTU_buildW_msg(SRC_ID, 0x06, 0x1111);

            try
            {
                ns.Write(SourceCmd1, 0, 8); // отсылка команды в источник  
                //while (!ns.DataAvailable)
                //{
                //     искусственный таймаут чтения...
                //    if (count >= 10) { break; }
                //    count++;
                //    Thread.Sleep(1);
                //}

                ns.Write(SourceCmd2, 0, 8); // отсылка команды в источник
                //while (!ns.DataAvailable)
                //{
                //    // искусственный таймаут чтения...
                //    if (count >= 10) { break; }
                //    count++;
                //    Thread.Sleep(1);
                //}
                status = "1";
            }
            catch (Exception)
            {
                // действие при ошибке записи
                status = "0";
            }

            return status;
        }

        /// <summary>
        /// Задать предварительное значение напряжения, В
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <param name="VoltageHexValue"></param>
        /// <returns></returns>
        public string SetVoltage (byte SRC_ID, NetworkStream ns, StreamReader sr, ushort V2set)
        {
            string status = "";
            byte[] SourceCmd = new byte[8]; // буфер команды для отправки
            byte[] SourceAns = new byte[7]; // буфер для чтения

            byte Read_volt_msb = 0x00;        // msb U источника
            byte Read_volt_lsb = 0x00;        // lsb U источника
            ushort Read_voltage = 0x0000;     // 2-байтный результат чтения U

            byte CRC_msb = 0x00;
            byte CRC_lsb = 0x00;
            UInt16 CRC_calc = 0x0000;              // CRC расчетн
            UInt16 CRC_read = 0x0000;              // CRC счит.
 
            //Ответ 3,5 мс Скорость обмена 19200 [бод]
            SourceCmd = ModRTU_buildW_msg(SRC_ID, Wr_V_reg_addr, V2set);

            try
            {
                ns.Write(SourceCmd, 0, 8); // отсылка команды в источник  

                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 10) { break; }
                    count++;
                    Thread.Sleep(1);
                }
                status = "1";
            }
            catch (Exception)
            {
                // действие при ошибке записи
                status = "0";
            }

            return status;
        }

        /// <summary>
        /// Чтение напряжения
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string GetVoltage(byte SRC_ID, NetworkStream ns)
        {
            string retValue = "err";
            byte[] SourceCmd = new byte[8]; // буфер команды для отправки
            byte[] SourceAns = new byte[7]; // буфер для чтения

            byte Read_volt_msb = 0x00;        // msb U источника
            byte Read_volt_lsb = 0x00;        // lsb U источника
            ushort Read_voltage = 0x0000;     // 2-байтный результат чтения U

            byte CRC_msb = 0x00;
            byte CRC_lsb = 0x00;
            UInt16 CRC_calc = 0x0000;              // CRC расчетн
            UInt16 CRC_read = 0x0000;              // CRC счит.

            //Ответ 3,5 мс Скорость обмена 19200 [бод]
            SourceCmd = ModRTU_buildR_msg(SRC_ID, Rd_V_reg_addr);

            try
            {
                ns.Write(SourceCmd, 0, 8); // отсылка команды в источник  

                //while (!ns.DataAvailable)
                //{
                //    // искусственный таймаут чтения...
                //    if (count >= 1000) { break; }
                //    count++;
                    Thread.Sleep(50);
                //}

            }
            catch (Exception)
            {
                // действие при ошибке записи
                retValue = "0";
            }
            try
            {   // чтение ответа источника
                
                for (int i = 0; i < 7; i++)
                {
                    SourceAns[i] = (byte)ns.ReadByte(); 
                }

                CRC_lsb = SourceAns[5];
                CRC_msb = SourceAns[6];

                CRC_read = (ushort)((CRC_msb << 8) + CRC_lsb);
                CRC_calc = ModRTU_CRC(SourceAns, 5);

                if (CRC_calc == CRC_read) // контр. сумма сходится  
                {
                    Read_volt_msb = SourceAns[3]; // 'U_msb'
                    Read_volt_lsb = SourceAns[4]; // 'U_lsb'
                    Read_voltage = (ushort)((Read_volt_msb << 8) + Read_volt_lsb); // U full
                    retValue = Read_voltage.ToString();
                    retValue = CorStrGetVoltage(Read_voltage.ToString());
                    retValue += ";" + SourceAns[0]; 
                }
                else 
                {
                    retValue = "-";
                }
                
            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1"; 
            }
            //MessageBox.Show(retValue);
            return retValue;
        }

        /// <summary>
        /// Чтение тока
        /// </summary>
        /// <param name="ns"></param>
        /// <returns></returns>
        public string GetCurrent(byte SRC_ID, NetworkStream ns)
        {
            string retValue = "";
            byte[] SourceCmd = new byte[8]; // буфер команды для отправки
            byte[] SourceAns = new byte[7]; // буфер для чтения

            byte Read_curr_msb = 0x00;        // msb I источника
            byte Read_curr_lsb = 0x00;        // lsb I источника
            ushort Read_current = 0x0000;     // 2-байтный результат чтения I

            byte CRC_msb = 0x00;
            byte CRC_lsb = 0x00;
            UInt16 CRC_calc = 0x0000;              // CRC расчетн
            UInt16 CRC_read = 0x0000;              // CRC счит.

            //Ответ 3,5 мс Скорость обмена 19200 [бод]
            SourceCmd = ModRTU_buildR_msg(SRC_ID, Rd_I_reg_addr);

            try
            {
                ns.Write(SourceCmd, 0, 8); // отсылка команды в источник  

                //while (!ns.DataAvailable)
                //{
                //     искусственный таймаут чтения...
                //    if (count >= 1000) { break; }
                //    count++;
                    Thread.Sleep(100);
                //}

            }
            catch (Exception)
            {
                // действие при ошибке записи
                retValue = "0";
            }
            try
            {   // чтение ответа источника

                for (int i = 0; i < 7; i++) { SourceAns[i] = (byte)ns.ReadByte(); }

                CRC_lsb = SourceAns[5];
                CRC_msb = SourceAns[6];

                CRC_read = (ushort)((CRC_msb << 8) + CRC_lsb);
                CRC_calc = ModRTU_CRC(SourceAns, 5);

                if (CRC_calc == CRC_read) // контр. сумма сходится

                {
                    Read_curr_msb = SourceAns[3]; // 'I_msb'
                    Read_curr_lsb = SourceAns[4]; // 'I_lsb'
                    Read_current = (ushort)((Read_curr_msb << 8) + Read_curr_lsb); // U full
                    retValue = Read_current.ToString();
                    retValue = CorStrGetVoltage(retValue);
                    retValue += ";" + SourceAns[0]; 
                }

            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1;";
            }

            return retValue;
        }

        /// <summary>
        /// Чтение состояния выхода источника
        /// </summary>
        /// <param name="SRC_ID"></param>
        /// <param name="ns"></param>
        /// <returns></returns>
        public string GetStatus(byte SRC_ID, NetworkStream ns)
        {
            string retValue = "err";
            byte[] SourceCmd = new byte[8]; // буфер команды для отправки
            byte[] SourceAns = new byte[7]; // буфер для чтения

            byte Read_msb = 0x00;        // msb U источника
            byte Read_lsb = 0x00;        // lsb U источника
            ushort Read = 0x0000;     // 2-байтный результат чтения U

            byte CRC_msb = 0x00;
            byte CRC_lsb = 0x00;
            UInt16 CRC_calc = 0x0000;              // CRC расчетн
            UInt16 CRC_read = 0x0000;              // CRC счит.

            //Ответ 3,5 мс Скорость обмена 19200 [бод]
            SourceCmd = ModRTU_buildR_msg(SRC_ID, Rd_stat_reg_addr);

            try
            {
                ns.Write(SourceCmd, 0, 8); // отсылка команды в источник  

                //while (!ns.DataAvailable)
                //{
                //    искусственный таймаут чтения...
                //    if (count >= 1000) { break; }
                //    count++;
                    Thread.Sleep(50);
                //}

            }
            catch (Exception)
            {
                // действие при ошибке записи
                retValue = "0";
            }
            try
            {   // чтение ответа источника

                for (int i = 0; i < 7; i++)
                {
                    SourceAns[i] = (byte)ns.ReadByte();
                }

                CRC_lsb = SourceAns[5];
                CRC_msb = SourceAns[6];

                CRC_read = (ushort)((CRC_msb << 8) + CRC_lsb);
                CRC_calc = ModRTU_CRC(SourceAns, 5);

                if (CRC_calc == CRC_read) // контр. сумма сходится  
                {

                    
                    Read_lsb = SourceAns[3];
                    Read_msb = SourceAns[4];
                    Read = (ushort)((Read_msb << 8) + Read_lsb);
                    retValue = Convert.ToString(Read, 2).PadLeft(13, '0');
                }
                else
                {

                }

            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1;";
                //MessageBox.Show(ex.Message);
            }
            return retValue;
        }

        /// <summary>
        /// Управление выходом источника
        /// </summary>
        /// <param name="SRC_ID"></param>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <param name="OutputState"></param>
        /// <returns></returns>
        public string SetOutput(byte SRC_ID, NetworkStream ns, StreamReader sr, ushort OutputState)
        {
            byte SrcOutCfgBit_CoilAddr = 2; // адрес бита в битовом поле регистра № 100 источника

            string retValue = "";
            byte[] SourceCmd = new byte[8]; // буфер команды для отправки
            byte[] SourceAns = new byte[7]; // буфер для чтения

            byte Read_out_msb = 0x00;        // msb сост. выхода источника
            byte Read_out_lsb = 0x00;        // lsb сост. выхода источника
            UInt16 Read_out = 0x0000;        // сост. выхода источника

            byte CRC_msb = 0x00;
            byte CRC_lsb = 0x00;
            UInt16 CRC_calc = 0x0000;              // CRC расчетн
            UInt16 CRC_read = 0x0000;              // CRC счит.

            if (OutputState == 1) OutputState = 0xff00;
            else                  OutputState = 0x0000;

            SourceCmd = ModRTU_buildWс_msg(SRC_ID, SrcOutCfgBit_CoilAddr, OutputState);
            try
            {
                ns.Write(SourceCmd, 0, 8); // отсылка команды в источник  
                //Ответ 3,5 мс Скорость обмена 19200 [бод]
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 10) { break; }
                    count++;
                    Thread.Sleep(1);
                }

            }
            catch (Exception)
            {
                // действие при ошибке записи
                retValue = "0";
            }
            try
            {   // чтение ответа источника

                for (int i = 0; i < 8; i++) { SourceAns[i] = (byte)ns.ReadByte(); }

                CRC_lsb = SourceAns[5];
                CRC_msb = SourceAns[6];

                CRC_read = (ushort)((CRC_msb << 8) + CRC_lsb);
                CRC_calc = ModRTU_CRC(SourceAns, 5);

                if (CRC_calc == CRC_read) // контр. сумма сходится
                {   //0xff00 - out ON, 0x0000 - out off
                    Read_out_msb = SourceAns[3]; // 'out_msb'
                    Read_out_lsb = SourceAns[4]; // 'out_lsb'
                    Read_out = (ushort)((Read_out_msb << 8) + Read_out_lsb); // out state full
                    retValue = Read_out.ToString();
                }

            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
            }

            return retValue;
        }

        public string SaveCfg2EEPROM(byte SRC_ID, NetworkStream ns, StreamReader sr)
        {
            byte SrcEESaveBit_CoilAddr = 4; // адрес бита в битовом поле регистра № 100 источника

            string retValue = "";
            byte[] SourceCmd = new byte[8]; // буфер команды для отправки
            byte[] SourceAns = new byte[7]; // буфер для чтения

            byte Read_out_msb = 0x00;        // msb сост. выхода источника
            byte Read_out_lsb = 0x00;        // lsb сост. выхода источника
            UInt16 Read_out = 0x0000;        // сост. выхода источника

            byte CRC_msb = 0x00;
            byte CRC_lsb = 0x00;
            UInt16 CRC_calc = 0x0000;              // CRC расчетн
            UInt16 CRC_read = 0x0000;              // CRC счит.

            SourceCmd = ModRTU_buildWс_msg(SRC_ID, SrcEESaveBit_CoilAddr, 0xff00);
            try
            {
                ns.Write(SourceCmd, 0, 8); // отсылка команды в источник  
                //Ответ 3,5 мс Скорость обмена 19200 [бод]
                while (!ns.DataAvailable)
                {
                    // искусственный таймаут чтения...
                    if (count >= 10) { break; }
                    count++;
                    Thread.Sleep(1);
                }

            }
            catch (Exception)
            {
                // действие при ошибке записи
                retValue = "0";
            }
            try
            {   // чтение ответа источника

                for (int i = 0; i < 8; i++) { SourceAns[i] = (byte)ns.ReadByte(); }

                CRC_lsb = SourceAns[5];
                CRC_msb = SourceAns[6];

                CRC_read = (ushort)((CRC_msb << 8) + CRC_lsb);
                CRC_calc = ModRTU_CRC(SourceAns, 5);

                if (CRC_calc == CRC_read) // контр. сумма сходится
                {   //0xff00 - out ON, 0x0000 - out off
                    Read_out_msb = SourceAns[3]; // 'out_msb'
                    Read_out_lsb = SourceAns[4]; // 'out_lsb'
                    Read_out = (ushort)((Read_out_msb << 8) + Read_out_lsb); // out state full
                    retValue = Read_out.ToString();
                }

            }
            catch (Exception ex)
            {
                // действие при ошибке чтения ответа
                retValue = "-1";
            }

            return retValue;
        }

        /// <summary>
        /// Корректировка отображения значения напряжения [kV] 
        /// </summary>
        /// <param name="_correctString"></param>
        /// <returns></returns>
        private string CorStrGetVoltage (string _correctString)
        {
            switch (_correctString.Length)
            {
                case 1:
                    _correctString = _correctString.Insert(_correctString.Length - 1, "0.");
                    break;
                case 2:
                    _correctString = _correctString.Insert(_correctString.Length - 1, ".");
                    break;
                case 3:
                    _correctString = _correctString.Insert(_correctString.Length - 1, ".");
                    break;
                case 4:
                    _correctString = _correctString.Insert(_correctString.Length - 1, ".");
                    break;
                default:
                    break;
            }
            return _correctString;
        }

    }
}
