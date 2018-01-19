using System;

namespace CrissCrossGame
{
    /// <summary>
    /// "Устройство вывода в игре "
    /// </summary>
    class GameOutput
    {
        //--- public -----------------------------------------------------------------
        public static void ShowGame(GameField f)
        {
            // Данный метод можно улучшить, используя табличные символы
            // ANSI-графики:
            // http://en.wikipedia.org/wiki/Box-drawing_characters

            // Граничный символ.
            char box = (char)0x2592;

            // Построчный вывод матрицы и границ.
            for (int y = 0; y < f.Size; y++)
            {
                Console.SetCursorPosition(0, y * 2);

                for (int i = 0; i < f.Size * 2 + 1; i++)
                    Console.Write(box);

                Console.SetCursorPosition(0, y * 2 + 1);

                for (int x = 0; x < f.Size; x++)
                {
                    GameChar gameChar = f.GetChar(x, y);
                    char c = GetChar(gameChar);
                    Console.Write(box);
                    Console.Write(c);
                }

                Console.Write(box);
            }

            // Вывод последней строки.
            Console.SetCursorPosition(0, f.Size * 2);

            for (int i = 0; i < f.Size * 2 + 1; i++)
                Console.Write(box);
        }

        public static void ShowResult(GameChar winner)
        {
            // Идем вниз экрана.
            Console.SetCursorPosition(0, 23);

            // Выводим исход игры.
            switch (winner)
            {
                case GameChar.Null:
                    Console.WriteLine("Ничья.");
                    break;

                case GameChar.Cross:
                    Console.WriteLine("Вы проиграли, увы.");
                    break;

                case GameChar.Zero:
                    Console.WriteLine("Поздравляю! Вы выиграли.");
                    break;
            }
        }

        //--- private ---------------------------------------------------------------
        public static char GetChar(GameChar c)
        {
            switch (c)
            {
                case GameChar.Cross:
                    return 'X';

                case GameChar.Zero:
                    return 'O';

                default:
                    return ' ';
            }
        }
    }
}