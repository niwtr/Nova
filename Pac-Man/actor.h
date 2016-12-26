#ifndef FIGUREPROTOTYPE_H
#define FIGUREPROTOTYPE_H

#include <QQuickItem>
#include <QSGNode>

class Actor : public QQuickItem
{
    Q_OBJECT

public:
    explicit Actor(int x, int y, int speed, QQuickItem *parent = NULL);
    ~Actor(){}

    int getX() {
        return curX;
    }
    int getY() {
        return curY;
    }
    int setSpeed(int speed) {
        this->speed = speed;
    }

    void updatePaintNode(QSGNode *, UpdatePaintNodeData *);

public slots:
    void setX(int x);
    void setY(int y);

protected:
    int curX;
    int curY;

    int tarX;
    int tarY;

    int speed;
};

#endif // FIGUREPROTOTYPE_H
