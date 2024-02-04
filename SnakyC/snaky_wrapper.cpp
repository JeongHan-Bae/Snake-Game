// snaky_wrapper.cpp
#include "snaky_wrapper.h"
#include "Snaky.h"

extern "C" {

SnakyHandle Snaky_create(int initialX, int initialY, int size, int initialDirectionX, int initialDirectionY) {
    return reinterpret_cast<SnakyHandle>(new Snaky(initialX, initialY, size, std::make_pair(initialDirectionX, initialDirectionY)));
}

void Snaky_destroy(SnakyHandle handle) {
    delete reinterpret_cast<Snaky*>(handle);
}

int Snaky_turn(SnakyHandle handle, int newDirectionX, int newDirectionY) {
    return reinterpret_cast<Snaky*>(handle)->turn(std::make_pair(newDirectionX, newDirectionY)) ? 1 : 0;
}

int Snaky_nextStep(SnakyHandle handle) {
    return static_cast<int>(reinterpret_cast<Snaky*>(handle)->nextStep());
}

void Snaky_getApplePosition(SnakyHandle handle, int* x, int* y) {
    auto position = reinterpret_cast<Snaky*>(handle)->getApplePosition();
    *x = position.first;
    *y = position.second;
}

void Snaky_getHeadPosition(SnakyHandle handle, int* x, int* y) {
    auto position = reinterpret_cast<Snaky*>(handle)->getHeadPosition();
    *x = position.first;
    *y = position.second;
}

void Snaky_getSnakePositions(SnakyHandle handle, int** positionsArray, int* arrayLength) {
    int* tmpPositionsArray;
    reinterpret_cast<SnakyImpl*>(handle)->getSnakePositions(tmpPositionsArray, *arrayLength);
    *positionsArray = tmpPositionsArray;
}

}
