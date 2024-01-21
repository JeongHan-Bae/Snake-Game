#pragma once

#include <string>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <utility>

enum MoveResult {
    WALL,
    APPLE,
    SELF,
    VOID,
    WIN
};

const std::pair<int, int> EAST = std::make_pair(1, 0);
const std::pair<int, int> WEST = std::make_pair(-1, 0);
const std::pair<int, int> NORTH = std::make_pair(0, 1);
const std::pair<int, int> SOUTH = std::make_pair(0, -1);

class SnakyImpl {
public:
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 ^ h2;
        }
    };
private:

    struct RapidSet {
        const int size;
        std::pair<int, int>* container;
        int back;
        std::unordered_map<std::pair<int, int>, int, PairHash> searchMap;

        explicit RapidSet(int newSize);

        ~RapidSet();

        bool add(const std::pair<int, int>& element);

        bool replace(const std::pair<int, int>& toRemove, const std::pair<int, int>& toAdd);

        bool empty() const;

        std::pair<int, int> random_pop();
    };

    struct SnakeNode {
        std::pair<int, int> pos;
        SnakeNode* next;

        explicit SnakeNode(const std::pair<int, int>& position);

        ~SnakeNode() = default;
    };

    struct Snake {
        int length;
        std::unordered_set<std::pair<int, int>, PairHash> posSet;
        SnakeNode* head;
        SnakeNode* tail;

        explicit Snake(const std::pair<int, int>& initialPosition);

        ~Snake();

        std::pair<int, int> head_pos() const;

        std::pair<int, int> tail_pos() const;

        bool contains(const std::pair<int, int>& position) const;

        void grow(const std::pair<int, int>& new_pos);

        void crawl(const std::pair<int, int>& new_pos);
    };

    const int size;
    Snake snake;
    RapidSet board;
    std::pair<int, int> apple;
    std::pair<int, int> direction;

    MoveResult tryNext(const std::pair<int, int>& nextPos);

public:
    SnakyImpl(int initialX, int initialY, int size, const std::pair<int, int>& initialDirection);

    bool turn(const std::pair<int, int>& newDirection);

    MoveResult nextStep();

    std::pair<int, int> getApplePosition() const;

    std::pair<int, int> getHeadPosition() const;

    void getSnakePositions(int*& positionsArray, int& arrayLength) const;

    ~SnakyImpl();
};
