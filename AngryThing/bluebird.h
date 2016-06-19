#ifndef BLUEBIRD_H
#define BLUEBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BLUEBIRD_DENSITY 8.0f //密度
#define BLUEBIRD_FRICTION 0.2f //摩擦力
#define BLUEBIRD_RESTITUTION 0.5f //彈性

class bluebird : public GameItem
{
public:
    bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void morebird(b2World *world, QGraphicsScene *scene, int *once);
    int alreadyclicked;
};

#endif // BLUEBIRD_H





