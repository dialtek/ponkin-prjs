using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PSP_405_control
{
    /// <summary>
    /// Команды для обращения к источнику питания PSP-405
    /// </summary>

    public class PSP405_commands
    {
        private int delay = 400;
        public bool Init(NetworkStream ns)
        {
            /// команда инициализации источника
            /// установка пределов I и U на максимум

            try
            {
                SetMaxU(ns);
                Thread.Sleep(100);
                SetMaxI(ns);
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        public String GetAllData(NetworkStream ns, StreamReader sr)
        {
            string AllData;
            int count = 0;
            // подача команды на чтение напряжения
            ns.Write(Encoding.ASCII.GetBytes("L\r"), 0, 2);
            while (!ns.DataAvailable)
            {
                if (count >= 10)
                {
                    // искусственный таймаут чтения...
                    AllData = "*";
                    break;
                }
                count++;
                Thread.Sleep(1);
            }
            try
            {
                do
                {
                    AllData = sr.ReadLine();
                    Thread.Sleep(1);
                }
                while (!AllData.StartsWith("V"));
            }
            catch (System.IO.IOException)
            {
                // действие при отключении питания источника
                AllData = "*";
            }
            // выбрасываем в ответе источника все, что до V включительно
            if (AllData.StartsWith("V"))
            {
                AllData = AllData.Split('V')[1];
            }

            return AllData; //.Substring(0,voltage.Length-1);
        }

        /// <summary>
        /// Команда запроса напряжения
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string GetVoltage(NetworkStream ns, StreamReader sr)
        {  
            string voltage;
            int count = 0;
            // подача команды на чтение напряжения
            ns.Write(Encoding.ASCII.GetBytes("V\r"), 0, 2);
            while (!ns.DataAvailable) 
            {
                if ( count >= 10)
                {  
                    // искусственный таймаут чтения...
                    voltage = "*";
                    break;
                }
                count++;
                Thread.Sleep(1);
            }
            try
            {
                do
                {
                    voltage = sr.ReadLine();
                    //Thread.Sleep(1); 
                }
                while (!voltage.StartsWith("V"));
            }
            catch (System.IO.IOException)
            { 
              // действие при отключении питания источника
              voltage = "*";
            }
            // выбрасываем в ответе источника все, что до V включительно
            if (voltage.Contains("V"))
            {
              voltage = voltage.Split('V')[1];
            }

            return voltage; //.Substring(0,voltage.Length-1);
        }

        /// <summary>
        /// Команда установки напряжения
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="V2set"></param>
        /// <returns></returns>
        public bool SetVoltage(NetworkStream ns, String V2set)
        {
            /// команда установки напряжения
            /// 
            if (V2set == null) return false;

            int mLenght = V2set.Length;

            switch (mLenght)
            {
                case 1: V2set = "0" + V2set + ".00"; break;
                case 2: V2set = V2set + ".00";       break;
                case 3: V2set = "0" + V2set + "0";   break;
                case 4:
                    String[] SplittedV2set = V2set.Split('.');
                    if (SplittedV2set[0].Length == 2) V2set =  V2set + "0";
                    if (SplittedV2set[1].Length == 2) V2set = "0" + V2set;
                break;
                case 5: break;
            }
                try
                {
                    ns.Write(Encoding.ASCII.GetBytes("SV " + V2set + "\r"), 0, 9);
                    
                    ns.Flush();
                    Thread.Sleep(delay);
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }
        }

        /// <summary>
        /// Команда установки ограничения по напряжению
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="V_limit"></param>
        /// <returns></returns>
        public bool SetVoltageLimit(NetworkStream ns, String V_limit)
        {
            /// команда установки напряжения
            /// 
            if (V_limit.Length < 2)
                V_limit = "0" + V_limit;
            try
            {
                ns.Write(Encoding.ASCII.GetBytes("SU " + V_limit + "\r"), 0, 6);
                
                ns.Flush();
                Thread.Sleep(delay);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// Команда чтения ограничения по напряжению
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public String GetVoltageLimit(NetworkStream ns, StreamReader sr)
        {
            /// команда запроса величины лимита напряжения
            /// 
                string voltageLimit;
                int count = 0;
                // подача команды на чтение лимита напряжения
                ns.Write(Encoding.ASCII.GetBytes("U\r"), 0, 2);
                while (!ns.DataAvailable)
                {
                    if (count >= 10)
                    {
                        // искусственный таймаут чтения...
                        voltageLimit = "*";
                        break;
                    }
                    count++;
                    Thread.Sleep(1);
                }
                try
                {
                    do
                    {
                        voltageLimit = sr.ReadLine();
                        //Thread.Sleep(1);
                    }
                    while (!voltageLimit.StartsWith("U"));
                }
                catch (System.IO.IOException)
                {
                    // действие при отключении питания источника
                    voltageLimit = "*";
                }
                // выбрасываем в ответе источника все, что до U включительно
                if (voltageLimit.Contains("U"))
                {
                    voltageLimit = voltageLimit.Split('U')[1];
                }

                return voltageLimit;
        }

        /// <summary>
        /// Команда запроса тока 
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public string GetCurrent(NetworkStream ns, StreamReader sr)
        {
            /// команда запроса напряжения
            string current;
            int count = 0;
            // подача команды на чтение тока
            ns.Write(Encoding.ASCII.GetBytes("A\r"), 0, 2);
            while (!ns.DataAvailable)
            {
                if (count >= 10)
                {
                    // искусственный таймаут чтения...
                    current = "*";
                    break;
                }
                count++;
                Thread.Sleep(1);
            }
            try
            {
                do
                {
                    current = sr.ReadLine();
                    //Thread.Sleep(1);
                }
                while (!current.StartsWith("A"));
            }
            catch (System.IO.IOException)
            {
                // действие при отключении питания источника
                current = "*";
            }
            // выбрасываем в ответе источника все, что до A включительно
            if (current.Contains("A"))
            { 
            current = current.Split('A')[1];
            current = current.Substring(0,current.Length-1);
            }
            current = current.Replace(".",",");
            return current;
        }

        /// <summary>
        /// Команда установки ограничения по току
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="V_limit"></param>
        /// <returns></returns>
        public bool SetCurrentLimit(NetworkStream ns, String I_limit)
        {
            if (I_limit.Length < 0) return false;

                int mLenght = I_limit.Length;

            switch (mLenght)
            {
                case 1: I_limit = I_limit + ".00"; break;
                case 3: I_limit = I_limit + "0";   break;

            }
            try
            {
                ns.Write(Encoding.ASCII.GetBytes("SI " + I_limit + "\r"), 0, 8);
                ns.Flush();
                Thread.Sleep(delay);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// Команда чтения ограничения по току
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public String GetCurrentLimit(NetworkStream ns, StreamReader sr ) 
        {
            /// команда запроса величины лимита тока
            /// 
            string CurrentLimit;
            int count = 0;
            // подача команды на чтение лимита тока
            ns.Write(Encoding.ASCII.GetBytes("I\r"), 0, 2);
            while (!ns.DataAvailable)
            {
                if (count >= 10)
                {
                    // искусственный таймаут чтения...
                    CurrentLimit = "*";
                    break;
                }
                count++;
                //Thread.Sleep(1);
            }
            try
            {
                do
                {
                    CurrentLimit = sr.ReadLine();
                    //Thread.Sleep(1);
                }
                while (!CurrentLimit.StartsWith("I"));
            }
            catch (System.IO.IOException)
            {
                // действие при отключении питания источника
                CurrentLimit = "*";
            }
            // выбрасываем в ответе источника все, что до I включительно
            if (CurrentLimit.Contains("I"))
            {
                CurrentLimit = CurrentLimit.Split('I')[1];
            }

            return CurrentLimit;
        }

        /// <summary>
        /// Команда запроса статуса выхода источника 
        /// </summary>
        /// <param name="ns"></param>
        /// <param name="sr"></param>
        /// <returns></returns>
        public String GetOutputStatus(NetworkStream ns, StreamReader sr)
        {
            // команда запроса статуса источника питания

            string status;
            int count = 0;
            // подача команды на чтение статуса выхода
            ns.Write(Encoding.ASCII.GetBytes("F\r"), 0, 2);
            while (!ns.DataAvailable)
            {
               if (count >= 10)
                  {
                      // искусственный таймаут чтения...
                      status = "*";
                      break;
                   }
              count++;
              Thread.Sleep(1);
             }
             try
             {
               do
                 {
                     status = sr.ReadLine();
                     //Thread.Sleep(1);
                 }
               while (!status.StartsWith("F"));
              }
                catch (System.IO.IOException)
                {
                    // действие при отключении питания источника
                    status = "*";
                }
            // выбрасываем в ответе источника все, что до F включительно
             if (status.Contains("F"))
             { 
                 status = status.Split('F')[1];            
                 if (status.Substring(0,1) == "1")
                    status   = "Вкл.";
                 else status = "Выкл.";
             }
            
            return status;
        }

        public void GetLoad(NetworkStream ns)
        {
            // команда запроса текущей рассеиваемой мощности источника питания
            ns.Write(Encoding.ASCII.GetBytes("W\r"), 0, 2);
        }

        public void SetMaxU(NetworkStream ns)
        {
            // Set the maximum voltage limit value.
            // the power supply will set the voltage limit to the maximum immediately.

            ns.Write(Encoding.ASCII.GetBytes("SUM\r"), 0, 4);
        }

        public void SetMaxI(NetworkStream ns)
        {
            // Set the maximum Current limit value.
            // the power supply will set the Current limit to the maximum immediately.

            ns.Write(Encoding.ASCII.GetBytes("SIM\r"), 0, 4);
        }

        public void OutputEnable(NetworkStream ns)
        {
            // Set the Relay status to ON.
            // надо переделать чтобы дожидалась вкл. выхода анализируя 
            // его состояние командой GetStatus
                try
                {
                    ns.Write(Encoding.ASCII.GetBytes("KOE\r"), 0, 4);
                    Thread.Sleep(delay);
                }
                catch (Exception)
                { return; }
        
        }
        
        public void OutputDisable(NetworkStream ns)
        {
            // Set the Relay status to OFF.

                try
                {
                    ns.Write(Encoding.ASCII.GetBytes("KOD\r"), 0, 4);
                    Thread.Sleep(delay);
  
                }
                catch (Exception)
                { return; }
        }
    }

}