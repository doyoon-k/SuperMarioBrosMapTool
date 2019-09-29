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
        qDebug()<<block->pos()/accumulatedScale;
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
    for(auto environment : vEnvironments)
    {
        environment->setScale(environment->scale()*newScale);
        qreal x = environment->x();
        qreal y = environment->y();
        environment->setPos(x*newScale,y*newScale);
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
            if(tmpItemName == "Pirhana Plant Pipe")
            {
                addEnvironments("Pirhana Plant Pipe",QPixmap(":/Img/Img/Piranha Plant Pipe.png"));
            }
            else if(tmpItemName == "Pipe Head(Horizontal)")
            {
                addEnvironments("Pipe Head Horizontal",QPixmap(":/Img/Img/Pipe Head Hor.png"));
            }
            else if(tmpItemName == "Pipe Head(Vertical)")
            {
                addEnvironments("Pipe Head Vertical",QPixmap(":/Img/Img/Pipe Head Ver.png"));
            }
            else if(tmpItemName == "Pipe Body(Horizontal)")
            {
                addEnvironments("Pipe Body Horizontal",QPixmap(":/Img/Img/Pipe Body Hor.png"));
            }
            else if(tmpItemName == "Pipe Body(Vertical)")
            {
                addEnvironments("Pipe Body Vertical",QPixmap(":/Img/Img/Pipe Body Ver.png"));
            }
            else if(tmpItemName == "Flag")
            {
                addEnvironments("Flag",QPixmap(":/Img/Img/Flag.png"));
            }
            else if(tmpItemName == "Cloud1")
            {
                addEnvironments("Cloud1",QPixmap(":/Img/Img/Cloud1.png"));
            }
            else if(tmpItemName == "Cloud2")
            {
                addEnvironments("Cloud2",QPixmap(":/Img/Img/Cloud2.png"));
            }
            else if(tmpItemName == "Cloud3")
            {
                addEnvironments("Cloud3",QPixmap(":/Img/Img/Cloud3.png"));
            }
            else if(tmpItemName == "Bush1")
            {
                addEnvironments("Bush1",QPixmap(":/Img/Img/Bush1.png"));
            }
            else if(tmpItemName == "Bush2")
            {
                addEnvironments("Bush2",QPixmap(":/Img/Img/Bush2.png"));
            }
            else if(tmpItemName == "Bush3")
            {
                addEnvironments("Bush3",QPixmap(":/Img/Img/Bush3.png"));
            }
            else if(tmpItemName == "Castle")
            {
                addEnvironments("Castle",QPixmap(":/Img/Img/Castle.png"));
            }
            else if(tmpItemName == "Mountain")
            {
                addEnvironments("Mountain",QPixmap(":/Img/Img/Mountain.png"));
            }
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

void MapScreen::addEnvironments(const QString &name, const QPixmap &image)
{
    for(auto tmpItem : vTmpItems)
    {
        Environment* environment = new Environment(name,image);
        environment->setPos(tmpItem->pos());
        environment->setScale(tmpItem->scale());
        environment->setObjectName(name);
        vEnvironments.push_back(environment);
        p_mapScene->addItem(environment);
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

void MapScreen::writeMapDataToJsonObject(QJsonObject &json)
{
    QJsonArray blocks;
    QJsonArray items;
    QJsonArray characters;
    QJsonArray environments;
    QJsonArray backgrounds;

    for(auto nBlock : vBlocks)
    {
        QJsonObject block;
        QJsonObject position;
        block["blockType"] = nBlock->getBlockType();
        position["x"] = (int)(nBlock->pos().x()/accumulatedScale)+(nBlock->getImage().width()/2);
        position["y"] = (int)(nBlock->pos().y()/accumulatedScale)+(nBlock->getImage().height());
        block["position"] = position;
        block["isContainingItem"] = nBlock->isContainingItem();

        blocks.push_back(block);
    }

    for(auto nItem : vItems)
    {
        QJsonObject item;
        QJsonObject position;
        item["itemType"] = nItem->getItemType();
        position["x"] = (int)(nItem->pos().x()/accumulatedScale)+(nItem->getImage().width()/2);
        position["y"] = (int)(nItem->pos().y()/accumulatedScale)+(nItem->getImage().height());
        item["position"] = position;

        items.push_back(item);
    }

    for(auto nCharacter : vCharacters)
    {
        QJsonObject character;
        QJsonObject position;
        character["characterType"] = nCharacter->getCharacterType();
        position["x"] = (int)(nCharacter->pos().x()/accumulatedScale)+(nCharacter->getImage().width()/2);
        position["y"] = (int)(nCharacter->pos().y()/accumulatedScale)+(nCharacter->getImage().height());
        character["position"] = position;

        characters.push_back(character);
    }

    for(auto nEnvironment : vEnvironments)
    {
        QJsonObject environment;
        QJsonObject position;
        QString name = nEnvironment->getEnvironmentType();
        environment["characterType"] = name;
        position["x"] = (int)(nEnvironment->pos().x()/accumulatedScale)+(nEnvironment->getImage().width()/2);
        position["y"] = (int)(nEnvironment->pos().y()/accumulatedScale)+(nEnvironment->getImage().height());
        environment["position"] = position;
        if(name.contains("Cloud")||name.contains("Bush")||name.contains("Mountain"))
        {
            backgrounds.push_back(environment);
        }
        else
        {
            environments.push_back(environment);
        }
    }

    json["blocks"] = blocks;
    json["items"] = items;
    json["characters"] = characters;
    json["environments"] = environments;
    json["backgrounds"] = backgrounds;
}
