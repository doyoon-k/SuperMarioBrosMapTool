#include "character.h"
#include <QPainter>

Character::Character()
{

}

Character::Character(const QString &type, const QPixmap &img, QGraphicsItem *parent)
    :CharacterType(type),
      image(img)
{
}

Character::Character(const Character &other)
    :CharacterType(other.CharacterType),
      image(other.image)
{

}

Character &Character::operator=(const Character &other)
{
    CharacterType = other.CharacterType;
    image = other.image;
    return *this;
}

QString Character::getCharacterType() const
{
    return CharacterType;
}

QPixmap Character::getImage() const
{
    return image;
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(QPoint(0,0),image);
}

QRectF Character::boundingRect() const
{
    QRectF rect(0,0,image.width(),image.height());
    return rect;
}
