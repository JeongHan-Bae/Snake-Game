# Snake-Game QVersion 1.1.0 (QMake-Snake-Game Branch)

Snake-Game QVersion 1.1.0 is a variant of the Snake-Game Version 1.1.0, incorporating the Qt framework for enhanced visualization through the use of QMake. This branch is dedicated to the development and maintenance of the QMake version of the Snake-Game.

## What's New in QVersion 1.1.0?

### QMake Integration

In this version, the Snake-Game has been adapted to utilize QMake for streamlined building and compilation. The project structure has been modified to include QMake configuration files, allowing for easier project management and compilation across platforms.

### Note on Qt Framework Enhancement

The Qt visualization has been enhanced with the utilization of QMake. The project now includes a QMake-built executable (`SnakeGame_QVersion.exe`) for playing the game. Ensure that the executable is well-connected to all the necessary C++ and Qt DLLs. You can either place it in a folder with all the required files or add the paths to the system.

## Usage

1. **Clone the Repository:**
   Clone the repository to your local machine:

   ```bash
   git clone https://github.com/your-username/your-repo.git
   ```

2. **Switch to the QMake-Snake-Game Branch:**
   Change into the repository directory and switch to the QMake-Snake-Game branch:

   ```bash
   cd your-repo
   git checkout QMake-Snake-Game
   ```

3. **Build and Run the QMake Version:**
   Navigate to the Qt source folder containing all the source files. Build and run the QMake application using the provided `main` function in `SnakeGame_QVersion/main.cpp`:

   ```bash
   cd SnakeGame_QVersion
   qmake
   make
   ./SnakeGame_QVersion
   ```

4. **Play the Game:**
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
```

Make sure to replace `your-username` and `your-repo` with your GitHub username and repository name. Additionally, adjust the paths and commands based on your actual project structure and file locations.