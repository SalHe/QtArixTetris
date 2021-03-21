#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tetrisPanel->init(12, 18);
    ui->tpNextBlock->init(4, 4);

    controller = new TetrisController(4, -1, ui->tetrisPanel);
    nextBlockController = new TetrisController(0, 0, ui->tpNextBlock);

    QRandomGenerator random(QTime::currentTime().msec());
    nextBlockColor = QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255);
    nextBlock = random.generate() % 7;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setNextBlock(int blockID, QColor color)
{
    controller->nextBlock(nextBlock, nextBlockColor);

    nextBlock = blockID;
    nextBlockColor = color;
    nextBlockController->setCurrentBlock(nextBlock);
    nextBlockController->setBlockColor(nextBlockColor);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
        paused = !paused;
        this->setWindowTitle(tr("俄罗斯方块：") + (paused ? tr("已暂停") : ""));
    }else{
        pressedKeys[event->key()] = true;
        handleKey();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys[event->key()] = false;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == blockDownTimer){
        if(paused) return;
        if(controller->isBlockToBottom()){
            controller->placeBlock();

            int fullLines = controller->removeFullLine();
            addScores(fullLines * fullLines * 10);

            QRandomGenerator random(QTime::currentTime().msec());
            setNextBlock(rand() % 7, QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));
            if(controller->isBlockToBottom()){
                QMessageBox::critical(this, tr("俄罗斯方块"), tr("游戏结束！"));

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
    if(paused) return;
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

void MainWindow::setScores(int score)
{
    this->scores = score;
    ui->labelScore->setText(QString("%1").arg(score));
}

void MainWindow::emptyScores()
{
    setScores(0);
}

void MainWindow::addScores(int ds)
{
    setScores(ds + scores);
}

void MainWindow::generateRandomCells()
{
    QRandomGenerator random(QTime::currentTime().msec());
    for (int y=17 - random.generate()%3;y < ui->tetrisPanel->cellRows(); y++) {
        for (int x=0; x < ui->tetrisPanel->cellColumns(); x++) {
            ui->tetrisPanel->getCell(x, y)->setExist((random.generate() % 2) || y>=16);
            ui->tetrisPanel->setCellColor(x, y, QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));
        }
    }
    // ui->tetrisPanel->update();

    setNextBlock(rand() % 7, QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));

}

void MainWindow::startGame()
{
    blockDownTimer = startTimer(1000 / 2);
    keyPressProcessTimer = startTimer(1000/3);

    emptyScores();
    QRandomGenerator random(QTime::currentTime().msec());
    setNextBlock(random.generate() % 7, QColor::fromRgb(random.generate() % 255, random.generate() % 255, random.generate() % 255));
}

void MainWindow::emptyCells()
{
    for (int y=0;y < ui->tetrisPanel->cellRows(); y++) {
        for (int x=0; x < ui->tetrisPanel->cellColumns(); x++) {
            ui->tetrisPanel->getCell(x, y)->setExist(false);
        }
    }
    ui->tetrisPanel->update();
}

