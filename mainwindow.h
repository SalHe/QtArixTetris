#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tetriscontroller.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TetrisController * controller;

    int blockDownTimer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void timerEvent(QTimerEvent *event) override;


private slots:
    void generateRandomCells();
    void startGame();
};
#endif // MAINWINDOW_H
