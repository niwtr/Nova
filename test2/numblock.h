#ifndef NUMBLOCK_H
#define NUMBLOCK_H

#include <QObject>
#include <QPushButton>

class NumBlock : public QPushButton
{
public:
    explicit NumBlock(QWidget *parent = Q_NULLPTR);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // NUMBLOCK_H
