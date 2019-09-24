#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include<QGraphicsScene>
#include<QGraphicsItem>
#include "block.h"

class myGraphicsScene:public QGraphicsScene
{
public:
    myGraphicsScene(QObject* parent = nullptr);
    QVector<Block*>& getvBlocks();
    QVector<QGraphicsItem*>& getvTmpItems();
private:
    QVector<Block*> vBlocks;
    QVector<QGraphicsItem*> vTmpItems;
};

#endif // MYGRAPHICSSCENE_H
