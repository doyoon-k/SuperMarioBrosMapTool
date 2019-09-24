#pragma once
#ifndef MAPSCREEN_H
#define MAPSCREEN_H

#include <QWidget>
#include <QGraphicsView>
#include "block.h"
#include "item.h"
#include "character.h"

using namespace std;

class MapScreen : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapScreen(QWidget *parent = nullptr);
    ~MapScreen();


    void set_p_MapScene(QGraphicsScene* mapScene);
    void set_p_mw(void* mw);
    QVector<QGraphicsItem*>& getvTmpItems();
    QGraphicsScene*& getMapScene();
    QGraphicsPixmapItem*& getBackgroundPixmapItem();
    QImage*& getBackgroundImageObject();
    static qreal getAccumulatedScale();
    void setTmpItemType(int type,const QString& name);
private:
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void addBlocks(const QString& name,const QPixmap& image);
    void addItems(const QString& name,const QPixmap& image);
    void addCharacters(const QString& name, const QPixmap& image);

    QGraphicsPixmapItem* p_bgImageItem = nullptr;
    QImage* p_bgImgObject = nullptr;
    QGraphicsScene* p_mapScene = nullptr;
    QVector<QGraphicsItem*> vTmpItems;
    QVector<Block*> vBlocks;
    QVector<Item*> vItems;
    QVector<Character*> vCharacters;
    //item QVector
    //character QVector
    static qreal accumulatedScale;
    int tmpItempType = -1;
    QString tmpItemName = "";
    void* p_mw = nullptr;
};

#endif // MAPSCREEN_H
