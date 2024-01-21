cmake_minimum_required(VERSION 3.24)
project(Snaky)

# Add your source files
set(SOURCE_FILES SnakyImpl.cpp
        Snaky.h)

# Create a dynamic library from the source files
add_library(Snaky SHARED ${SOURCE_FILES}
        Snaky.h)
