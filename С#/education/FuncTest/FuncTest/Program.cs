using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace FuncTest
{
    class Program
    {
        static void counter(int numberOftic)
        {
            /// считает до numberOftic, выводит на экран

            do
            {
                Console.WriteLine(10 - numberOftic);
                numberOftic--;
                Thread.Sleep(500); // чтобы увидеть
            }
            while (numberOftic != 1); 
            
        }


        static int square (int x)
        {
            int y = x * x;

            return y;
        }
        
        static void Main()
            {
            byte[] CmdBuf = new byte[5];
            byte[] SourceAns = new byte[4];
            string v = "1829";

            SourceAns[0] = 4;
            SourceAns[1] = 0;
            SourceAns[2] = 1;
            SourceAns[3] = 0;
            string Result = "";

            CmdBuf[0] = 0x72;          // 'r'

            int mLenght = v.Length;

            switch (mLenght)
            {
                case 1: v = "000" + v; break;
                case 2: v = "00" + v; break;
                case 3: v = "0" + v; break;
                case 4: break;
            }            
            
            CmdBuf[1] = (byte)v[0];
            CmdBuf[2] = (byte)v[1];
            CmdBuf[3] = (byte)v[2];
            CmdBuf[4] = (byte)v[3];

            string s = System.Text.Encoding.Default.GetString(CmdBuf);
            Result = Convert.ToString(SourceAns[0], 2).PadLeft(3, '0');

            double x = 8.1;
            string str = String.Format("{0:000.0}", x);

            Console.WriteLine(str);
            
            Console.ReadKey();
           }
    }
}
