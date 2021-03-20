#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include "cellsgroup.h"
#include "tetrispanel.h"

#include <QObject>


class TetrisController : public QObject
{
    Q_OBJECT

    QVector<Block *> blockTemplates;

    QColor blockColor;

    QPoint blockPosition;

    QPoint originPosition;
    int currentBlock[4][4] = {0};

public:

    enum MoveDirection{
        UP, DOWN, LEFT, RIGHT
    };

    explicit TetrisController(int ox, int oy,TetrisPanel *parent = nullptr);

    inline TetrisPanel * panel(){
        return qobject_cast<TetrisPanel *>(parent());
    }

    void setCurrentBlock(int id);
    void nextBlock(int id, QColor color);
    void setBlockPosition(QPoint position);
    void setBlockPosition(int x, int y);
    void setBlockColor(QColor color);
    void setOriginPosition(int x, int y);
    void resetBlockPosition();
    bool isBlockToBottom();
    void placeBlock();

    void rotate();

    void moveBlock(MoveDirection direction);
    void moveBlockUp();
    void moveBlockDown();
    void moveBlockLeft();
    void moveBlockRight();

private:

    void move(int dx, int dy);
    bool canMove(int dx, int dy);

    void emptyBlockInPanel();
    void showBlockInPanel();
    void refreshBlockInPanel();
    void refreshBlockInPanel(QPoint newPostion);

signals:

};

#endif // TETRISCONTROLLER_H
