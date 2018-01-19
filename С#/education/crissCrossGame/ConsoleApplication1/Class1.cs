using System;

namespace ConsoleApplication1
{
    /// <summary>
    /// Игровое поле
    /// </summary>

    class GameField
    {
        private GameChar[,] mMatrix;
        private int mSize;

        public GameField(int size)
        {
            mMatrix = new GameChar[size, size];
            mSize = size;

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    mMatrix[i,j] = GameChar.Null;
                }
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
    /// Установить символ
    /// </summary>
    public void GetChar(GameChar c, int x, int y) 
    {
      return mMatrix[x, y];
    }


    /// <summary>
    /// Получить символ
    /// </summary>
    enum GameChar
    {
        Null, Cross, Zero
    }


}
