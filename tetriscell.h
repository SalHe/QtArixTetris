#ifndef TETRISCELL_H
#define TETRISCELL_H

#include <QObject>
#include <QColor>

class TetrisCell
{

    QColor m_color;
    bool   m_exist = false;

    bool   m_isFree = false;
    QPoint m_position;

public:
    TetrisCell();
    explicit TetrisCell(QColor color);

    QColor * color();
    void setColor(QColor color);

    bool exist();
    void setExist(bool exist);

    bool freeCell();
    void setFreeCell(bool free);

    QPoint position();
    void setPosition(int x, int y);

};

#endif // TETRISCELL_H
