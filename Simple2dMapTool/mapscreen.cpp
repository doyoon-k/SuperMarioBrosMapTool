#include "mapscreen.h"
#include "mainwindow.h"
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include <QScrollBar>

qreal MapScreen::accumulatedScale = 1.0;

MapScreen::MapScreen(QWidget *parent) :
    QGraphicsView(parent),
    p_bgImgObject(new QImage)
{
    vTmpItems.reserve(100);
}

MapScreen::~MapScreen()
{
}

void MapScreen::wheelEvent(QWheelEvent *event)
{
    if(p_bgImageItem == nullptr)
        return;

    qreal width = p_bgImageItem->boundingRect().width();
    qreal height = p_bgImageItem->boundingRect().height();
    qreal deltaScale = event->delta()/500.0;
    qreal newScale = 1.0+deltaScale;

    p_bgImageItem->setScale(p_bgImageItem->scale()*newScale);
    accumulatedScale = p_bgImageItem->scale();
    qDebug()<<accumulatedScale;

    p_mapScene->setSceneRect(0,0,width*accumulatedScale,height*accumulatedScale);
    for(QGraphicsItem* tmpItem : vTmpItems)
    {
        tmpItem->setScale(tmpItem->scale()*newScale);
        qreal x = tmpItem->x();
        qreal y = tmpItem->y();
        tmpItem->setPos(x*newScale,y*newScale);
//        qDebug()<<item->pos()/accumulatedScale;
    }
    for(auto block : vBlocks)
    {
        block->setScale(block->scale()*newScale);
        qreal x = block->x();
        qreal y = block->y();
        block->setPos(x*newScale,y*newScale);
//        qDebug()<<block->pos()/accumulatedScale;
    }
    for(auto item : vItems)
    {
        item->setScale(item->scale()*newScale);
        qreal x = item->x();
        qreal y = item->y();
        item->setPos(x*newScale,y*newScale);
    }
    for(auto character : vCharacters)
    {
        character->setScale(character->scale()*newScale);
        qreal x = character->x();
        qreal y = character->y();
        character->setPos(x*newScale,y*newScale);
    }
}

void MapScreen::mouseMoveEvent(QMouseEvent *event)
{
    if(vTmpItems.size() == 0)
        return ;

    qreal half_blockLength = MainWindow::half_block_length*accumulatedScale;
    QPoint mousePos = event->pos();

    int mousePosX = mousePos.x();
    int mousePosY = mousePos.y();
    int horizontalScrolledDistance = this->horizontalScrollBar()->value();
    int verticalScrolledDistance = this->verticalScrollBar()->value();
    int itemPosX = (mousePosX+horizontalScrolledDistance)/half_blockLength;
    int itemPosY = (mousePosY+verticalScrolledDistance)/half_blockLength;

//    qDebug()<<mousePos;
//    vTmpItems[0]->setPos(QPointF(itemPosX*blockLength,itemPosY*blockLength));

    QPointF origin = vTmpItems[0]->pos();
    for(auto item : vTmpItems)
    {
        item->setPos(QPointF(itemPosX*half_blockLength,itemPosY*half_blockLength) + (item->pos()-origin));
    }
}

void MapScreen::mousePressEvent(QMouseEvent *event)
{
    if(vTmpItems.size() == 0)
    {
        return;
    }
    if(event->buttons() == Qt::RightButton)
    {
        for(auto item : vTmpItems)
        {
            p_mapScene->removeItem(item);
        }
        vTmpItems.clear();
        tmpItemName = "";
        tmpItempType = -1;
        return ;
    }
    else if(event->buttons() == Qt::LeftButton)
    {
        switch(tmpItempType)
        {
        case block:
            if(tmpItemName == "Ground")
            {
                addBlocks("GroundBlock",QPixmap(":/Img/Img/GroundBlock.png"));
            }
            else if(tmpItemName == "Hidden")
            {
                addBlocks("HiddenBlock",QPixmap(":/Img/Img/HiddenBlock.png"));
            }
            else if(tmpItemName == "Mushroom")
            {
                addBlocks("MushroomBlock",QPixmap(":/Img/Img/Mushroom Block.png"));
            }
            else if(tmpItemName == "Coin")
            {
                addBlocks("CoinBlock",QPixmap(":/Img/Img/Coin Block.png"));
            }
            else if(tmpItemName == "Star")
            {
                addBlocks("StarBlock",QPixmap(":/Img/Img/Star Block.png"));
            }
            else if(tmpItemName == "Questionmark")
            {
                addBlocks("QuestionMarkBlock",QPixmap(":/Img/Img/QuestionBlock.png"));
            }
            else if(tmpItemName == "Brick")
            {
                addBlocks("BrickBlock",QPixmap(":/Img/Img/BrickBlock.png"));
            }
            else if(tmpItemName == "Hard")
            {
                addBlocks("HardBlock",QPixmap(":/Img/Img/HardBlock.png"));
            }
            break;
        case item:
            if(tmpItemName == "Coin")
            {
                addItems("Coin",QPixmap(":/Img/Img/Coin.png"));
            }
            else if(tmpItemName == "Mushroom")
            {
                addItems("Mushroom",QPixmap(":/Img/Img/Mushroom.png"));
            }
            else if(tmpItemName == "1-Up Mushroom")
            {
                addItems("1-Up Mushroom",QPixmap(":/Img/Img/1-Up Mushroom.png"));
            }
            else if(tmpItemName == "Star")
            {
                addItems("Star",QPixmap(":/Img/Img/Star.png"));
            }
            else if(tmpItemName == "Fire Flower")
            {
                addItems("Fire Flower",QPixmap(":/Img/Img/Fireflower.png"));
            }
            break;
        case characters:
            if(tmpItemName == "Mario")
            {
                addCharacters("Mario",QPixmap(":/Img/Img/Mario.png"));
            }
            else if(tmpItemName == "Gumba")
            {
                addCharacters("Gumba",QPixmap(":/Img/Img/Gumba.png"));
            }
            else if(tmpItemName == "Green Koopa Troopa")
            {
                addCharacters("Green Koopa Troopa",QPixmap(":/Img/Img/Green Koopa Troopa.png"));
            }
            else if(tmpItemName == "Red Koopa Troopa")
            {
                addCharacters("Red Koopa Troopa",QPixmap(":/Img/Img/Red Koopa Troopa.png"));
            }
            break;
        case environments:
            break;
        default:
            break;
        }
        vTmpItems.clear();
        tmpItemName = "";
        tmpItempType = -1;
        return ;
    }
}

void MapScreen::addBlocks(const QString &name, const QPixmap &image)
{
    for(auto item : vTmpItems)
    {
        Block* block = new Block(name,image);
        block->setPos(item->pos());
        block->setScale(item->scale());
        block->setObjectName(name);
        if(name == "HiddenBlock")
        {
            block->setbIsContainingItem(true);
            block->setItemType("1-Up Mushroom");
        }
        else if(name == "MushroomBlock")
        {
            block->setbIsContainingItem(true);
            block->setItemType("Mushroom");
        }
        else if(name == "CoinBlock")
        {
            block->setbIsContainingItem(true);
            block->setItemType("Coin");
        }
        else if(name == "StarBlock")
        {
            block->setbIsContainingItem(true);
            block->setItemType("Star");
        }
        vBlocks.push_back(block);
        p_mapScene->addItem(block);
        p_mapScene->removeItem(item);
    }
    vTmpItems.clear();
}

void MapScreen::addItems(const QString &name, const QPixmap &image)
{
    for(auto tmpItem : vTmpItems)
    {
        Item* item = new Item(name,image);
        item->setPos(tmpItem->pos());
        item->setScale(tmpItem->scale());
        item->setObjectName(name);
        vItems.push_back(item);
        p_mapScene->addItem(item);
        p_mapScene->removeItem(tmpItem);
    }
    vTmpItems.clear();
}

void MapScreen::addCharacters(const QString &name, const QPixmap &image)
{
    for(auto tmpItem : vTmpItems)
    {
        Character* character = new Character(name,image);
        character->setPos(tmpItem->pos());
        character->setScale(tmpItem->scale());
        character->setObjectName(name);
        vCharacters.push_back(character);
        p_mapScene->addItem(character);
        p_mapScene->removeItem(tmpItem);
    }
}

void MapScreen::set_p_MapScene(QGraphicsScene *mapScene)
{
    p_mapScene = mapScene;
}

void MapScreen::set_p_mw(void *mw)
{
    p_mw = mw;
}

QVector<QGraphicsItem *> &MapScreen::getvTmpItems()
{
    return vTmpItems;
}

QGraphicsScene*& MapScreen::getMapScene()
{
    return p_mapScene;
}

QGraphicsPixmapItem*& MapScreen::getBackgroundPixmapItem()
{
    return p_bgImageItem;
}

QImage*& MapScreen::getBackgroundImageObject()
{
    return p_bgImgObject;
}

qreal MapScreen::getAccumulatedScale()
{
    return accumulatedScale;
}

void MapScreen::setTmpItemType(int type,const QString& name)
{
    tmpItempType = type;
    tmpItemName = name;
}
