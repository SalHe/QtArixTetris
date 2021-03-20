#ifndef CELLSGROUP_H
#define CELLSGROUP_H

#include "tetriscell.h"

#include <QObject>
#include <QVector>

class Block : public QObject
{
    Q_OBJECT

    int cellsInfo[4][4];
    int cellsRotataion[4][4][4];

public:
    explicit Block(QObject *parent = nullptr);

    void setCellsInfo(int cellsInfo[4][4]);

    void copyTo(int block[4][4]);

signals:

};

#endif // CELLSGROUP_H
