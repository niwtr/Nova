#include "actor.h"

Actor::Actor(int x, int y, int speed, QQuickItem *parent):
    curX(x), curY(y), speed(speed), QQuickItem(parent)
{

}

void Actor::updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData *) {

}

void Actor::setX(int x) {
    this->tarX = x;
    update();
}

void Actor::setY(int y) {
    this->tarY = y;
    update();
}
