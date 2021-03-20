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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void generateRandomCells();
};
#endif // MAINWINDOW_H
