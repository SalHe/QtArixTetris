#ifndef TETRISCELL_H
#define TETRISCELL_H

#include <QObject>
#include <QColor>
#include <QPoint>

class TetrisCell
{

    QColor m_color;

    /**
     * @brief m_exist 用于指明该对象所在位置是否代表了一个方块。
     */
    bool   m_exist = false;

    /**
     * @brief m_isFree 指明方块是否是非受限制类的方块。
     */
    bool   m_isFree = false;

    /**
     * @brief m_position 指明方块的位置，用于非受限制的方块。
     */
    QPoint m_position;

public:
    TetrisCell();
    explicit TetrisCell(QColor color);

    QColor * color();
    void setColor(QColor color);

    bool exist();
    void setExist(bool exist);

};

#endif // TETRISCELL_H
