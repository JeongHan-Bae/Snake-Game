#include "Snaky.h"
#include "mainwindow.h"

#include <QApplication>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <iostream>

#include <iostream>
#include <utility>

QList<std::pair<int, int>> snakeList;

class SnakeGame : public MainWindow {

public:
    SnakeGame(QWidget* parent = nullptr)
        : MainWindow(parent), snakeGame(0, 0, BoardSIZE, Snaky::EAST) {

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SnakeGame::update);
        timer->start(PERIODE);

        blockSize = FontSIZE;

        direction = Snaky::EAST;

        snakeList.clear();
        // clean the previous list

        initializeGame();
        // Call the initializeGame function to initialise the board
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
        int key = event->key();
        if (event->key() == Qt::Key_Space)
            startGame();
        // restart the game
        else if (key == Qt::Key_Up)
            newDirection = Snaky::NORTH;
        else if (key == Qt::Key_Down)
            newDirection = Snaky::SOUTH;
        else if (key == Qt::Key_Left)
            newDirection = Snaky::WEST;
        else if (key == Qt::Key_Right)
            newDirection = Snaky::EAST;
        // Store newDirection but not update Immediately
    }

    void update() {

        if (snakeGame.turn(newDirection))
            direction = newDirection;
        // update the last input direction

        MoveResult result = snakeGame.nextStep();

        // snake move

        if (result == MoveResult::WALL) {
            showGameOverMessage("Hit wall! Game over!");
        } else if (result == MoveResult::SELF) {
            showGameOverMessage("Bit yourself! Game over!");
        } else if (result == MoveResult::WIN) {
            showGameOverMessage("Congratulations! You win!");
        } else if (result == MoveResult::VOID) {
            drawVoid(snakeList.last());
            snakeList.removeLast();
            // remove the previous tail
        } else {
            // apple eaten, get the new pos
            drawApple(snakeGame.getApplePosition());
        }
        if (!snakeList.isEmpty())
            drawBody(snakeList.first());

        snakeList.prepend(snakeGame.getHeadPosition());
        drawHead(snakeList.first());
        // draw the new head
    }

    void resetGame() {
        snakeGame = Snaky(0, 0, BoardSIZE, Snaky::EAST);
        direction = Snaky::EAST;
        newDirection = Snaky::EAST;
        snakeList.clear();
        initializeGame();
    }

    void startGame() {
        resetGame();
        // Start the game timer and set isGameActive to true
        timer->start(PERIODE);

        // Initialize the scene and show the game
        initializeGame();
        snakeList.removeLast();
        show();
    }

private:
    QTimer* timer;
    Snaky snakeGame;
    std::pair<int, int> direction;
    std::pair<int, int> newDirection = Snaky::EAST;
    int blockSize;

    void initializeGame() {
        initializeTable(); // Call the initializeTable function from MainWindow
        drawApple(snakeGame.getApplePosition());
        snakeList.prepend(snakeGame.getHeadPosition());
        drawHead(snakeList.first());
    }

    void drawHead(std::pair<int, int> headPos) {
        // Set text and color for the head (yellow)
        QString headtext;
        if (direction == Snaky::EAST)
            headtext = " :<";
        else if (direction == Snaky::WEST)
            headtext = ">: ";
        else if (direction == Snaky::NORTH)
            headtext = " .v.";
        else
            headtext = "'^'";

        ChangeColor(headPos.first, headPos.second, Qt::yellow, headtext);
    }

    void drawBody(std::pair<int, int> bodyPos) {
        ChangeColor(bodyPos.first, bodyPos.second, Qt::green, "");
    }

    void drawApple(std::pair<int, int> applPos) {
        ChangeColor(applPos.first, applPos.second, Qt::red, "");
    }

    void drawVoid(std::pair<int, int> voidPos) {
        ChangeColor(voidPos.first, voidPos.second, Qt::black, "");
    }

    void showGameOverMessage(const QString& message) {
        timer->stop();
        QMessageBox gameOverMessageBox;
        gameOverMessageBox.setText(message + "\nPress Space to restart...");
        gameOverMessageBox.setWindowTitle(message == "Congratulations! You win!"
                                              ? "Congratulations"
                                              : "Game Over");
        gameOverMessageBox.setStandardButtons(QMessageBox::Ok);
        gameOverMessageBox.exec();
    }
};

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    SnakeGame game;
    game.show();
    return a.exec();
}
