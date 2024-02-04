# 🐍 Snake-Game 🎮

Snake-Game is a classic Snake game implementation in C++ with various front-end realizations, including a Qt-based version and a C# console version. The project leverages the `Snaky` library for the core game logic, offering convenient interfaces for controlling the game.

## Project Structure 📁

```markdown
Snake-Game
│
├── CPP-QtSnakeGame
│   ├── CSnakeGame         # CMake project for the Qt-based version
│   ├── QSnakeGame         # QMake project for the Qt-based version
│   └── Release            # Contains the released executable files
│
├── CSharpSnakeGame        # C# console front-end realization
│   ├── CSharpSnakeGame    # Source files for the C# version
│   └── Release            # Contains the released executable files
│
├── Snaky                  # C++ source folder for the Snaky library
└── SnakyC                 # C source folder for the Snaky library wrapper
```

## Snaky Library Interface 🐍⚒️

The `Snaky` library provides interfaces for controlling the snake, managing game state, and retrieving positions. Below are the key functions and types offered by the `Snaky` library:

- **C++ Interface**:
  - `Snaky(int initialX, int initialY, int size, const std::pair<int, int>& initialDirection)`: Constructor to create a new snake instance with the specified initial position, size, and direction.
  - `bool turn(const std::pair<int, int>& newDirection)`: Turns the snake in the specified direction.
  - `MoveResult nextStep()`: Moves the snake one step forward and returns the result.
  - `std::pair<int, int> getApplePosition() const`: Retrieves the position of the apple.
  - `std::pair<int, int> getHeadPosition() const`: Retrieves the position of the snake's head.
  - `void getSnakePositions(int*& positionsArray, int& arrayLength) const`: Retrieves an array of positions occupied by the snake.
  
  **Note**: The function getSnakePositions() has a time complexity of O(n), while all other operations are of complexity O(1).
  It is provided as an optional function for easy front-end development. For improved time performance, consider using a linked list to store the snake positions in the front end.

- **C Interface**:
  - `SnakyHandle Snaky_create(int initialX, int initialY, int size, int initialDirectionX, int initialDirectionY)`: Creates a new snake instance with the specified parameters and returns a handle to it.
  - `void Snaky_destroy(SnakyHandle handle)`: Destroys the snake instance.
  - `int Snaky_turn(SnakyHandle handle, int newDirectionX, int newDirectionY)`: Turns the snake with the specified direction.
  - `int Snaky_nextStep(SnakyHandle handle)`: Moves the snake one step forward.
  - `void Snaky_getApplePosition(SnakyHandle handle, int* x, int* y)`: Retrieves the position of the apple.
  - `void Snaky_getHeadPosition(SnakyHandle handle, int* x, int* y)`: Retrieves the position of the snake's head.
  - `void Snaky_getSnakePositions(SnakyHandle handle, int** positionsArray, int* arrayLength)`: Retrieves an array of positions occupied by the snake.

These interfaces allow easy integration of the snake logic into various front-end implementations, providing flexibility and convenience for developers.

## Examples for Front Ends 🌇

### Qt-based Version

The Qt-based version of Snake-Game offers a visually appealing graphical user interface implemented using the Qt framework. Below are the key components and functionalities of the front-end implementation:

- **MainWindow Class**: This class represents the main window of the application. It is responsible for:
  - Initializing the game board and setting up the graphical elements.
  - Handling user interactions, such as key presses for controlling the snake.
  - Managing the visualization of the game, including updating the positions of the snake, apple, and game board.

- **SnakeGame Class**: This class inherits from the MainWindow class and implements the game logic using the `Snaky` library. It includes functionality for:
  - Initializing the game state and starting the game loop.
  - Updating the game state based on user input and the snake's movements.
  - Handling collision detection, including detecting collisions with walls, the snake's body, and the apple.
  - Displaying messages for game over scenarios or victory.

The source code for the Qt-based version of Snake-Game can be found in the `CPP-QtSnakeGame` directory. Specifically, the implementation is split into the `CSnakeGame` and `QSnakeGame` subdirectories, depending on whether CMake or QMake is used for building the project.

<div align="center">
  <img src="https://github.com/JeongHan-Bae/Snake-Game/blob/main/CPP-QtSnakeGame/CSnakeGame/Snaky.png" alt="Snaky">
</div>

### C# Console Version

#### SnakyWrapper Class

The `SnakyWrapper` class acts as a bridge between the C# console application and the underlying C library, `libSnaky_wrapper.dll`. It simplifies interaction with the game logic by providing methods to:

- Create and manage instances of the `Snaky` class.
- Control the snake's movement by turning it in different directions.
- Advance the game state by moving the snake forward.
- Retrieve the positions of the apple and the snake's head.
- Access the positions of all segments of the snake for display purposes.

#### Program Class

The `Program` class orchestrates the game's execution in the console environment. It follows a familiar logic similar to the Qt-based version but utilizes the console for output. Key features include:

- Initialization of game components, including the `SnakyWrapper` instance and the game grid.
- A game loop that manages the flow of the game, handling the snake's movements and user input.
- Simple input handling to control the snake's direction using keyboard arrow keys.
- Visualization of the game state in the console window, depicting the snake, the apple, and the empty spaces using characters.

The C# console version provides an accessible and straightforward way to enjoy the classic Snake game, making it easy for players to immerse themselves in the gameplay directly from the command-line interface.

## Cross-Platform Compatibility 🛠️🗺️

The `Snaky` library is designed to be platform-independent, easily integrating into non-Qt implementations or other languages like C#. The dynamic libraries (`libSnaky.dll` and `libSnaky_wrapper.dll`) provides a seamless way to incorporate the core game logic into various environments.

## License 📜

Snake-Game is distributed under the [MIT License](LICENSE). Feel free to use it freely, and for any questions or suggestions, please contact the author at mastropseudo@gmail.com.

🚀 Feel the thrill of the Snake game! Dive into the code and unleash your creativity. With `Snaky` library at your disposal, you can craft exciting front-end experiences on any platform you desire. Let's create some gaming magic together! 🎉
