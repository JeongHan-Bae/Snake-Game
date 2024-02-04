// snaky_wrapper.h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Define a handle type for Snaky
typedef void* SnakyHandle;

// Function prototypes for the wrapper functions
SnakyHandle Snaky_create(int initialX, int initialY, int size, int initialDirectionX, int initialDirectionY);
void Snaky_destroy(SnakyHandle handle);
int Snaky_turn(SnakyHandle handle, int newDirectionX, int newDirectionY);
int Snaky_nextStep(SnakyHandle handle);
void Snaky_getApplePosition(SnakyHandle handle, int* x, int* y);
void Snaky_getHeadPosition(SnakyHandle handle, int* x, int* y);
void Snaky_getSnakePositions(SnakyHandle handle, int** positionsArray, int* arrayLength);

#ifdef __cplusplus
}
#endif
