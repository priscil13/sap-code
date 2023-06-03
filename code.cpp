# sap-code
using System;

class Minesweeper
{
    private const int BoardSize = 10;
    private const int MineCount = 10;

    private bool[,] mines = new bool[BoardSize, BoardSize];
    private int[,] counts = new int[BoardSize, BoardSize];
    private bool[,] revealed = new bool[BoardSize, BoardSize];
    private bool gameover = false;

    private Random random = new Random();

    public void Initialize()
    {
        Console.Title = "Minesweeper";
        Console.CursorVisible = false;

        GenerateMines();
        CalculateCounts();

        Console.WriteLine("Welcome to Minesweeper!");
        Console.WriteLine("Instructions:");
        Console.WriteLine(" - Use arrow keys to move the cursor.");
        Console.WriteLine(" - Press 'Enter' to reveal a cell.");
        Console.WriteLine(" - Press 'Q' to quit the game.");

        Console.WriteLine();
        Console.WriteLine(" - 'X' represents an unopened cell.");
        Console.WriteLine(" - '#' represents a mine.");
        Console.WriteLine(" - Numbers represent the count of surrounding mines.");

        Console.WriteLine();
        Console.WriteLine("Good luck!");
        Console.WriteLine();
    }

    private void GenerateMines()
    {
        int count = 0;
        while (count < MineCount)
        {
            int x = random.Next(BoardSize);
            int y = random.Next(BoardSize);

            if (!mines[x, y])
            {
                mines[x, y] = true;
                count++;
            }
        }
    }

    private void CalculateCounts()
    {
        for (int x = 0; x < BoardSize; x++)
        {
            for (int y = 0; y < BoardSize; y++)
            {
                if (mines[x, y])
                    continue;

                int count = 0;

                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < BoardSize && ny >= 0 && ny < BoardSize && mines[nx, ny])
                            count++;
                    }
                }

                counts[x, y] = count;
            }
        }
    }

    public void Play()
    {
        int cursorX = 0;
        int cursorY = 0;

        while (!gameover)
        {
            Console.Clear();
            DrawBoard(cursorX, cursorY);

            ConsoleKeyInfo keyInfo = Console.ReadKey(true);
            switch (keyInfo.Key)
            {
                case ConsoleKey.UpArrow:
                    if (cursorY > 0)
                        cursorY--;
                    break;
                case ConsoleKey.DownArrow:
                    if (cursorY < BoardSize - 1)
                        cursorY++;
                    break;
                case ConsoleKey.LeftArrow:
                    if (cursorX > 0)
                        cursorX--;
                    break;
                case ConsoleKey.RightArrow:
                    if (cursorX < BoardSize - 1)
                        cursorX++;
                    break;
                case ConsoleKey.Enter:
                    RevealCell(cursorX, cursorY);
                    break;
                case ConsoleKey.Q:
                    gameover = true;
                    break;
            }

            if (CheckWin())
            {
                Console.Clear();
                DrawBoard(cursorX, cursorY);
                Console.WriteLine("Congratulations! You won!");
                Console.WriteLine("Press any key to exit.");
                Console.ReadKey();
                gameover = true;
            }
        }
    }

    private void Draw
