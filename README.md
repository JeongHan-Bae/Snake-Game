# Snake-Game

Snake-Game is a versatile C++ implementation of the classic Snake game utilizing the Qt framework for visualization. The project is organized into two main components: the core game logic provided in the `Snaky` library and the Qt visualization in the `SnakeGame` folder.

## Snaky Library

The `Snaky` library encapsulates the game logic and is conveniently included within the Qt source folder. For non-Qt implementations, a dynamic link library (DLL) version is available at `Snake-Game/Snaky/cmake-build-debug/libSnaky.dll`. The library includes the following files:

- `Snaky/Snaky.h`: Header file containing the `Snaky` class declaration.
- `Snaky/SnakyImpl.cpp` and `Snaky/SnakyImpl.h`: Implementation files for the `Snaky` class.

### Snaky Class

The `Snaky` class represents the core game logic and includes methods for controlling the snake's movement, retrieving positions, and handling the game's state. Notable members include static constants for cardinal directions and methods such as `turn`, `nextStep`, and `getSnakePositions`.

## SnakeGame Qt Visualization

The Qt visualization of the Snake game is provided in the `SnakeGame` folder. The main application is implemented in the `SnakeGame` class, extending `QGraphicsView`. Key features include handling user input, updating the game state, and displaying the game using the Qt framework.

### SnakeGame Class

The `SnakeGame` class manages the graphical representation of the game using the Qt graphics framework. It includes methods for handling key events, updating the game state, and drawing the scene. Notable features include a timer for continuous updates, initialization functions, and methods for handling game over scenarios.

## Usage

1. Navigate to the Qt source folder containing all the source files.
2. Build the `Snaky` library for non-Qt implementations if needed.
3. Build and run the Qt application using the provided `main` function in `SnakeGame/SnakeGame/main.cpp`.

## Cross-Platform Compatibility

The `Snaky` library is designed to be platform-independent and can be easily integrated into non-Qt implementations or other languages such as C#. The dynamic library (`libSnaky.dll`) provides a seamless way to incorporate the core game logic into various environments.

## License

Snake-Game is distributed under the [MIT License](LICENSE). Feel free to use it freely, and if you have any questions or suggestions, please contact the author at mastropseudo@gmail.com.

Feel free to explore and adapt the Snake game to suit your needs, whether in a Qt environment or in other platforms and languages!
