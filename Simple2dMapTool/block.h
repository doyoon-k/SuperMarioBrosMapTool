#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QGraphicsObject>

class Block:QGraphicsObject
{
public:
    explicit Block(QGraphicsItem* parent,QString type);
private:
    bool bIsContainingItem = false;
    QString BlockType;
};

#endif // BLOCK_H
