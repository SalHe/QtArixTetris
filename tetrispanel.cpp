#include <QPaintEvent>
#include <QPainter>
#include "tetrispanel.h"



TetrisPanel::TetrisPanel(QWidget *parent) : QWidget(parent)
{
}

TetrisPanel::~TetrisPanel()
{
}

void TetrisPanel::init(int c, int r)
{
    if(inited)return;

    inited = true;

    row = r;
    column = c;

    QSize size = this->size();
    cellWidth = size.width() / c;
    cellHeight = size.height() / r;

    cells.resize(r);
    for (int y=0;y<r ; y++ ) {
        cells[y].resize(c);
    }

    resize(cellWidth * column + 1, cellHeight * row + 1);
}

void TetrisPanel::paintEvent(QPaintEvent *event)
{
    if(!inited){
        QWidget::paintEvent(event);
        return;
    }
    QPainter * painter = new QPainter(this);

    drawCells(painter);
    drawGridLines(painter);

    delete painter;
}

TetrisCell *TetrisPanel::getCell(int x, int y)
{
    if(x>=0 && y>=0 && x<column && y<row)
        return &cells[y][x];
    return nullptr;
}

void TetrisPanel::setCellColor(int x, int y, QColor color, bool update)
{
    cells[y][x].setColor(color);
    if(update) this->update();
}

int TetrisPanel::cellRows()
{
    return row;
}

int TetrisPanel::cellColumns()
{
    return column;
}

void TetrisPanel::drawCells(QPainter *painter)
{
    for (int y=0; y<cells.size() ; y++) {
        auto cellsRow = cells[y];
        for (int x=0; x<cellsRow.size() ; x++) {
            if(cellsRow[x].exist()){
                painter->fillRect(x*cellWidth, y*cellHeight, cellWidth, cellHeight, *cellsRow[x].color());
            }
        }
    }
}

void TetrisPanel::drawGridLines(QPainter *painter)
{
    painter->setPen(QColor("red"));
    for (int y=0 ; y<=row ; y++) {
        painter->drawLine(0, y*cellHeight, size().width(), y*cellHeight);
    }

    for (int x=0; x<=column; x++) {
        painter->drawLine(x*cellWidth, 0, x*cellWidth, size().height());
    }
}

