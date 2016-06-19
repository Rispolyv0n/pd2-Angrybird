#ifndef WHITEBIRD_H
#define WHITEBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define WHITEBIRD_DENSITY 10.0f //密度
#define WHITEBIRD_FRICTION 0.2f //摩擦力
#define WHITEBIRD_RESTITUTION 0.5f //彈性

class whitebird : public GameItem
{
public:
    whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    int alreadyclicked;
};

#endif // WHITEBIRD_H
