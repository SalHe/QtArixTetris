#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tetriscontroller.h"

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TetrisController * controller;

    int blockDownTimer;
    int keyPressProcessTimer;

    QMap<int, bool> pressedKeys;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    void handleKey();


private slots:
    void generateRandomCells();
    void startGame();
    void emptyCells();
};
#endif // MAINWINDOW_H
