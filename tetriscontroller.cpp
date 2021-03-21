#include "tetriscontroller.h"

TetrisController::TetrisController(int ox, int oy, TetrisPanel *parent) : QObject(parent)
{

    blockColor = QColor::fromRgb(255,0,0);

    originPosition.setX(ox);
    originPosition.setY(oy);
    blockPosition = originPosition;


    Block * group;


    // □□
    // □□
    int item1[4][4]=
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    // □
    // □
    // □□
    int item2[4][4]=
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    //  □
    //  □
    // □□
    int item3[4][4]=
    {
        {0,0,1,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    // □
    // □□
    //  □
    int item4[4][4]=
    {
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };
    //  □
    // □□
    // □
    int item5[4][4]=
    {
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {0,0,0,0}
    };
    //  □
    // □□□
    int item6[4][4]=
    {
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,1},
        {0,0,0,0}
    };
    // □□□□
    int item7[4][4]=
    {
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
    };

    group = new Block();
    group->setCellsInfo(item1);
    blockTemplates.append(group);

    group = new Block();
    group->setCellsInfo(item2);
    blockTemplates.append(group);

    group = new Block();
    group->setCellsInfo(item3);
    blockTemplates.append(group);

    group = new Block();
    group->setCellsInfo(item4);
    blockTemplates.append(group);

    group = new Block();
    group->setCellsInfo(item5);
    blockTemplates.append(group);

    group = new Block();
    group->setCellsInfo(item6);
    blockTemplates.append(group);

    group = new Block();
    group->setCellsInfo(item7);
    blockTemplates.append(group);

}

void TetrisController::setCurrentBlock(int id)
{
    emptyBlockInPanel();
    blockTemplates[id]->copyTo(currentBlock);
    //    refreshBlockInPanel(blockPosition);
    showBlockInPanel();
}

void TetrisController::nextBlock(int id, QColor color)
{
    blockTemplates[id]->copyTo(currentBlock);
    blockColor = color;
    blockPosition = originPosition;
    showBlockInPanel();
}

void TetrisController::setBlockPosition(QPoint position)
{
    refreshBlockInPanel(position);
}

void TetrisController::setBlockPosition(int x, int y)
{
    setBlockPosition(QPoint(x,y));
}

void TetrisController::setBlockColor(QColor color)
{
    blockColor = color;
    refreshBlockInPanel(blockPosition);
}

void TetrisController::setOriginPosition(int x, int y)
{
    originPosition.setX(x);
    originPosition.setY(y);
    refreshBlockInPanel(blockPosition);
}

void TetrisController::emptyBlockInPanel()
{
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            if(currentBlock[y][x]){
                TetrisCell * cell;
                cell = panel()->getCell(blockPosition.x() + x, blockPosition.y() + y);
                if(cell)
                    cell->setExist(false);
            }
        }
    }
}

void TetrisController::showBlockInPanel()
{
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            if(currentBlock[y][x]){
                TetrisCell * cell;

                if(blockPosition.x() + x>=0 && blockPosition.y() + y >= 0){
                    cell = panel()->getCell(blockPosition.x() + x, blockPosition.y() + y);
                    cell->setColor(blockColor);
                    cell->setExist(true);
                }
            }

        }
    }

    panel()->update();
}

void TetrisController::resetBlockPosition()
{
    refreshBlockInPanel(originPosition);
}

bool TetrisController::isBlockToBottom()
{
    return !canMove(0, 1);
}

void TetrisController::placeBlock()
{
    for(int y=0 ; y<4; y++){
        for(int x=0 ; x<4; x++){
            auto * cell = panel()->getCell(blockPosition.x() + x, blockPosition.y() + y);
            if(cell && currentBlock[y][x]){
                cell->setExist(true);
                cell->setColor(blockColor);
            }
        }
    }
}

#include <QDebug>
int TetrisController::removeFullLine()
{
    int fullLines = 0;
    int y = panel()->cellRows()-1;
    while(y>0){
        int cellCount = 0;
        for(int x=0; x<panel()->cellColumns(); x++){
            if(panel()->getCell(x, y)->exist()){
                cellCount++;
            }
        }

        if(cellCount == panel()->cellColumns()){
            for(int ny = y; ny > 0; ny--){
                for(int x=0; x<panel()->cellColumns(); x++){
                    auto * downCell = panel()->getCell(x, ny);
                    auto * upCell = panel()->getCell(x, ny-1);
                    downCell->setColor(*upCell->color());
                    downCell->setExist(upCell->exist());
                    upCell->setExist(false);
                }
            }
            fullLines++;
            y++;
        }

        panel()->debugOutputCells();
        y--;
    }
    panel()->update();
    return fullLines;
}

bool TetrisController::rotate()
{
    int rotatedBlock[4][4];

    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            rotatedBlock[y][x] = currentBlock[3-x][y];

            if(rotatedBlock[y][x]){
                // 在判断之前本就有自身的方块在目标位置
                // 但是它们不会影响自身的旋转
                if(y>=0 && y < 4 && x>=0 && x <4 && currentBlock[y][x])
                    continue;

                auto * cell = panel()->getCell(blockPosition.x() + x, blockPosition.y() + y);

                if(!cell) return false; // 越界

                if(cell->exist()) return false; // 目的位置有方块存在

            }
        }
    }

    emptyBlockInPanel();
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            currentBlock[y][x] = rotatedBlock[y][x];
        }
    }
    showBlockInPanel();
    return true;
}

void TetrisController::moveBlock(TetrisController::MoveDirection direction)
{
    switch (direction) {
    case UP:
        moveBlockUp();
        break;
    case DOWN:
        moveBlockDown();
        break;
    case LEFT:
        moveBlockLeft();
        break;
    case RIGHT:
        moveBlockRight();
        break;
    }
}

void TetrisController::moveBlockUp()
{
    move(0,-1);
}

void TetrisController::moveBlockDown()
{
    move(0,1);
}

void TetrisController::moveBlockLeft()
{
    move(-1,0);
}

void TetrisController::moveBlockRight()
{
    move(1,0);
}

void TetrisController::move(int dx, int dy)
{
    if(canMove(dx,dy)){
        setBlockPosition(blockPosition.x()+dx, blockPosition.y() + dy);
    }
}

#include <QDebug>

bool TetrisController::canMove(int dx, int dy)
{
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            if(currentBlock[y][x]){
                // 在判断之前本就有自身的方块在目标位置
                // 但是它们不会影响自身的移动
                if(y+dy>=0 && y+dy < 4 && x+dx>=0 && x+dx <4 && currentBlock[y+dy][x+dx])
                    continue;

                auto * cell = panel()->getCell(blockPosition.x() + x + dx, blockPosition.y() + y+ dy);

                if(!cell) return false; // 越界

                if(cell->exist()) return false; // 目的位置有方块存在

            }
        }
    }
    return true;
}

void TetrisController::refreshBlockInPanel()
{
    emptyBlockInPanel();
    showBlockInPanel();
}

void TetrisController::refreshBlockInPanel(QPoint newPostion)
{
    emptyBlockInPanel();
    blockPosition = newPostion;
    showBlockInPanel();
}
