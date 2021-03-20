#include "tetriscontroller.h"

TetrisController::TetrisController(int ox, int oy, TetrisPanel *parent) : QObject(parent)
{

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
    refreshBlockInPanel(blockPosition);
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

                if(blockPosition.x() + x>=0 && blockPosition.y() + y>= 0){
                    cell = panel()->getCell(blockPosition.x() + x, blockPosition.y() + y);
                    cell->setExist(false);
                }
            }

        }
    }
}

void TetrisController::resetBlockPosition()
{
    blockPosition = originPosition;
    refreshBlockInPanel(blockPosition);
}

void TetrisController::refreshBlockInPanel(QPoint newPostion)
{
    emptyBlockInPanel();
    blockPosition = newPostion;
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
