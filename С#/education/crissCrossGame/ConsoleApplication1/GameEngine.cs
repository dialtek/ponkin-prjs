using System;

namespace CrissCrossGame
{
    /// <summary>
    /// Движок игры
    /// </summary>
    class GameEngine
    {

        /// Инициализация игрового поля
        public static GameField Start(int size)
        {
            // Инициализация игрового поля.
            GameField f = new GameField(size);
            return f;
        }

        /// Ход компьютера
        public static bool PutComputerChar(GameField f)
        {
            //
            // Нужно переделать, слишком уж тупая реализация.
            //
            for (int i = 0; i < f.Size; i++)
            {
                for (int j = 0; j < f.Size; j++)
                {
                    if (f.GetChar(i, j) == GameChar.Null)
                    {
                        f.SetChar(GameChar.Cross, i, j);
                        return true;
                    }
                }
            }

            return false;
        }

        /// Ход пользователя
        public static bool PutUserChar(GameField f, int x, int y)
        {
            if (f.GetChar(x, y) == GameChar.Null)
            {
                f.SetChar(GameChar.Zero, x, y);
                return true;
            }
            else
            {
                return false;
            }
        }

        /// Окончена ли игра
        public static bool IsGameFinished(GameField f)
        {
            if (CheckVictory(f, GameChar.Cross))
                return true;

            if (CheckVictory(f, GameChar.Zero))
                return true;

            return !CheckFreeSpace(f);
        }

        /// Кто победитель
        public static GameChar GetWinner(GameField f)
        {
            if (CheckVictory(f, GameChar.Cross))
                return GameChar.Cross;

            if (CheckVictory(f, GameChar.Zero))
                return GameChar.Zero;

            return GameChar.Null;
        }

        //--- private -------------------------------------------------

        /// Победитель ли "c"
        /// 
        private static bool CheckVictory(GameField f, GameChar c)
        {
            //
            // Этот метод нужно реализовать.
            // Сейчас игра всегда заканчивается ничьей.
            //
            int cWinCountX = 0;
            int cWinCountY = 0;
            int cWinCountZ = 0;

            for (int i = 0; i < f.Size; i++)
            {
                    if (f.GetChar(i, 0) == c)
                        cWinCountX++;

                    if (f.GetChar(i, 1) == c)
                        cWinCountY++;

                    if (f.GetChar(i, 2) == c)
                        cWinCountZ++;

                    if (cWinCountX > 2 || cWinCountY > 2 || cWinCountZ > 2)
                        return true;  
            }

            return false;
        }

        /// Есть ли пустые клетки
        /// 
        private static bool CheckFreeSpace(GameField f)
        {
            for (int i = 0; i < f.Size; i++)
            {
                for (int j = 0; j < f.Size; j++)
                {
                    if (f.GetChar(i, j) == GameChar.Null)
                        return true;
                }
            }

            return false;
        } 

    }
}

