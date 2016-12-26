#ifndef COMMON_ANIMATION_H
#define COMMON_ANIMATION_H
#include <QPropertyAnimation>
#include <QPauseAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QTime>
#include <QApplication>
#include "def.h"
#include <iostream>
#include <vector>
using namespace std;

/*Animation library for atQlas.
 * Some of them are crowned generic, means you can freely use them to evey
 * item of Qt.
 * But the rest of them are only usable for the window itself.
 * You should not use them to morph items since they can take no effect.
 * * * * * * * * * * * * */

#define LEFT 1
#define RIGTH 2
#define UP 3
#define DOWN 4
using namespace std;
//QSequentialAnimationGroup *group;
//QSequentialAnimationGroup *group1;
Func (csleep, auto duration){
    QTime t;
    t.start();
    while(t.elapsed()<duration)
        QCoreApplication::processEvents();
};
auto breath=[](auto any, auto opacity, auto _opacity, auto time){
    QPropertyAnimation *ani = new QPropertyAnimation(any, "windowOpacity");
    ani->setDuration(time);
    ani->setStartValue(opacity);
    ani->setEndValue(_opacity);

    QPropertyAnimation *_ani = new QPropertyAnimation(any, "windowOpacity");
    _ani->setDuration(time);
    _ani->setStartValue(_opacity);
    _ani->setEndValue(opacity);
    ani->start();
    QAbstractAnimation::connect(ani, SIGNAL(finished()), _ani, SLOT(start()));
    QAbstractAnimation::connect(_ani, SIGNAL(finished()), ani, SLOT(start()));

};
auto one_breath=[](auto any, auto opacity, auto _opacity, auto time){
    QPropertyAnimation *ani = new QPropertyAnimation(any, "windowOpacity");
    ani->setDuration(time);
    ani->setStartValue(opacity);
    ani->setEndValue(_opacity);

    QPropertyAnimation *_ani = new QPropertyAnimation(any, "windowOpacity");
    _ani->setDuration(time);
    _ani->setStartValue(_opacity);
    _ani->setEndValue(opacity);
    ani->start();
    QAbstractAnimation::connect(ani, SIGNAL(finished()), _ani, SLOT(start()));

};

auto abstract_jump=[](auto any, auto margin, auto animation){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(3000);
    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setKeyValueAt(0.5,QRect(ank.x(),ank.y()-margin,any->width(), any->height()));
    ani1->setEndValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setEasingCurve(animation);//QEasingCurve::OutCurve);
    ani1->start();
    QAbstractAnimation:: connect(ani1, SIGNAL(finished()), ani1,SLOT(start()));
};


auto abstract_hangout=[](auto any, auto margin, auto duration){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);
    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setKeyValueAt(0.25,QRect(ank.x()-margin,ank.y(),any->width(), any->height()));
    ani1->setKeyValueAt(0.5, QRect(ank.x(), ank.y(), any->width(), any->height()));
    ani1->setKeyValueAt(0.75,QRect(ank.x()+margin,ank.y(),any->width(), any->height()));
    ani1->setEndValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setEasingCurve(QEasingCurve::Linear);//QEasingCurve::OutCurve);
    ani1->start();
    QAbstractAnimation:: connect(ani1, SIGNAL(finished()), ani1,SLOT(start()));
};
auto generic_move_in=[](auto any, auto margin, auto duration, int dir, auto group,auto xy){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);
    switch (dir) {
    case LEFT:
        ani1->setStartValue(QRect(xy[0],xy[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy[0]-margin,xy[1],any->width(),any->height()));
        //any->setGeometry(xy[0]+margin,xy[1],any->width(),any->height());
        break;
    case RIGTH:
        ani1->setStartValue(QRect(xy[0],xy[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy[0]+margin,xy[1],any->width(),any->height()));
        //any->setGeometry(xy[0]-margin,xy[1],any->width(),any->height());
        break;
    case UP:
        ani1->setStartValue(QRect(xy[0],xy[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy[0],xy[1]-margin,any->width(),any->height()));
        //any->setGeometry(xy[0],xy[1]-margin,any->width(),any->height());
        break;
    case DOWN:
        ani1->setStartValue(QRect(xy[0],xy[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy[0],xy[1]+margin,any->width(),any->height()));
        //any->setGeometry(xy[0],xy[1]+margin,any->width(),any->height());
        break;
    default:
        break;
    }
    ani1->setEasingCurve(QEasingCurve::OutQuart);//QEasingCurve::OutCurve);
    group->addAnimation(ani1);
    //ani1->start();
    //connect(ani1, SIGNAL(finished()), any, SLOT(startAnimation()));

};

auto generic_move_in1=[](auto any, auto margin, auto duration, int dir,auto group1,auto xy1){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);
    switch (dir) {
    case LEFT:
        ani1->setStartValue(QRect(xy1[0],xy1[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy1[0]-margin,xy1[1],any->width(),any->height()));
        //any->setGeometry(xy1[0]+margin,xy1[1],any->width(),any->height());
        break;
    case RIGTH:
        ani1->setStartValue(QRect(xy1[0],xy1[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy1[0]+margin,xy1[1],any->width(),any->height()));
        //any->setGeometry(xy1[0]-margin,xy1[1],any->width(),any->height());
        break;
    case UP:
        ani1->setStartValue(QRect(xy1[0],xy1[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy1[0],xy1[1]-margin,any->width(),any->height()));
        //any->setGeometry(xy1[0],xy1[1]-margin,any->width(),any->height());
        break;
    case DOWN:
        ani1->setStartValue(QRect(xy1[0],xy1[1],any->width(),any->height()));
        ani1->setEndValue(QRect(xy1[0],xy1[1]+margin,any->width(),any->height()));
        //xy1[1]=xy1[1]+margin;
        //any->setGeometry(xy1[0],xy1[1]+margin,any->width(),any->height());
        break;
    default:
        break;
    }
    ani1->setEasingCurve(QEasingCurve::OutQuart);//QEasingCurve::OutCurve);
    group1->addAnimation(ani1);

    //ani1->start();
    //connect(ani1, SIGNAL(finished()), any, SLOT(startAnimation()));

};

auto generic_move_in_4init=[](auto any, auto margin_lr, auto margin_ud,auto duration){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);
    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setEndValue(QRect(ank.x()+margin_ud,ank.y()+margin_lr,any->width(),any->height()));
    ani1->setEasingCurve(QEasingCurve::OutQuart);//QEasingCurve::OutCurve);
    ani1->start();
    //connect(ani1, SIGNAL(finished()), any, SLOT(startAnimation()));

};

auto start_group_animation=[](auto group, auto group1){
    group->start();
    group1->start();
};

auto generic_move_out=[](auto any, auto margin, auto duration){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);
    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setEndValue(QRect(ank.x()-margin,ank.y(),any->width(),any->height()));
    ani1->setEasingCurve(QEasingCurve::OutQuart);//QEasingCurve::OutCurve);
    ani1->start();
};

auto scaler=[](auto any, auto margin, auto animation, auto duration){
    QPoint ank=any->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);
    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setKeyValueAt(0.5,QRect(ank.x(),ank.y(),any->width()-margin, any->height()-margin));
    ani1->setEndValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setEasingCurve(animation);//QEasingCurve::OutCurve);
    ani1->start();
    QAbstractAnimation:: connect(ani1, SIGNAL(finished()), ani1,SLOT(start()));
};
auto scaler_once=[](auto any, auto margin, auto animation, auto duration){

    QPoint ank=any->pos();
    auto the_original=any->geometry();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);

    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setKeyValueAt(0.5,QRect(ank.x()+margin,ank.y()+margin,any->width()-2*margin, any->height()-2*margin));
    ani1->setEndValue(the_original);
    ani1->setEasingCurve(animation);//QEasingCurve::OutCurve);
    ani1->start();
};
auto scaler_once_animation_object=[](auto any, auto margin, auto animation, auto duration){

    QPoint ank=any->pos();
    auto the_original=any->geometry();
    QPropertyAnimation *ani1 = new QPropertyAnimation(any, "geometry");
    ani1->setDuration(duration);

    ani1->setStartValue(QRect(ank.x(),ank.y(),any->width(),any->height()));
    ani1->setKeyValueAt(0.5,QRect(ank.x()+margin,ank.y()+margin,any->width()-2*margin, any->height()-2*margin));
    ani1->setEndValue(the_original);
    ani1->setEasingCurve(animation);//QEasingCurve::OutCurve);
    return ani1;
};



auto fade=[](auto slot){
    QPropertyAnimation *animation = new QPropertyAnimation(slot, "windowOpacity");

    animation->setDuration(1500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
};
auto appear=[](auto slot){
    QPropertyAnimation *animation = new QPropertyAnimation(slot, "windowOpacity");
    animation->setDuration(1500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

};
auto fade_out=[](auto slot){
    QPropertyAnimation *animation = new QPropertyAnimation(slot, "windowOpacity");

    animation->setDuration(1500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    slot->connect(animation, SIGNAL(finished()), slot, SLOT(hide()));
};
auto fade_close=[](auto slot, auto duration){
    QPropertyAnimation *animation = new QPropertyAnimation(slot, "windowOpacity");

    animation->setDuration(duration);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    slot->connect(animation, SIGNAL(finished()), slot, SLOT(close()));
    return animation;
};

auto set_opacity=[](auto any, auto __this, auto opacity){
    auto *effect = new QGraphicsOpacityEffect(__this);
    effect->setOpacity(opacity);
    any->setGraphicsEffect(effect);
};

auto generic_one_breath=[](auto any, auto __this, auto opacity=1, auto _opacity=0.5, auto duration=1000){
    auto *effect = new QGraphicsOpacityEffect(__this);
    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity" );
    any->setGraphicsEffect(effect);
    anim->setDuration(duration);
    anim->setStartValue(opacity);
    anim->setKeyValueAt(0.5, _opacity);
    anim->setEndValue(opacity);
    anim->setEasingCurve( QEasingCurve::OutCurve);
    anim->start();
    return anim;
};

auto smoothed_generic_one_breath=[](auto any, auto __this, auto opacity=1, auto _opacity=0.5, auto duration=1000){
    generic_one_breath(any, __this, opacity, _opacity, duration);
    QTime t;
    t.start();
    while(t.elapsed()<500)
        QCoreApplication::processEvents();
};


auto generic_appear=[](auto any, auto __this, auto duration)
{
    auto *effect = new QGraphicsOpacityEffect(__this);
    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity" );
    any->setGraphicsEffect(effect);
    anim->setDuration(duration);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve( QEasingCurve::OutCurve);
    anim->start();
    return anim;
};
auto generic_fade=[](auto any, auto __this, auto duration){
    auto *effect = new QGraphicsOpacityEffect(__this);
    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity" );
    any->setGraphicsEffect(effect);
    anim->setDuration(duration);
    anim->setStartValue(1);
    anim->setEndValue(0);
    anim->setEasingCurve( QEasingCurve::OutCurve);
    anim->start();
    return anim;
};

//zero for forever.
Func (generic_breath, auto any, auto __this, auto opacity=1, auto _opacity=0, auto duration=1000){
    auto anim=generic_one_breath(any, __this, opacity, _opacity, duration);
    QAbstractAnimation::connect(anim, SIGNAL(finished()), anim, SLOT(start()));
};
//auto generic_appear=[](auto any, __this, )

auto travel_jump=[](auto __this, auto duration){
    QPoint ank=__this->pos();
    QPropertyAnimation *ani1 = new QPropertyAnimation(__this, "geometry");
    ani1->setDuration(duration);
    ani1->setStartValue(QRect(ank.x(),ank.y(),__this->width(),__this->height()));
    ani1->setKeyValueAt(0.1,QRect(ank.x(),ank.y()-50,__this->width(), __this->height()));
    ani1->setKeyValueAt(0.2,QRect(ank.x(),ank.y(),__this->width(), __this->height()));
    ani1->setKeyValueAt(0.3,QRect(ank.x(),ank.y()+50,__this->width(), __this->height()));
    ani1->setKeyValueAt(0.4,QRect(ank.x(),ank.y(),__this->width(), __this->height()));
    ani1->setKeyValueAt(0.5,QRect(ank.x(),ank.y()-50,__this->width(), __this->height()));
    ani1->setKeyValueAt(0.6,QRect(ank.x(),ank.y(),__this->width(), __this->height()));
    ani1->setKeyValueAt(0.7,QRect(ank.x(),ank.y()+50,__this->width(), __this->height()));
    ani1->setKeyValueAt(0.8,QRect(ank.x(),ank.y(),__this->width(), __this->height()));
    ani1->setKeyValueAt(0.9,QRect(ank.x(),ank.y()-50,__this->width(), __this->height()));
    ani1->setKeyValueAt(1,QRect(ank.x(),ank.y(),__this->width(), __this->height()));
    ani1->setEndValue(QRect(ank.x(),ank.y(),__this->width(),__this->height()));
    ani1->setEasingCurve(QEasingCurve::OutBounce);
    ani1->start();
    return ani1;
};
#endif // COMMON_ANIMATION_H

