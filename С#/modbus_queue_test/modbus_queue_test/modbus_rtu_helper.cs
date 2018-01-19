using System;
using System.Net;
using System.IO;
using System.Net.Sockets;
using System.Linq;
using System.Collections.Generic;
using System.Windows;
using System.Threading;

namespace modbus_queue_test
{   
    enum cmd_type
     {
        rhr = (byte)0x03,   // modbus Read Holding Registers command 
        wsr = (byte)0x06    // modbus Write Single Register command 
     } 

    class modbus_rtu_helper
    {


        // расчет контрольной суммы
        private ushort calc_crc(byte[] buf, int len)
        {//-------crc16
            UInt16 crc = 0xFFFF;
            for (int pos = 0; pos < len; pos++)
            {
                crc ^= (UInt16)buf[pos];          // XOR byte into least sig. byte of crc
                for (int i = 8; i != 0; i--)
                {    // Loop over each bit
                    if ((crc & 0x0001) != 0)
                    {      // If the LSB is set
                        crc >>= 1;                // Shift right and XOR 0xA001
                        crc ^= 0xA001;
                    }
                    else                          // Else LSB is not set
                        crc >>= 1;                  // Just shift right
                }
            }
            // Note, this number has low and high bytes swapped, 
            // so use it accordingly (or swap bytes)
            // swapping bytes
            //if (invert_en) crc = Convert.ToUInt16(((crc << 8) & 0xff00) | ((crc >> 8) & 0x00ff));

            return crc;
        }

        /// <summary>
        /// Формирование посылки байт для чтения одного регистра Modbus
        /// </summary>
        /// <param name="device_id"></param>
        /// <param name="reg_addr"></param>
        /// <returns></returns>
        public byte[] build_rhr_cmd(byte device_id, ushort reg_addr, ushort count)
        {
            ushort crc16 = 0x0000;
            byte crc16_lsb = 0x00;
            byte crc16_msb = 0x00;

            if (count > 125)
                count = 125;

            byte[] WrCmdBuf = new byte[8]; // буфер команды для отправки

            byte addr_msb = (byte)(reg_addr >> 8); // ст. байт адреса
            reg_addr = (byte)(reg_addr & 0x00ff);  
            byte addr_lsb = (byte)(reg_addr);      // мл. байт адреса

            WrCmdBuf[0] = device_id;     // id
            WrCmdBuf[1] = (byte)cmd_type.rhr;       // ReadHoldingRegister cmd
            WrCmdBuf[2] = addr_msb;      // адрес регистра для чтения ст. байт
            WrCmdBuf[3] = addr_lsb;      // адрес регистра для чтения мл. байт
            WrCmdBuf[4] = 0x00;          // количество байт- ст.байт
            WrCmdBuf[5] = (byte) count;         // количество байт- мл. байт

            crc16 = calc_crc(WrCmdBuf, 6);// crc текущей команды подсчет и сохранение 

            crc16_msb = (byte)(crc16 >> 8); //Ст разряд контрол суммы
            crc16 = (byte)(crc16 & 0x00ff);
            crc16_lsb = (byte)(crc16);

            WrCmdBuf[7] = crc16_msb;
            WrCmdBuf[6] = crc16_lsb;
            return WrCmdBuf;

        }

        /// <summary>
        /// Формирование посылки байт для записи в один регистр по адресу
        /// </summary>
        /// <param name="device_id"></param>
        /// <param name="reg_addr"></param>
        /// <param name="data2wr"></param>
        /// <returns></returns>
        public byte[] build_wsr_cmd(byte device_id, ushort reg_addr, ushort data2wr)
        {
            ushort crc16 = 0x0000;
            byte crc16_msb = 0x00;
            byte crc16_lsb = 0x00;
            
            byte[] RdCmdBuf = new byte[8]; // буфер команды для отправки

            byte data2wr_msb = (byte)(data2wr >> 8); // ст. байт данных
            data2wr = (byte)(data2wr & 0x00ff);
            byte data2wr_lsb = (byte)(data2wr);      // мл. байт данных

            byte addr_msb = (byte)(reg_addr >> 8); // ст. байт адреса
            reg_addr = (byte)(reg_addr & 0x00ff);
            byte addr_lsb = (byte)(reg_addr);      // мл. байт адреса

            RdCmdBuf[0] = device_id;     // id
            RdCmdBuf[1] = (byte)cmd_type.wsr;      // WriteSingleRegister cmd
            RdCmdBuf[2] = addr_msb;                // адрес регистра для записи ст. байт
            RdCmdBuf[3] = addr_lsb;      // адрес регистра для записи мл. байт 
            RdCmdBuf[4] = data2wr_msb;   // ст.байт данных
            RdCmdBuf[5] = data2wr_lsb;   // мл. байт данных

            crc16 = calc_crc(RdCmdBuf, 6);// crc текущей команды подсчет и сохранение 

            crc16_msb = (byte)(crc16 >> 8); //Ст разряд контрол суммы
            crc16 = (byte)(crc16 & 0x00ff);
            crc16_lsb = (byte)(crc16);

            RdCmdBuf[7] = crc16_msb;
            RdCmdBuf[6] = crc16_lsb;

            return RdCmdBuf;

        }
        /// <summary>
        /// Извлечение строки из считанного регистра
        /// </summary>
        /// <param name="modbus_array"></param>
        /// <returns></returns>
        private List<string> parse_read_answer(byte[] modbus_array)
        {

            int count = modbus_array[2];           // число переданных байт
            string[] regs_data = new string[125];  // массив для сохр. значений запрошеных регистров  
            byte msb, lsb;
            short word;
            int pointer = 3;  // смещения индекса с начала посылки на байты данных
            for (int i = 0; i < count/2; i++)
            {
                msb = modbus_array[pointer++]; // reg_msb
                lsb = modbus_array[pointer++]; // reg_lsb

                word = (short)((msb << 8) + lsb); // объединение байт
                regs_data[i] = word.ToString();
            }

            List<string> resp = new List<string>(regs_data).FindAll(x => x != null);

            return resp;
        }

        /// <summary>
        /// Извлечение строки из отввета на команду записи в регистр
        /// </summary>
        /// <param name="modbus_array"></param>
        /// <returns></returns>
        private string parse_write_answer(byte[] modbus_array)
        {

            byte msb = modbus_array[4]; // 'data_msb'
            byte lsb = modbus_array[5]; // 'data_lsb'

            short word = (short)((msb << 8) + lsb); // объединение байт

            return word.ToString();
        }

        /// <summary>
        /// запись данных в регистра modbus с подтверждением ответа
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="write_array"></param>
        /// <returns></returns>
        private List<string> write_reg(NetworkStream ns, byte[] write_array)
        {
            byte[] dev_wr_answer = new byte[8];           // буфер для чтения ответ
            List<string> return_list = new List<string>();  // список для сохр. ответа на команду записи
            string reg_data; 
            try
            {
                ns.Write(write_array, 0, 8);                                        // отсылка команды записи регистра                         
                for (int i = 0; i < 8; i++) dev_wr_answer[i] = (byte)ns.ReadByte(); // чтение

                if (write_array.SequenceEqual(dev_wr_answer))                       // сравнение массивов элемент к элементу
                {
                    reg_data = parse_write_answer(dev_wr_answer);              // сохр. считаное значение регистра если все ок     
                }
                else reg_data = "crc error";    // ошибка контрольной суммы
            }
            catch { reg_data = "r/w error"; }   // ошибка чтения или записи

            return_list.Add(reg_data);

            return return_list;                
        }

        /// <summary>
        /// чтение регистрв modbus
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="read_array"></param>
        /// <returns></returns>
        private List<string> read_regs(NetworkStream ns, byte[] read_array)
        {
            // возвращает массив строк со значениями запрошенных регистров в случае успешного чтения
            // в случае ошибки на уровне пакетов модбас вернет строчку "crc error" в нулевом элементе массива, остальные - null
            // в случае ошибки на уровне чтения/записи сокета вернет строчку "r/w error" в нулевом элементе массива, остальные - null
            byte[] dev_rd_answer = new byte[255];  // буфер для чтения ответа  
            List<string> regs_data = new List<string>();  // список для сохр. значений запрошеных регистров  
            
            ushort crc_rd, crc_calc;              // для хранения контрольных сумм - считаной из посылки и рассчитаной на ее основе
            byte count = read_array[5];           // сохр. число байт для чтения, 
                                                  // 5ый байт команды запроса содержит число регистров. 1 регистр = 2 байта

            int bytes_to_rd = (count * 2) + 5;    // число байт для чтения по сле отправки запроса на чтение
                                                  // 1 регистр = 2 байта, + 3 байта зоголока ответа + 2 байта CRC в хвосте
            int crc_msb_index = bytes_to_rd - 1;  // динамический расчет индекса msb crc
            int crc_lsb_index = bytes_to_rd - 2;  // динамический расчет индекса lsb crc
            int rd_count = 0;

            try
            {
                ns.Write(read_array, 0, 8);                                       // отсылка команды чтения регистра       
                //while (!ns.DaAvailable)
                //{
                //    rd_count++;
                //    Thread.Sleep(1);
                //    if (rd_count > 20) break; 
                //}
                for (int i = 0; i < bytes_to_rd; i++) 
                    dev_rd_answer[i] = (byte)ns.ReadByte();                       // чтение

                crc_rd = (ushort)((dev_rd_answer[crc_msb_index] << 8) + dev_rd_answer[crc_lsb_index]);      // сохр. считанной контрольной суммы
                crc_calc = calc_crc(dev_rd_answer, bytes_to_rd-2);           // расчет контрольной суммы считанного массива 
                                                                                  // из считаных регистров без учета 2 байт контрольнй суммы
                if (crc_rd == crc_calc)                                // сравнение контрольных сумм
                {
                    regs_data = parse_read_answer(dev_rd_answer); // сохр. считаное значение регистра если все ок     
                }
                else regs_data.Add("crc error");                       // ошибка контрольной суммы
            }
            catch { regs_data.Add("r/w error"); }                      // ошибка чтения или записи

            return regs_data;
        }
        
        /// <summary>
        /// выполнение команды modbus из очереди, возвращение ответа устройства на команду
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="read_array"></param>
        /// <returns></returns>
        public KeyValuePair<Dictionary<string, int>, List<string>> do_cmd(NetworkStream ns, byte[] read_array)
        { 
            // словарь контейнера возврата - информация о передаваемых данных
            Dictionary<string, int> resp_info = new Dictionary<string, int>();
            // список для сохр. данных 
            List<string> response = new List<string>();

            switch (read_array[1]) // анализ команды
            {
                case (byte)cmd_type.rhr: response = read_regs(ns, read_array); break; // ответ при чтении регистров
                case (byte)cmd_type.wsr: response = write_reg(ns, read_array); break; // ответ при записи в регистр

                default: response.Add("unknown command"); break;
            }


            resp_info.Add("id", (int)read_array[0]);      // запись id отвечающего устройства     
            resp_info.Add("cmd", (int)read_array[1]);      // запись команды, на которую отвечает устройтво 
            resp_info.Add("reg", (int)((read_array[2] << 8)// чтение - начальный адрес регистра чтения, запись - регистр записи   
                                        + read_array[3]));
            if (read_array[1] == (byte)cmd_type.rhr)
            {   // если чтение - вставляем содержание регистра числа регистров
                resp_info.Add("count", (int)((read_array[4] << 8) + read_array[5]));
            }
            else resp_info.Add("count", 1);  // если запись, то читается 1 регистр 

            KeyValuePair<Dictionary<string, int>, List<string>> modbus_container
                                 = new KeyValuePair<Dictionary<string, int>, List<string>>(resp_info, response);
            
            return modbus_container;
}

    }
}