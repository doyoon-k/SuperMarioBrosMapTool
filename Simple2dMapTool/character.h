#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QGraphicsObject>

class Character : public QGraphicsObject
{
public:
    Character();
    Character(const QString& type, const QPixmap& img, QGraphicsItem* parent = nullptr);
    Character(const Character& other);
    Character& operator= (const Character& other);
    void setPosition(const QPointF& point);
    void setScale(qreal scale);
private:

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr)override;
//    void dragMovement(QGraphicsSceneDragDropEvent* event)override;
//    void mousePressEvent(QGraphicsSceneMouseEvent* event)override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;
    QRectF boundingRect()const override;

    QString CharacterType = "";
    QPixmap image;
};

#endif // CHARACTER_H
