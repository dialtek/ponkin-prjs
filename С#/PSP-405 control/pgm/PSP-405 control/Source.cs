using System;
using System.Data;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace PSP_405_control
{
    /// <summary>
    /// Получени данных от источника
    /// </summary>
    public class Source
    {
        private NetworkStream ns;
        private StreamReader sr;
        private Socket server;
        private PSP405_commands SrcCmd;
        /// <summary>
        /// Инициализация подключения к серверу
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
        public bool Connect2server(IPEndPoint IpAndPort)
        {
            /// подключаемся к удаленному прибору в новом потоке
            ///
            //String IP = IpAndPort.Substring(0,15);
            //int Port = Convert.ToInt16(IpAndPort.Substring(15,4));

            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            server.ReceiveTimeout = 300;
            try
            {
                IAsyncResult result = server.BeginConnect(IpAndPort, null, null);
                bool success = result.AsyncWaitHandle.WaitOne(300, true);

                if (!success)
                {
                    server.Close();
                    return false;
                }

            }
            catch (Exception)
            {
                server.Close();
                return false;
            }
            //
            try
            {
                if (server.Connected)
                {
                    ns = new NetworkStream(server);
                    ns.ReadTimeout = 300;
                    sr = new StreamReader(ns);
                    sr.BaseStream.ReadTimeout = 300;
                    SrcCmd = new PSP405_commands();
                    return true;
                }
                return false;
            }
            catch (Exception)
            {
                ns.Close();
                sr.Close();
                server.Close();
                return false;
            }
        }

        /// <summary>
        /// Отключение от сервера
        /// </summary>
        public void DisconnectServer()
        {
            /// отключение от сервера и закрытие всех потоков
            /// 
            try
            {
                if (server.Connected)
                {
                    server.Shutdown(SocketShutdown.Both);
                    server.Disconnect(true);
                }
                ns.Close();
                sr.Close();
                server.Close();
            }
            catch (Exception)
            { return; }
        }

        public String GetAllData(IPEndPoint IpAndPort)
        {
            String AllData = "xxxxxxxxxxxxxxxxxxxxxxxxxxx"; //= { "-", "-", "-", "", "" };

            if (Connect2server(IpAndPort))
            {
                AllData = SrcCmd.GetAllData(ns, sr);

            }

            DisconnectServer();

            return AllData;
        }

        /// <summary>
        /// Запрос на получение данных от указанного источника
        /// </summary>
        /// <returns></returns>
        public String[] GetData(IPEndPoint IpAndPort)
        {
            String[] Data = { "-", "-", "-", "", "" };

            if (Connect2server(IpAndPort))
            {  // читаем ток источника
                Data[0] = SrcCmd.GetCurrent(ns, sr);
            }
            DisconnectServer();

            if (Connect2server(IpAndPort))
            {   // читаем напряжение источника
                Data[1] = SrcCmd.GetVoltage(ns, sr);
            }
            DisconnectServer();

            if (Connect2server(IpAndPort))
            {   // читаем статус выхода источника
                Data[2] = SrcCmd.GetOutputStatus(ns, sr);
            }
            DisconnectServer();

            if (Connect2server(IpAndPort))
            {   // читаем лимит напряжения источника
                Data[3] = SrcCmd.GetVoltageLimit(ns, sr);
            }
            DisconnectServer();

            if (Connect2server(IpAndPort))
            {   // читаем лимит тока источника
                Data[4] = SrcCmd.GetCurrentLimit(ns, sr);
            }
            DisconnectServer();

            return Data;
        }

        /// <summary>
        /// Запрос на включение выхода источника
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
        public bool SetOutputOn(IPEndPoint IpAndPort)
        {
            bool result_flag = false;
            DisconnectServer();
            if (Connect2server(IpAndPort))
            {
                SrcCmd.OutputEnable(ns);
                result_flag = true;
            }
            DisconnectServer();

            return result_flag;
        }

        /// <summary>
        /// Запрос на выключение выхода источника
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
        public bool SetOutputOff(IPEndPoint IpAndPort)
        {
            bool result_flag = false;

            if (Connect2server(IpAndPort))
            {
                SrcCmd.OutputDisable(ns);
                result_flag = true;
            }
            DisconnectServer();

            return result_flag;
        }

        /// <summary>
        /// Запрос на установку величины ограничения напряжения
        /// </summary>
        /// <param name="IpAndPor"></param>
        /// <param name="V2set"></param>
        /// <returns></returns>
        public bool SetVoltage(IPEndPoint IpAndPort, String V2set)
        {
            bool result_flag = false;

            if (Connect2server(IpAndPort))
            {
                SrcCmd.SetVoltage(ns, V2set);
                result_flag = true;
            }
            DisconnectServer();

            return result_flag;
        }

        /// <summary>
        /// Запрос на установку величины ограничения тока
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <param name="V_limit"></param>
        /// <returns></returns>
        public bool SetVoltageLimit(IPEndPoint IpAndPort, String V_limit)
        {
            bool result_flag = false;

            if (Connect2server(IpAndPort))
            {
                SrcCmd.SetVoltageLimit(ns, V_limit);
                result_flag = true;
            }
            DisconnectServer();

            return result_flag;
        }

        /// <summary>
        /// Запрос на чтение величины ограничения напряжения
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
        //public static String GetVoltageLimit(IPEndPoint IpAndPort)
        //{
        //    String VoltageLimit = "-";

        //    if (Connect2server(IpAndPort))
        //    {

        //    }
        //    DisconnectServer();

        //    return VoltageLimit;
        //}

        /// <summary>
        /// Запрос на установку величины ограничения тока
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <param name="I_limit"></param>
        /// <returns></returns>
        public bool SetCurrentLimit(IPEndPoint IpAndPort, String I_limit)
        {
            bool result_flag = false;

            if (Connect2server(IpAndPort))
            {
                SrcCmd.SetCurrentLimit(ns, I_limit);
                result_flag = true;
            }
            DisconnectServer();

            return result_flag;
        }

        /// <summary>
        /// Запрос на чтение величины ограничения тока
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
        //public static String GetCurrentLimit(IPEndPoint IpAndPort)
        //{
        //    String CurrentLimit = "-";

        //    if (Connect2server(IpAndPort))
        //    {
        //        CurrentLimit = PSP405_commands.GetCurrentLimit(ns, sr);
        //    }
        //    DisconnectServer();

        //    return CurrentLimit;
        //}



    }
}
