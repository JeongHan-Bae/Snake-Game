#pragma once

#include "SnakyImpl.h"

class Snaky {
public:
    static const std::pair<int, int> EAST;
    static const std::pair<int, int> WEST;
    static const std::pair<int, int> NORTH;
    static const std::pair<int, int> SOUTH;

private:
    SnakyImpl impl;

public:
    Snaky(int initialX, int initialY, int size,
          const std::pair<int, int>& initialDirection)
            : impl(initialX, initialY, size, initialDirection) {}

    bool turn(const std::pair<int, int>& newDirection) {
        return impl.turn(newDirection);
    }

    MoveResult nextStep() { return impl.nextStep(); }

    std::pair<int, int> getApplePosition() const {
        return impl.getApplePosition();
    }

    std::pair<int, int> getHeadPosition() const {
        return impl.getHeadPosition();
    }

    void getSnakePositions(int*& positionsArray, int& arrayLength) const {
        // Call an appropriate method in SnakyImpl to get snake positions
        impl.getSnakePositions(positionsArray, arrayLength);
    }

    Snaky& operator=(const Snaky& other) {
        this->impl = other.impl;
        return *this;
    }

    ~Snaky() = default;
};

const std::pair<int, int> Snaky::EAST = {1, 0};
const std::pair<int, int> Snaky::WEST = {-1, 0};
const std::pair<int, int> Snaky::NORTH = {0, -1};
const std::pair<int, int> Snaky::SOUTH = {0, 1};