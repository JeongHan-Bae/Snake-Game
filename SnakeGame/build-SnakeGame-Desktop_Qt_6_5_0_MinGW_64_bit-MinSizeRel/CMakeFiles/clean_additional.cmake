# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles\\SnakeGame_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SnakeGame_autogen.dir\\ParseCache.txt"
  "SnakeGame_autogen"
  )
endif()
