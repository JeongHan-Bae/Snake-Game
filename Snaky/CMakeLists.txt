cmake_minimum_required(VERSION 3.24)
project(Snaky)

# Add your source files
set(SOURCE_FILES SnakyImpl.cpp Snaky.h)

# Create a dynamic library from the source files
add_library(Snaky SHARED ${SOURCE_FILES})

set(DLL_DIR ${CMAKE_SOURCE_DIR}/lib)

set(DLL_FILES libSnaky.dll)

set(DEST_DIR ${CMAKE_BINARY_DIR})

foreach (DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET Snaky POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL_DIR}/${DLL_FILE}"
            "${DEST_DIR}")
endforeach ()
