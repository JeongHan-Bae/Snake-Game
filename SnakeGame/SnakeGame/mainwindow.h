#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QLabel>
#include <QMainWindow>

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
    QFrame* frames[6][6];
};

#endif // MAINWINDOW_H
