#include "tetriscell.h"

TetrisCell::TetrisCell() : TetrisCell(QColor::fromRgb(0,0,0))
{

}

TetrisCell::TetrisCell(QColor color) : m_color(color), m_position(0,0)
{

}

QColor *TetrisCell::color()
{
    return &m_color;
}

void TetrisCell::setColor(QColor color)
{
    this->m_color = color;
}

bool TetrisCell::exist()
{
    return m_exist;
}

void TetrisCell::setExist(bool exist)
{
    m_exist = exist;
}
