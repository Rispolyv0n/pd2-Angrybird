#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QMouseEvent>

#define YELLOWBIRD_DENSITY 15.0f //密度
#define YELLOWBIRD_FRICTION 0.5f //摩擦力
#define YELLOWBIRD_RESTITUTION 0.1f //彈性

class yellowbird : public GameItem
{
public:
    yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    //void mousePressEvent(QMouseEvent *event);
};

#endif // YELLOWBIRD_H
