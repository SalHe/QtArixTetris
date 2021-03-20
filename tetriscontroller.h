#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include "tetrispanel.h"

#include <QObject>


class TetrisController : public QObject
{
    Q_OBJECT

    QVector<QVector<TetrisCell>> cellsGroup;
    QPoint groupLT;

public:
    explicit TetrisController(TetrisPanel *parent = nullptr);

    inline TetrisPanel * panel(){
        return qobject_cast<TetrisPanel *>(parent());
    }



signals:

};

#endif // TETRISCONTROLLER_H
