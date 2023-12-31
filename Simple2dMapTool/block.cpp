#include "block.h"
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include "mapscreen.h"
#include "mainwindow.h"


Block::Block(const QString& type,const QPixmap& img,QGraphicsItem* parent)
    :QGraphicsObject(parent),
      bIsContainingItem(false),
      BlockType(type),
      image(img)
{
   setAcceptedMouseButtons(Qt::LeftButton);
}

Block::Block(const Block &other)
    :bIsContainingItem(other.bIsContainingItem),
      ItemType(other.ItemType),
      BlockType(other.BlockType),
      image(other.image)
{
}

Block &Block::operator=(const Block &other)
{
    ItemType = other.ItemType;
    BlockType = other.BlockType;
    image = other.image;
    bIsContainingItem = other.bIsContainingItem;
    return *this;
}

void Block::setbIsContainingItem(bool val)
{
    bIsContainingItem = val;
}

void Block::setItemType(const QString &itemType)
{
    ItemType = itemType;
}

QString Block::getItemType() const
{
    return ItemType;
}

QString Block::getBlockType() const
{
    return BlockType;
}

QPixmap Block::getImage() const
{
    return image;
}

bool Block::isContainingItem() const
{
   return bIsContainingItem;
}

QRectF Block::boundingRect() const
{
//    return QGraphicsObject::boundingRect();
    QRectF rect(0,0,image.width(),image.height());
    return rect;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(QPoint(0,0),image);
}

void Block::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
//    qDebug()<<"!!!!";
//    qreal blockLength = MainWindow::one_block_length*MapScreen::getAccumulatedScale();
//    QPointF mousePos = event->pos();

//    qreal mousePosX = mousePos.x();
//    qreal mousePosY = mousePos.y();

//    int itemPosX = (int)mousePosX/blockLength;
//    int itemPosY = (int)mousePosY/blockLength;

    //    this->setPosition(QPointF(itemPosX*blockLength,itemPosY*blockLength));
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   QGraphicsObject::mousePressEvent(event);
   qDebug()<<"mouse Clicked";
}

void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   QGraphicsObject::mouseReleaseEvent(event);
}
