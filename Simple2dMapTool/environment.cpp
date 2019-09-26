#include "environment.h"
#include <QPainter>

Environment::Environment()
{

}

Environment::Environment(const QString &type, const QPixmap &img, QGraphicsItem *parent)
    :EnvironmentType(type),
     image(img)

{

}

Environment::Environment(const Environment &other)
    :EnvironmentType(other.EnvironmentType),
      image(other.image)
{

}

Environment &Environment::operator=(const Environment &other)
{
    EnvironmentType = other.EnvironmentType;
    image = other.image;

    return *this;
}


void Environment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);
   painter->drawPixmap(QPoint(0,0),image);
}

QRectF Environment::boundingRect() const
{
    QRectF rect(0,0,image.width(),image.height());
    return rect;
}
