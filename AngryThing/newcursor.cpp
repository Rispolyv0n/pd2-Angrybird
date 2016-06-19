#include "newcursor.h"

newcursor::newcursor()
{
    setShape(Qt::OpenHandCursor);
    setPos(QCursor::pos().x(),QCursor::pos().y());
}
