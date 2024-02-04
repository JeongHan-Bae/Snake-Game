#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QLabel>
#include <QMainWindow>

#define BoardSIZE 6
#define PERIODE 500
const int FontSIZE = 512 / BoardSIZE;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void ChangeColor(int i, int j, QColor color, const QString& text);
    void ChangeColor(int i, int j, const QString& text);
    void initializeTable();

private:
    Ui::MainWindow* ui;

    QFont labelFont;

    // 2D array of frames
    QFrame* frames[BoardSIZE][BoardSIZE];
};

#endif // MAINWINDOW_H
