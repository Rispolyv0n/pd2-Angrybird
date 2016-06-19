#include "invwall.h"

invwall::invwall(float x, float y, float w, float h, b2World *world):GameItem(world)
{
    // Set pixmap
    //g_pixmap.setPixmap(pixmap);
    //g_size = QSize(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y); //初始位置
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f); //固定?

    //scene->addItem(&g_pixmap);
    //paint();
}
