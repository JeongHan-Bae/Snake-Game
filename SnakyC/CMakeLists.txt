cmake_minimum_required(VERSION 3.10)
project(SnakyWrapperDll)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
        snaky_wrapper.cpp
        snaky_wrapper.h
        Snaky.h
        SnakyImpl.h
        SnakyImpl.cpp
)

# Create the DLL target
add_library(Snaky_wrapper SHARED ${SOURCES})

# Set output directory
set_target_properties(Snaky_wrapper PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Include directories
target_include_directories(Snaky_wrapper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy DLL to target directory
set(DLL_DIR ${CMAKE_SOURCE_DIR}/lib)
set(DLL_FILES libSnaky_wrapper.dll) # Change DLL filename here
set(DEST_DIR ${CMAKE_BINARY_DIR}/bin)

foreach (DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET Snaky_wrapper POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL_DIR}/${DLL_FILE}"
            "${DEST_DIR}")
endforeach ()
