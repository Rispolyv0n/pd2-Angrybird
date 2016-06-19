#ifndef INVWALL_H
#define INVWALL_H

#include <gameitem.h>
#include <QGraphicsScene>

class invwall : public GameItem
{
public:
    invwall(float x, float y, float w, float h, b2World *world);
};

#endif // INVWALL_H
