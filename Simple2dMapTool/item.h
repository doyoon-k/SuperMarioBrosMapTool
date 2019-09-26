#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include<QGraphicsObject>

class Item:public QGraphicsObject
{
public:
    Item();
    Item(const QString& type,const QPixmap& img, QGraphicsItem* parent = nullptr);
    Item(const Item& other);
    Item& operator=(const Item& other);
private:
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr)override;
    QRectF boundingRect()const override;
    QString ItemType = "";
    QPixmap image;
};

#endif // ITEM_H
