#include "item.h"
#include <QPainter>

Item::Item()
{

}

Item::Item(const QString &type, const QPixmap &img, QGraphicsItem *parent)
    :QGraphicsObject (parent),
      ItemType(type),
      image(img)
{

}

Item::Item(const Item &other)
    :ItemType(other.ItemType),
      image(other.image)
{

}

void Item::setPosition(const QPointF &point)
{
    QGraphicsObject::setPos(point);
}

void Item::setScale(qreal scale)
{
    QGraphicsObject::setScale(scale);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(QPoint(0,0),image);
}

QRectF Item::boundingRect() const
{
    return QRectF(-image.width()/2,-image.height()/2,image.width(),image.height());
}
