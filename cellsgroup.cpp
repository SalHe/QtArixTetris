#include "cellsgroup.h"

Block::Block(QObject *parent) : QObject(parent)
{

}

void Block::setCellsInfo(int cellsInfo[4][4])
{
    for(int y=0; y<4; y++)
        for(int x=0; x<4; x++)
            this->cellsInfo[y][x] = cellsInfo[y][x];


}

void Block::copyTo(int block[4][4])
{
    for(int i=0; i<4 ; i++)
        for(int j=0; j<4 ; j++)
            block[i][j] = cellsInfo[i][j];
}
