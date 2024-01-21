#include "Snaky.h"
#include <QApplication>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <iostream>

#define BoardSIZE 6
#define PERIODE 512
const int FontSIZE = 500 / BoardSIZE;

class SnakeGame : public QGraphicsView {

public:
    SnakeGame(QWidget* parent = nullptr)
        : QGraphicsView(parent), snakeGame(0, 0, BoardSIZE, Snaky::EAST) {
        scene = new QGraphicsScene(this);
        setScene(scene);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SnakeGame::update);
        timer->start(PERIODE);

        // Initialize block size
        blockSize = FontSIZE;

        direction = Snaky::EAST;

        // Add initial items to the scene based on your SnakeBackend state
        initializeScene();

        setFocusPolicy(Qt::StrongFocus);
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
        // Handle key presses and update SnakeBackend accordingly
        int key = event->key();
        if (event->key() == Qt::Key_Space)
            startGame();
        else if (key == Qt::Key_Up)
            handleInput(Snaky::NORTH);
        else if (key == Qt::Key_Down)
            handleInput(Snaky::SOUTH);
        else if (key == Qt::Key_Left)
            handleInput(Snaky::WEST);
        else if (key == Qt::Key_Right)
            handleInput(Snaky::EAST);
    }

    void update() {
        // Move the snake
        MoveResult result = snakeGame.nextStep();

        // Handle different move results
        if (result == MoveResult::WALL) {
            // Handle hitting the wall
            showGameOverMessage("Hit wall! Game over!");
        } else if (result == MoveResult::SELF) {
            // Handle biting yourself
            showGameOverMessage("Bit yourself! Game over!");
        } else if (result == MoveResult::WIN) {
            // Handle winning the game
            showGameOverMessage("Congratulations! You win!");
        }

        // Redraw the scene based on the updated SnakeBackend state
        drawScene();
    }
    void resetGame() {
        Snaky newGame = Snaky(0, 0, BoardSIZE, Snaky::EAST);
        snakeGame = newGame;
        direction = Snaky::EAST;
        initializeScene();
    }
    void startGame() {
        resetGame();
        // Start the game timer and set isGameActive to true
        timer->start(PERIODE);

        // Initialize the scene and show the game
        initializeScene();
        show();
    }

private:
    QGraphicsScene* scene;
    QTimer* timer;
    Snaky snakeGame;
    std::pair<int, int> direction;
    int blockSize; // Size of each block in pixels

    void initializeScene() { drawScene(); }

    void drawScene() {
        // Clear the scene
        scene->clear();

        // Draw the cells
        for (int i = 0; i < BoardSIZE; ++i) {
            for (int j = 0; j < BoardSIZE; ++j) {
                QGraphicsTextItem* cell = new QGraphicsTextItem();
                cell->setPos(i * blockSize, j * blockSize);
                cell->setFont(QFont("Arial", FontSIZE, QFont::Bold));

                // Retrieve the state of the cell from SnakeBackend and set the
                // text and color accordingly
                if (std::make_pair(i, j) == snakeGame.getHeadPosition()) {
                    // Set text and color for the head (yellow)
                    QString head;
                    if (direction == Snaky::EAST) {
                        head = "> ";
                    } else if (direction == Snaky::WEST) {
                        head = "< ";
                    } else if (direction == Snaky::NORTH) {
                        head = "^ ";
                    } else {
                        head = "v ";
                    }
                    cell->setPlainText(head);
                    cell->setDefaultTextColor(Qt::yellow);
                } else {
                    // Check if the cell is an apple
                    std::pair<int, int> applePosition =
                        snakeGame.getApplePosition();
                    if (std::make_pair(i, j) == applePosition) {
                        // Set text and color for the apple (red)
                        cell->setPlainText("■ ");
                        cell->setDefaultTextColor(Qt::red);
                    } else {
                        // Check if the cell is part of the snake body
                        bool isBodyPart = false;
                        int doubleLength;
                        int* snakePositions;
                        snakeGame.getSnakePositions(snakePositions,
                                                    doubleLength);

                        for (int k = 0; k < doubleLength / 2; ++k) {
                            if (std::make_pair(i, j) ==
                                std::make_pair(snakePositions[2 * k],
                                               snakePositions[2 * k + 1])) {
                                // Set text and color for the body (green)
                                cell->setPlainText("■ ");
                                cell->setDefaultTextColor(Qt::green);
                                isBodyPart = true;
                                break;
                            }
                        }

                        if (!isBodyPart) {
                            // Set text and color for the background (black)
                            cell->setPlainText("■ ");
                            cell->setDefaultTextColor(Qt::black);
                        }
                    }
                }

                // Add the cell to the scene
                scene->addItem(cell);
            }
        }
    }

    void handleInput(const std::pair<int, int>& newDirection) {
        // Update the game state based on user input
        if (snakeGame.turn(newDirection)) {
            // Update direction only if the turn is valid
            direction = newDirection;
        }
        drawScene();
    }

    // Modify the showGameOverMessage function to call restartGame when the
    // space key is pressed
    void showGameOverMessage(const QString& message) {
        // Stop the game timer
        timer->stop();

        // Show a QMessageBox with the game over message
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
