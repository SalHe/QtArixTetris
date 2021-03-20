#ifndef TETRISPANEL_H
#define TETRISPANEL_H

#include <QWidget>
#include <QtCore/QVector>
#include "tetriscell.h"

class TetrisPanel : public QWidget
{
    Q_OBJECT

    bool inited = false;
    int row, column;
    int cellWidth, cellHeight;

    QVector<QVector<TetrisCell>> cells;


public:
    explicit TetrisPanel(QWidget *parent = nullptr);
    ~TetrisPanel();

    void init(int c, int r);
    void paintEvent(QPaintEvent *event) override;

    TetrisCell * getCell(int x, int y);
    void setCellColor(int x, int y, QColor color, bool update = false);
    int cellRows();
    int cellColumns();

signals:


private:
    void drawCells(QPainter * painter);
    void drawGridLines(QPainter * painter);

};

#endif // TETRISPANEL_H
