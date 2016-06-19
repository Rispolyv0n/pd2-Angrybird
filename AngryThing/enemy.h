#ifndef ENEMY_H
#define ENEMY_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define ENEMY_DENSITY 3.0f //密度
#define ENEMY_FRICTION 0.2f //摩擦力
#define ENEMY_RESTITUTION 0.2f //彈性

class enemy : public GameItem
{
public:
    enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // ENEMY_H
