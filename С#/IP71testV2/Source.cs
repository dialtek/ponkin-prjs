using System;
using System.Data;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace IP701testV2
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
            public string GetData(IPEndPoint IpAndPort)
            {
                string Data = "-";

                if (Connect2server(IpAndPort))
                {   // читаем напряжение источника
                    Data = SrcCmd.GetVoltage(ns);
                }
                DisconnectServer();

                return Data;
            }

        /// <summary>
        /// Статус состояния источника
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
            public string GetStatus(IPEndPoint IpAndPort)
            {
                string Status = "-";

                if (Connect2server(IpAndPort))
                {   // читаем статус состояния источника
                    Status = SrcCmd.GetStatus(ns);
                }
                DisconnectServer();

                return Status;
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
            public string SetVoltage(IPEndPoint IpAndPort, String V2set)
            {
                string result_flag = "-1";
                string src_answer;

                if (Connect2server(IpAndPort))
                {
                    src_answer = SrcCmd.SetVoltage(ns, sr, V2set);
                    result_flag = (src_answer == "OK") ? "0" : "1";
                }

                DisconnectServer();
                // result_flag = "-1" - ошибка соединения
                // result_flag = "1"  - успешная установка напряжения
                // result_flag = "0"  - ошибка установки напряжения
                return result_flag;
            }

        /// <summary>
        /// Команда заряда конденсаторов
        /// </summary>
        /// <param name="IpAndPort"></param>
        /// <returns></returns>
            public bool ChargeON(IPEndPoint IpAndPort)
            {
                bool result_flag = false;
                string status = "?";

                if (Connect2server(IpAndPort))
                {
                    status = SrcCmd.ChargeON(ns, sr);
                    if (status == "OK")
                        result_flag = true;
                }
                DisconnectServer();

                return result_flag;
            }

            /// <summary>
            /// Команда разряда конденсаторов
            /// </summary>
            /// <param name="IpAndPort"></param>
            /// <returns></returns>
            public bool ChargeOFF(IPEndPoint IpAndPort)
            {
                bool result_flag = false;
                string status = "?";

                if (Connect2server(IpAndPort))
                {
                    status = SrcCmd.ChargeOFF(ns, sr);
                    if (status == "OK")
                        result_flag = true;
                }
                DisconnectServer();

                return result_flag;
            }

        }
    }