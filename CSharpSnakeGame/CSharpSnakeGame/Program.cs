using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace CSharpSnakeGame
{
    internal class Program
    {
        // Snaky Attributes
        private static SnakyWrapper _snaky;
        private static bool _gameOver;
        private static IntPair _headPosition;
        private static readonly LinkedList<IntPair> SnakePositions = new LinkedList<IntPair>();
        private static IntPair _currDirection = new IntPair { First = 1, Second = 0 };
        private static IntPair _direction = new IntPair { First = 1, Second = 0 };

        // Attributes for grid and colors
        private static char[,] _grid;
        private static ConsoleColor[,] _colors;
        private const char BlockChar = '\u25a0'; // Unicode block character
        private static char _headChar = '\0';
        
        // Directions
        private static readonly IntPair North = new IntPair(0, -1);
        private static readonly IntPair South = new IntPair(0, 1);
        private static readonly IntPair West = new IntPair(-1, 0);
        private static readonly IntPair East = new IntPair(1, 0);

        // Colors
        private const ConsoleColor SnakeColor = ConsoleColor.Green;
        private const ConsoleColor EmptyColor = ConsoleColor.DarkGray;
        private const ConsoleColor AppleColor = ConsoleColor.Red;
        private const ConsoleColor HeadColor = ConsoleColor.Yellow;

        public static void Main(string[] args)
        {
            Console.WriteLine("Welcome to CSharp Snake Game by JH Bae");
            Thread.Sleep(500); // Wait for 500 milliseconds

            Console.WriteLine("Ready:");
            Thread.Sleep(300); // Wait for 300 milliseconds

            // Countdown
            for (int i = 3; i > 0; i--)
            {
                Console.Write(i);
                Thread.Sleep(100);
                Console.Write(".");
                Thread.Sleep(100);
                Console.Write(".");
                Thread.Sleep(100);
                Console.Write(".");
                Thread.Sleep(700);
                Console.Write("\r");
            }

            Console.WriteLine("GO!");
            Thread.Sleep(200); // Wait for 200 milliseconds

            Console.Clear(); // Clear the console screen

            _snaky = new SnakyWrapper(0, 0, 10, new IntPair { First = 1, Second = 0 });

            // Add initial head position to the snake positions
            _headPosition = _snaky.GetHeadPosition();
            SnakePositions.AddLast(_headPosition);

            // Initialize grid and colors
            InitializeGrid(10, 10); // Adjust the grid size as needed

            // Visualize initial game state
            VisualizeGame();

            // Thread for handling time intervals
            Thread timeThread = new Thread(TimeLoop);
            timeThread.Start();

            // Thread for capturing keyboard input
            Thread inputThread = new Thread(InputLoop);
            inputThread.Start();

            // Wait for both threads to finish
            timeThread.Join();
            inputThread.Join();
            
        }

        private static void TimeLoop()
        {
            while (!_gameOver)
            {
                Thread.Sleep(300); // Wait for 500 milliseconds
                
                if (_snaky.Turn(_direction))
                {
                    _currDirection = _direction;
                }
                
                MoveResult res = _snaky.NextStep();

                String msg = "";
                var prev = SnakePositions.Last();
                var tail = SnakePositions.First();

                if (res == MoveResult.Win)
                {
                    msg = "WIN\nPress Any Key to Quit";
                    UpdateHead();
                    _grid[_headPosition.First,_headPosition.Second] = _headChar; // Set head char
                    _gameOver = true;
                }
                else if (res == MoveResult.Wall || res == MoveResult.Self)
                {
                    msg = "LOST: " + (res == MoveResult.Wall ? "Hit the Wall" : "Bit Yourself") + "\nPress Any Key to Quit";
                    UpdateHead();
                    _grid[_headPosition.First,_headPosition.Second] = _headChar; // Set head char
                    _gameOver = true;
                }

                // Update head position and snake positions
                _headPosition = _snaky.GetHeadPosition();
                if (res == MoveResult.Apple)
                {
                    
                    _grid[prev.First,prev.Second] = BlockChar; // Set prev char
                    _colors[prev.First,prev.Second] = SnakeColor; // Set prev color
                    SnakePositions.AddLast(_headPosition);
                    UpdateHead();
                    _grid[_headPosition.First,_headPosition.Second] = _headChar; // Set head char
                    _colors[_headPosition.First,_headPosition.Second] = HeadColor; // Set head color
                    // Renew apple position
                    RenewApplePosition();
                    // Clear the console screen and visualize the game
                }
                else if (res == MoveResult.Void)
                {
                    
                    _grid[prev.First,prev.Second] = BlockChar; // Set prev char
                    _colors[prev.First,prev.Second] = SnakeColor; // Set prev color
                    _grid[tail.First,tail.Second] = BlockChar; // Set void char
                    _colors[tail.First,tail.Second] = EmptyColor; // Set void color
                    SnakePositions.AddLast(_headPosition);
                    SnakePositions.RemoveFirst();
                    UpdateHead();
                    _grid[_headPosition.First,_headPosition.Second] = _headChar; // Set head char
                    _colors[_headPosition.First,_headPosition.Second] = HeadColor; // Set head color
                    // Clear the console screen and visualize the game
                    
                }
                Console.Clear();
                VisualizeGame();
                Console.WriteLine(msg);
            }
        }

        private static void InputLoop()
        {
            while (!_gameOver)
            {
                var keyInfo = Console.ReadKey(true);

                switch (keyInfo.Key)
                {
                    case ConsoleKey.UpArrow:
                        _direction = North;
                        break;
                    case ConsoleKey.DownArrow:
                        _direction = South;
                        break;
                    case ConsoleKey.LeftArrow:
                        _direction = West;
                        break;
                    case ConsoleKey.RightArrow:
                        _direction = East;
                        break;
                    default:
                        continue; // Ignore other keys
                }
            }
        }

        private static void VisualizeGame()
        {
            // Visualize the grid
            Console.Clear(); // Clear the console screen
            for (int j = 0; j < _grid.GetLength(1); j++)
            {
                for (int i = 0; i < _grid.GetLength(0); i++)
                {
                    Console.ForegroundColor = _colors[i, j];
                    Console.Write(_grid[i, j] + " ");
                }
                Console.WriteLine();
            }
            Console.ResetColor(); // Reset color to default
        }

        private static void InitializeGrid(int maxX, int maxY)
        {
            // Initialize grid and colors with default values
            _grid = new char[maxX, maxY];
            _colors = new ConsoleColor[maxX, maxY];

            // Fill grid with block characters and set colors
            for (int i = 0; i < maxX; i++)
            {
                for (int j = 0; j < maxY; j++)
                {
                    _grid[i, j] = BlockChar; // Set each cell to the block character
                    _colors[i, j] = EmptyColor;
                }
            }

            // Add apple to grid
            RenewApplePosition();

            UpdateHead();
            _grid[_headPosition.First, _headPosition.Second] = _headChar; // Set head char
            _colors[_headPosition.First, _headPosition.Second] = HeadColor; // Set head color
        }

        private static void UpdateHead()
        {
            switch (_currDirection)
            {
                case var direction when direction.Equals(North):
                    _headChar = '^';
                    break;
                case var direction when direction.Equals(South):
                    _headChar = 'v';
                    break;
                case var direction when direction.Equals(West):
                    _headChar = '<';
                    break;
                case var direction when direction.Equals(East):
                    _headChar = '>';
                    break;
            }
        }


        private static void RenewApplePosition()
        {
            var applePos = _snaky.GetApplePosition();
            _colors[applePos.First, applePos.Second] = AppleColor;
        }
    }
}
