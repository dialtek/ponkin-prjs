using System;

namespace CrissCrossGame
{
    /// <summary>
    /// Игровое поле
    /// </summary>

    class GameField
    {
        //--- members ------------------------------------------------------------------
        private GameChar[,] mMatrix;
        private int mSize;


        //--- public -------------------------------------------------------------------
        public GameField(int size)
        {
            mMatrix = new GameChar[size, size];
            mSize = size;

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    mMatrix[i, j] = GameChar.Null;
                }
            }
        }

        /// <summary>
        /// Установить символ
        /// </summary>
        public void SetChar(GameChar c, int x, int y)
        {
            mMatrix[x, y] = c;
        }

        /// <summary>
        /// Получить символ
        /// </summary>
        public GameChar GetChar(int x, int y)
        {
            return mMatrix[x, y];
        }

        /// <summary>
        /// Размер матрицы
        /// </summary>
        public int Size
        {
            get { return mSize;  }
        }
    }

    /// <summary>
    /// Игровой символ
    /// </summary>
    enum GameChar
    {
        Null, Cross, Zero
    }
}
