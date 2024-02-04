#pragma once

#include "SnakyImpl.h"

class Snaky {
public:
    constexpr static const std::pair<int, int> EAST= {1, 0};
    constexpr static const std::pair<int, int> WEST = {-1, 0};
    constexpr static const std::pair<int, int> NORTH = {0, -1};
    constexpr static const std::pair<int, int> SOUTH = {0, 1};

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

    Snaky& operator=(const Snaky& other) = default;

    ~Snaky() = default;
};
