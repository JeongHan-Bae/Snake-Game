# Snaky Library

Snaky is a lightweight C++ library designed to facilitate the implementation of snake games. It provides a straightforward interface for managing the snake's movements and extracting key information about its position. The library is efficient, easy to integrate, and well-suited for both backend logic and frontend development.

## Features

- **Directional Constants:** Snaky offers directional constants (`EAST`, `WEST`, `NORTH`, `SOUTH`) for convenient snake movement.

- **Snake Management:** The `Snaky` class allows simple management of the snake's state, including initial position, size, and direction.

- **Efficient Movement:** Users can easily turn the snake and move it forward using the `turn` and `nextStep` methods, respectively.

- **Position Retrieval:** Retrieve the current positions of the snake's head, apple, and, optionally, the entire snake body.

## Optional Functionality

- **Snake Body Positions Retrieval:** The `getSnakePositions` method allows users to retrieve the positions of the entire snake body. While basic functionalities are O(1), this method is optional for easier frontend development and operates in O(n) time, where n is the length of the snake.

## Build Instructions

To integrate Snaky into your project, you can use CMake. Here's an example CMakeLists.txt file:

```cmake
cmake_minimum_required(VERSION 3.27)
project(SnakyTest)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the Snaky library
set(SNAKY_DIR "Path/In/Your/Directory/Snake-Game/Snaky")
set(SNAKY_LIB_DIR "${SNAKY_DIR}/lib")

add_executable(SnakyTest main.cpp)

# Include the directory containing Snaky.h
target_include_directories(SnakyTest PRIVATE "${SNAKY_DIR}")

# Link against the Snaky library
target_link_libraries(SnakyTest PRIVATE "${SNAKY_LIB_DIR}/libSnaky.dll")

# Set the working directory for the Test executable
set_target_properties(SnakyTest PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/SnakyTest")

# Copy the DLL file from Snaky to SnakyTest during build
add_custom_command(TARGET SnakyTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SNAKY_LIB_DIR}/libSnaky.dll"
        "$<TARGET_FILE_DIR:SnakyTest>"
        COMMENT "Copying libSnaky.dll to SnakyTest output directory"
)
```

Ensure to replace `"Path/In/Your/Directory/Snake-Game/Snaky"` with the actual path to the Snaky library on your system.

For a ready-to-use Snake game implementation in Qt, refer to [JeongHan-Bae's SnakeGame repository](https://github.com/JeongHan-Bae/Snake-Game/tree/main/SnakeGame/SnakeGame).