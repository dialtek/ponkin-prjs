using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MovAverTest
{
    class Program
    {
        static void Main(string[] args)
        {

            int k = 0;  // индекс массива
            int m = 0;  // переменная усреднения
            int n = 10;  // размер буфера усреднения

            double sample = 1;
            double sum = 0;
            double aver = 0;

            double[] buf = new double[10];

            for (int i = 0; i < 10; i++)
            {
                if (m >= n) // буфер усреднения заполнился?
                    sum = sum - buf[k] + sample; // удаление предыдущего эл, добавление нового
                else
                {   // нет
                    sum += sample;      // копим сумму
                    m++;
                }
                buf[k] = sample;    // сохр. нового значения для след. итерации
                aver = sum / m;     // расчет среднего значения 
                k++;                // инкремент индекса массива
                if (k >= n) k = 0;  // сброс индекса если переполнился
                sample++;
            }
            Console.WriteLine("sample = " + sample.ToString());
            Console.ReadKey();

        }
    }
}
