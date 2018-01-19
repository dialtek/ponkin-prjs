using System;
using System.Threading;

namespace CrissCrossGame
{
    class Program
    {
            static void Main(string[] args)
        {
            //
            // Здесь нужно написать подробные комментарии для каждого кусочка 
            // кода.
            //
            GameField f = GameEngine.Start(3); // создается игровое поля 3 на 3
            bool userExit = false;             // обнуляем флаг хода пользователя

            GameOutput.ShowGame(f);            // рисуем игровое поле
            Thread.Sleep(500);                 // спим 500 мс, разгружаем ЦП

            while (!userExit && !GameEngine.IsGameFinished(f)) // пока пользователь не вышел  
            {                                                  // или не выполн. усл. остановки игры..
                GameEngine.PutComputerChar(f);                 // Компьютер совершает ход
                GameOutput.ShowGame(f);                        // Рисуем игровое поле с рез. хода ком.

                if (!GameEngine.IsGameFinished(f))             // пока игра не окончена ...         
                {
                    int x, y;

                    userExit = !GameInput.GetInput(out x, out y); // обрабатываем ход пользователя

                    while (!userExit && !GameEngine.PutUserChar(f, x, y)) // сидим тут пока пользов.
                        userExit = !GameInput.GetInput(out x, out y);     // не выполн. ход или не вышел
                    // обрабатываем ход пользователя 
                    if (!userExit)
                    {
                        // рисуем поле с результатом хода пользователя
                        GameOutput.ShowGame(f);
                        Thread.Sleep(500);
                    }
                }
            }

            if (!userExit)
            {
                // анализируем флаг конца игры и запоминанем выйгравшего

                GameChar winner = GameEngine.GetWinner(f);
                GameOutput.ShowResult(winner);
                Console.ReadKey(true);
            }
        
        }
    }
}
