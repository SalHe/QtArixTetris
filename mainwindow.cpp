#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tetrisPanel->init(12, 18);

    controller = new TetrisController(4, -1, ui->tetrisPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    pressedKeys[event->key()] = true;
    handleKey();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys[event->key()] = false;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == blockDownTimer){
        if(controller->isBlockToBottom()){
            controller->placeBlock();

            QRandomGenerator random(QTime::currentTime().msec());
            controller->nextBlock(rand() % 7, QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));
            if(controller->isBlockToBottom()){
                QMessageBox::critical(this, "游戏结束！", "Game Over");
                killTimer(blockDownTimer);
                killTimer(keyPressProcessTimer);
            }
        }else{
            controller->moveBlock(TetrisController::MoveDirection::DOWN);
        }
    }else if(event->timerId() == keyPressProcessTimer){
        handleKey();
    }
}

void MainWindow::handleKey()
{
    if(pressedKeys[Qt::Key_A]){
        controller->moveBlockLeft();
    }else if(pressedKeys[Qt::Key_D]){
        controller->moveBlockRight();
    }else if(pressedKeys[Qt::Key_S]){
        controller->moveBlockDown();
    }else if(pressedKeys[Qt::Key_W]){
        controller->rotate();
    }
}

void MainWindow::generateRandomCells()
{
    QRandomGenerator random(QTime::currentTime().msec());
    // for (int y=0;y < ui->tetrisPanel->cellRows(); y++) {
    //     for (int x=0; x < ui->tetrisPanel->cellColumns(); x++) {
    //         ui->tetrisPanel->getCell(x, y)->setExist(random.generate() % 2);
    //         ui->tetrisPanel->setCellColor(x, y, QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));
    //     }
    // }
    // ui->tetrisPanel->update();

    controller->setBlockColor(QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));
    controller->setCurrentBlock(random.generate() % 7);

}

void MainWindow::startGame()
{
    blockDownTimer = startTimer(1000 / 2);
    keyPressProcessTimer = startTimer(1000/3);
}

