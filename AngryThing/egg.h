#ifndef EGG_H
#define EGG_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define EGG_DENSITY 10.0f //密度
#define EGG_FRICTION 0.2f //摩擦力
#define EGG_RESTITUTION 0.2f //彈性

class egg : public GameItem
{
public:
    egg(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // EGG_H
