using System;
using System.Data;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace Insitek_src
{
   /// <summary>
   /// Получени данных от источника
   /// </summary>
    public class Source
    {
            private NetworkStream ns;
            private StreamReader sr;
            private Socket server;
            private SourceCommand SrcCmd;

            /// <summary>
            /// Инициализация подключения к серверу
            /// </summary>
            /// <param name="IpAndPort"></param>
            /// <returns></returns>

            public bool Connect2server(IPEndPoint IpAndPort)
            {
                /// подключаемся к удаленному прибору в новом потоке
                ///

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

                        sr = new StreamReader(ns,System.Text.Encoding.ASCII,true);
                        sr.BaseStream.ReadTimeout = 300;
                        SrcCmd = new SourceCommand();
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

            /// <summary>
            /// Запрос на получение данных от указанного источника
            /// </summary>
            /// <returns></returns>
            public string[] GetData(byte SRC_ID, IPEndPoint IpAndPort)
            {
                string[] Data = new string[3];

                Data[0] = ";-";
                Data[1] = ";-";
                Data[2] = ";-";

            if (Connect2server(IpAndPort))
                {   // читаем ток и напряжение источника
                    Data[0] = SrcCmd.GetCurrent(SRC_ID, ns);
                    Data[1] = SrcCmd.GetVoltage(SRC_ID, ns);
                    Data[2] = SrcCmd.GetStatus(SRC_ID, ns);

                }
                DisconnectServer();

                return Data;
            }

            /// <summary>
            /// Запрос на включение выхода источника
            /// </summary>
            /// <param name="IpAndPort"></param>
            /// <returns></returns>
            //public bool SetOutputOn(IPEndPoint IpAndPort)
            //{
            //    bool result_flag = false;
            //    DisconnectServer();
            //    if (Connect2server(IpAndPort))
            //    {
            //        SrcCmd.OutputEnable(ns);
            //        result_flag = true;
            //    }
            //    DisconnectServer();

            //    return result_flag;
            //}

            /// <summary>
            /// Запрос на выключение выхода источника
            /// </summary>
            /// <param name="IpAndPort"></param>
            /// <returns></returns>
            //public bool SetOutputOff(IPEndPoint IpAndPort)
            //{
            //    bool result_flag = false;

            //    if (Connect2server(IpAndPort))
            //    {
            //        SrcCmd.OutputDisable(ns);
            //        result_flag = true;
            //    }
            //    DisconnectServer();

            //    return result_flag;
            //}

            /// <summary>
            /// Запрос на установку величины ограничения напряжения
            /// </summary>
            /// <param name="IpAndPor"></param>
            /// <param name="V2set"></param>
            /// <returns></returns>
            public string SetVoltage(byte SRC_ID, IPEndPoint IpAndPort, ushort V2set)
            {
                string result_flag = "";//"-1";
                string src_answer;

                if (Connect2server(IpAndPort))
                {
                    src_answer = SrcCmd.SetVoltage(SRC_ID, ns, sr, V2set);
                    //result_flag = (src_answer == "") ? "0" : "1";
                }

                DisconnectServer();
                // result_flag = "-1" - ошибка соединения
                // result_flag = "1"  - успешная установка напряжения
                // result_flag = "0"  - ошибка установки напряжения
                return result_flag;
            }

            private string SetID(byte SRC_ID, IPEndPoint IpAndPort, ushort ID2set)
            {
                string result_flag = "-1";

                if (Connect2server(IpAndPort))
                {
                    result_flag = SrcCmd.SetID(SRC_ID, ns, sr, ID2set);
                    //result_flag = (src_answer == "OK") ? "0" : "1";
                }

                DisconnectServer();
                // result_flag = "-1" - ошибка соединения
                // result_flag = "1"  - успешная установка напряжения
                // result_flag = "0"  - ошибка установки напряжения
                return result_flag;
            }

            /// <summary>
        /// Команда управления состоянием выхода источника
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
            public bool SetOutput(byte SRC_ID, IPEndPoint IpAndPort, ushort OutState)
            {
                bool result_flag = false;
                string status = "?";

                if (Connect2server(IpAndPort))
                {
                    status = SrcCmd.SetOutput(SRC_ID, ns, sr, OutState);
                    if (status == "65280") // 0xff00 - ответ источника в случае успешн. уст.
                        result_flag = true;
                }
                DisconnectServer();

                return result_flag;
            }

            /// <summary>
        /// Команда записи настроек в память источника
        /// </summary>
        /// <param name="SRC_ID"></param>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
            public bool Save2EEPROM(byte SRC_ID, IPEndPoint IpAndPort)
            {
                bool result_flag = false;
                string status = "?";

                if (Connect2server(IpAndPort))
                {
                    status = SrcCmd.SaveCfg2EEPROM(SRC_ID, ns, sr);
                    if (status == "65280") // 0xff00 - ответ источника в случае успешн. уст.
                        result_flag = true;
                }
                DisconnectServer();

                return result_flag;
            }

            /// <summary>
        /// Команда чтения статуса выхода
        /// </summary>
        /// <param name="SRC_ID"></param>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
            public string GetOutputStatus(byte SRC_ID, IPEndPoint IpAndPort)
            {
                bool result_flag = false;
                string status = "?";

                if (Connect2server(IpAndPort))
                {
                    status = SrcCmd.GetStatus(SRC_ID, ns);
                    //if (status == "65280") // 0xff00 - ответ источника в случае успешн. уст.
                        //result_flag = true;
                }
                DisconnectServer();

                return status;
            }

        
        }
    }