#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), labelFont("Segoe UI", 20) {
    ui->setupUi(this);

    QIcon appIcon(":Snaky.ico");
    setWindowIcon(appIcon);

    // Initialize the 2D array of frames
    for (int i = 0; i < BoardSIZE; ++i) {
        for (int j = 0; j < BoardSIZE; ++j) {
            frames[j][i] =
                findChild<QFrame*>(QString("frame%1%2").arg(i).arg(j));
        }
    }
}

MainWindow::~MainWindow() { delete ui; }
// update by color and text
void MainWindow::ChangeColor(int i, int j, QColor color, const QString& text) {
    if (i >= 0 && i < BoardSIZE && j >= 0 && j < BoardSIZE) {
        frames[i][j]->setStyleSheet(
            QString("background-color: %1").arg(color.name()));
        // If you have QLabel in the frame, set its text
        QLabel* label = frames[i][j]->findChild<QLabel*>(
            "label" + QString::number(j) + QString::number(i));
        if (label) {
            label->setText(text);
            label->setFont(labelFont);
        }
    }
}

// Initial function to set "void" to all frames
void MainWindow::initializeTable() {
    for (int i = 0; i < BoardSIZE; ++i) {
        for (int j = 0; j < BoardSIZE; ++j) {
            ChangeColor(i, j, Qt::black, "");
        }
    }
}
