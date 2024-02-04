# Snake-Game QVersion 1.1.0 (QMake-Snake-Game Branch)

Snake-Game QVersion 1.1.0 is a variant of the Snake-Game Version 1.1.0, incorporating the Qt framework for enhanced visualization through the use of QMake. This branch is dedicated to the development and maintenance of the QMake version of the Snake-Game.

## What's New in QVersion 1.1.0?

### QMake Integration

In this version, the Snake-Game has been adapted to utilize QMake for streamlined building and compilation. The project structure has been modified to include QMake configuration files, allowing for easier project management and compilation across platforms.

### Note on Qt Framework Enhancement

The Qt visualization has been enhanced with the utilization of QMake. The project now includes a QMake-built executable (`QSnakeGame.exe`) for playing the game.

Ensure that the executable is well-connected to all the necessary C++ and Qt DLLs. You can either place it in a folder with all the required files or add the paths to the system.

## Usage

### Downloading the Release (QV1.1.0)

We offer a release (`qv1.1.0`) for easy access. Users can download the source files for this branch without the need for cloning. The release includes all necessary files to build the project with Qt or to launch the pre-built executable (`QSnakeGame.exe`).

### Play the Game

Enjoy playing Snake-Game QVersion 1.1.0!

## Cross-Platform Compatibility

**Note:** The QMake-Snake-Game version, unlike the original Snake-Game, does not provide cross-platform compatibility by including the Snaky library DLLs within the program. The built executable (`SnakeGame_QVersion.exe`) is configured to work with the specific dependencies bundled with the application.

For cross-platform compatibility and integration into non-Qt implementations or other languages like C#, it is recommended to refer to the original Snake-Game version, which includes the dynamic library (`libSnaky.dll`) for flexible incorporation of the core game logic into various environments.

<div align="center">
  <img src="https://github.com/JeongHan-Bae/Snake-Game/blob/main/SnakeGame/SnakeGame/Snaky.png" alt="Snaky">
</div>

## License

Snake-Game QVersion 1.1.0 is distributed under the [MIT License](LICENSE). Feel free to use it, and for any questions or suggestions, please contact the author at mastropseudo@gmail.com.

Explore and adapt the Snake game to suit your needs, whether in a Qt environment or in other platforms and languages!
