using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace psp405_cmd_parse
{
    class Program
    {
        static void Main(string[] args)
        {
            
            char[] in_array1 = { 'V', '0', '2', '1', '2','\r', '\n' };
            char[] in_array2 = { 'A', '3', '.', '0', '7', '5','\r', '\n',
                                 'V', '0', '2', '1', '2','\r', '\n'};
            int rx_msg = 0;
            int V_index = 0;

            for (int i = 0; i < in_array2.Length; i++)
            {
                if (in_array2[i] == '\n')
                    rx_msg = 1;

                if (in_array2[i] == 'V')
                {
                    V_index = i;
                    in_array2[i] = 'W';
                }
            }

            if (rx_msg == 1)
            {
                rx_msg = 0;

                for (int i = V_index + 1; i < V_index+5; i++)
                    Console.Write(in_array2[i].ToString());
            }
            Console.ReadKey();




        }
    }
}
