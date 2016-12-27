#include "numblock.h"
#include <QApplication>
#include <QMouseEvent>

NumBlock::NumBlock(QWidget *parent) :
    QPushButton(parent)
{

}

void NumBlock::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        QMouseEvent newEvent(QEvent::MouseButtonPress, this->mapToParent(event->pos()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(this->parent(), &newEvent);
    }
}
