#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QWidget>
#include <QGraphicsObject>

class Environment:public QGraphicsObject
{
public:
    Environment();
    Environment(const QString& type,const QPixmap& img, QGraphicsItem* parent = nullptr);
    Environment(const Environment& other);
    Environment& operator= (const Environment& other);
private:

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr)override;
//    void dragMovement(QGraphicsSceneDragDropEvent* event)override;
//    void mousePressEvent(QGraphicsSceneMouseEvent* event)override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;
    QRectF boundingRect()const override;

    QString EnvironmentType = "";
    QPixmap image;
};

#endif // ENVIRONMENT_H
