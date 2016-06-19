#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define OBSTACLE_DENSITY 0.1f //密度
#define OBSTACLE_FRICTION 0.4f //摩擦力
#define OBSTACLE_RESTITUTION 0.5f //彈性

class obstacle : public GameItem
{
public:
    obstacle(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // OBSTACLE_H
