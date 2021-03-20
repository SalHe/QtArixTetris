#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

