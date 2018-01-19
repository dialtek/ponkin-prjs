using System;

namespace CrissCrossGame
{
    /// <summary>
    /// устройство ввода в игре
    /// </summary>
    class GameInput
    {
        public static bool GetInput(out int x, out int y)
        {
            // В цикле дожидаемся допустимой команды.
            // Неизвестные действия просто игнорируем.
            for (; ; )
            {
                Console.CursorVisible = false;
                ConsoleKeyInfo cki = Console.ReadKey(true);

                switch (cki.Key)
                {
                    case ConsoleKey.Escape:
                        x = -1;
                        y = -1;
                        return false;

                    case ConsoleKey.Q:
                        x = 0;
                        y = 0;
                        return true;

                    case ConsoleKey.W:
                        x = 1;
                        y = 0;
                        return true;

                    case ConsoleKey.E:
                        x = 2;
                        y = 0;
                        return true;

                    case ConsoleKey.A:
                        x = 0;
                        y = 1;
                        return true;

                    case ConsoleKey.S:
                        x = 1;
                        y = 1;
                        return true;

                    case ConsoleKey.D:
                        x = 2;
                        y = 1;
                        return true;

                    case ConsoleKey.Z:
                        x = 0;
                        y = 2;
                        return true;

                    case ConsoleKey.X:
                        x = 1;
                        y = 2;
                        return true;

                    case ConsoleKey.C:
                        x = 2;
                        y = 2;
                        return true;

                }
            }
        }
    }
}
