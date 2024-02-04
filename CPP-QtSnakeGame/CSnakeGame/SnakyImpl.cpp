#include "SnakyImpl.h"
#include <stdexcept>

SnakyImpl::RapidSet::RapidSet(const int newSize) : size(newSize), back(-1) {
    container = new std::pair<int, int>[size * size];
}

SnakyImpl::RapidSet& SnakyImpl::RapidSet::operator=(const RapidSet& other) {
    if (this != &other) {
        // Check if sizes match
        if (size != other.size) {
            // Handle the mismatch, e.g., throw an exception or log an error
            throw std::invalid_argument("RapidSet sizes do not match.");
        }

        // Copy basic types
        back = other.back;

        // Deallocate existing container and create a new one
        delete[] container;
        container = new std::pair<int, int>[size * size];

        // Copy elements and searchMap
        std::copy(other.container, other.container + size * size, container);
        searchMap = other.searchMap;
    }
    return *this;
}

SnakyImpl::RapidSet::~RapidSet() {
    delete[] container;
    searchMap.clear();
}

bool SnakyImpl::RapidSet::add(const std::pair<int, int>& element) {
    auto search = searchMap.find(element);
    if (search != searchMap.end()) {
        return false;
    } else {
        searchMap[element] = ++back;
        container[back] = element;
        return true;
    }
}

bool SnakyImpl::RapidSet::replace(const std::pair<int, int>& toRemove,
                                  const std::pair<int, int>& toAdd) {
    auto removeSearch = searchMap.find(toRemove);
    auto addSearch = searchMap.find(toAdd);
    if (removeSearch == searchMap.end() || addSearch != searchMap.end()) {
        return false;
    }
    int removePos = removeSearch->second;
    container[removePos] = toAdd;
    searchMap[toAdd] = removePos;
    searchMap.erase(toRemove);
    return true;
}

bool SnakyImpl::RapidSet::empty() const { return back == -1; }

std::pair<int, int> SnakyImpl::RapidSet::random_pop() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, back);
    int randIndex = dis(gen);
    std::swap(container[randIndex], container[back]);
    std::pair<int, int> result = container[back];
    searchMap[container[randIndex]] = randIndex;
    searchMap.erase(result);
    --back;
    return result;
}

SnakyImpl::SnakeNode::SnakeNode(const std::pair<int, int>& position)
        : pos(position), next(nullptr) {}

SnakyImpl::Snake::Snake(const std::pair<int, int>& initialPosition)
        : length(1), head(new SnakeNode(initialPosition)), tail(head) {
    posSet.emplace(initialPosition);
}

SnakyImpl::Snake& SnakyImpl::Snake::operator=(const Snake& other) {
    if (this != &other) {
        // Perform deep copy of members
        length = other.length;

        // Clear current posSet
        posSet.clear();

        // Copy each element from other.posSet to this->posSet
        for (const auto& position : other.posSet) {
            posSet.emplace(position);
        }

        // Deep copy SnakeNodes in reverse order (from tail to head)
        SnakeNode* current = other.tail;
        SnakeNode* thisCurrent;

        // Clear existing linked list
        while (tail != nullptr) {
            thisCurrent = tail;
            tail = tail->next;
            delete thisCurrent;
        }

        // Copy elements from other linked list
        tail = new SnakeNode(current->pos);
        current = current->next;
        thisCurrent = tail;
        while (current != nullptr) {
            auto* newNode = new SnakeNode(current->pos);
            thisCurrent->next = newNode; // Update next pointer
            thisCurrent = thisCurrent->next;
            current = current->next;
        }

        head = thisCurrent; // Update head
    }
    return *this;
}

SnakyImpl::Snake::~Snake() {
    SnakeNode* current = head;
    while (current != nullptr) {
        SnakeNode* next = current->next;
        delete current;
        current = next;
    }
    posSet.clear();
}

std::pair<int, int> SnakyImpl::Snake::head_pos() const { return head->pos; }

std::pair<int, int> SnakyImpl::Snake::tail_pos() const { return tail->pos; }

bool SnakyImpl::Snake::contains(const std::pair<int, int>& position) const {
    return posSet.find(position) != posSet.end();
}

void SnakyImpl::Snake::grow(const std::pair<int, int>& new_pos) {
    auto* newNode = new SnakeNode(new_pos);
    head->next = newNode;
    head = newNode;
    length += 1;
    posSet.emplace(new_pos);
}

void SnakyImpl::Snake::crawl(const std::pair<int, int>& new_pos) {
    auto* newNode = new SnakeNode(new_pos);
    head->next = newNode;
    head = newNode;
    posSet.erase(tail->pos);
    posSet.emplace(new_pos);
    SnakeNode* last_tail = tail;
    tail = tail->next;
    delete last_tail;
}

SnakyImpl::SnakyImpl(int initialX, int initialY, int size,
                     const std::pair<int, int>& initialDirection)
        : size(size), snake(std::make_pair(initialX, initialY)), board(size),
          direction(initialDirection) {
    if (initialX < 0 || initialX >= size || initialY < 0 || initialY >= size) {
        throw std::invalid_argument("Invalid initial position for Snaky.");
    }
    if (initialDirection != EAST && initialDirection != WEST &&
        initialDirection != NORTH && initialDirection != SOUTH) {
        throw std::invalid_argument("Invalid initial direction for Snaky.");
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != initialX || j != initialY) {
                board.add(std::make_pair(i, j));
            }
        }
    }
    if (!board.empty()) {
        apple = board.random_pop();
    } else {
        throw std::logic_error("Cannot initialize apple on an empty board.");
    }
}

bool SnakyImpl::turn(const std::pair<int, int>& newDirection) {
    if ((direction == EAST || direction == WEST) &&
        (newDirection == NORTH || newDirection == SOUTH) ||
        (direction == NORTH || direction == SOUTH) &&
        (newDirection == EAST || newDirection == WEST)) {
        direction = newDirection;
        return true;
    }
    return false;
}

MoveResult SnakyImpl::nextStep() {

    std::pair<int, int> nextPos = snake.head_pos();
    nextPos.first += direction.first;
    nextPos.second += direction.second;

    MoveResult result = tryNext(nextPos);

    switch (result) {
        case MoveResult::WALL:
            return MoveResult::WALL;
        case MoveResult::SELF:
            return MoveResult::SELF;
        case MoveResult::APPLE:
            if (board.empty()) {
                return MoveResult::WIN;
            }
            snake.grow(nextPos);
            apple = board.random_pop();
            return MoveResult::APPLE;
        default:
            board.replace(nextPos, snake.tail_pos());
            snake.crawl(nextPos);
            return MoveResult::VOID;
    }
}

std::pair<int, int> SnakyImpl::getApplePosition() const { return apple; }

std::pair<int, int> SnakyImpl::getHeadPosition() const {
    return snake.head_pos();
}

void SnakyImpl::getSnakePositions(int*& positionsArray,
                                  int& arrayLength) const {
    const std::unordered_set<std::pair<int, int>, PairHash>& snakePositions =
            snake.posSet;

    arrayLength = 2 * snake.length;

    // Allocate memory for C# to store the array
    positionsArray = new int[arrayLength];

    // Copy snake positions to the array
    int index = 0;
    for (const auto& position : snakePositions) {
        positionsArray[index++] = position.first;
        positionsArray[index++] = position.second;
    }
}

MoveResult SnakyImpl::tryNext(const std::pair<int, int>& nextPos) {
    if (nextPos.first == -1 || nextPos.first == size || nextPos.second == -1 ||
        nextPos.second == size) {
        return MoveResult::WALL;
    }

    if (nextPos == apple) {
        return MoveResult::APPLE;
    }

    if (snake.contains(nextPos) && nextPos != snake.tail->pos) {
        return MoveResult::SELF;
    }

    return MoveResult::VOID;
}

SnakyImpl& SnakyImpl::operator=(const SnakyImpl& other) {
    if (this != &other) {
        // Check if sizes match
        if (size != other.size) {
            // Handle the mismatch, e.g., throw an exception or log an error
            throw std::invalid_argument("RapidSet sizes do not match.");
        }
        // Copy the basic types
        apple = other.apple;
        direction = other.direction;

        // Copy the Snake object
        snake = other.snake;

        // Copy the RapidSet object
        board = other.board;
    }
    return *this;
}

SnakyImpl::~SnakyImpl() = default;
