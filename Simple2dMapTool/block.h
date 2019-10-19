#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QGraphicsObject>

class Block:public QGraphicsObject
{
public:

    Block(const QString& type,const QPixmap& img,QGraphicsItem* parent = nullptr);
    Block(const Block& other);
    Block& operator= (const Block& other);
    Block()
        :image(QPixmap(":/Img/Img/BrickBlock.png"))
    {}
    void setbIsContainingItem(bool val);
    void setItemType(const QString& itemType);
    QString getItemType()const;
    QString getBlockType()const;
    QPixmap getImage()const;
    bool isContainingItem()const;
private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;
    QRectF boundingRect()const override;

    bool bIsContainingItem = false;
    QString ItemType = "";
    QString BlockType = "";


    QPixmap image;
};

#endif // BLOCK_H
