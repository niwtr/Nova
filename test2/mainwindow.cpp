#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include "common_animation.h"
#include <iostream>
#include <vector>
#include <list>
#include "astar.hpp"

using std::vector;
using namespace std;


int cou,cou1;
int xy[2],xy1[2];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cou=0;
    cou1=0;
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height);
}

MainWindow::~MainWindow()
{
    delete ui;
}

auto MainWindow::find_p(int n)
{
    switch (n) {
    case 1:
        return ui->pushButton;
        break;
    case 2:
        return ui->pushButton_2;
        break;
    case 3:
        return ui->pushButton_3;
        break;
    case 4:
        return ui->pushButton_4;
        break;
    case 5:
        return ui->pushButton_5;
        break;
    case 6:
        return ui->pushButton_6;
        break;
    case 7:
        return ui->pushButton_7;
        break;
    case 8:
        return ui->pushButton_8;
        break;
    case 9:
        return ui->pushButton_9;
        break;
    default:
        break;
    }
}

void MainWindow::init_button(int init_arry[3][3])
{
    int num=0;
    auto p=ui->pushButton;
    //group = new QSequentialAnimationGroup;
    //group1 = new QSequentialAnimationGroup;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            num=init_arry[i][j];
            if(num==-1){
                num=9;
            }
            p=find_p(num);
            p->setGeometry(j*70,i*60,71,61);
        }
    }
}

void MainWindow::move_button(vector<vector<int> >  move)
{
    auto p=ui->pushButton;
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    QSequentialAnimationGroup *group1 = new QSequentialAnimationGroup;
    int nn=0;
    cou=0;
    cou1=0;
    for(auto m:move){
        switch (m[0]) {
        case 1:
            p=ui->pushButton;
            break;
        case 2:
            p=ui->pushButton_2;
            break;
        case 3:
            p=ui->pushButton_3;
            break;
        case 4:
            p=ui->pushButton_4;
            break;
        case 5:
            p=ui->pushButton_5;
            break;
        case 6:
            p=ui->pushButton_6;
            break;
        case 7:
            p=ui->pushButton_7;
            break;
        case 8:
            p=ui->pushButton_8;
        default:
            break;
        }

        int count1=0,count2=0;
        switch (m[1]) {
        case 1:
            count1=2;
            count2=70;
            break;
        case 2:
            count1=1;
            count2=70;
            break;
        case 3:
            count1=4;
            count2=60;
            break;
        case 4:
            count1=3;
            count2=60;
            break;
        default:
            break;
        }
        xy[0]=location[nn][0];
        xy[1]=location[nn][1];
        xy1[0]=location[nn][2];
        xy1[1]=location[nn][3];
        generic_move_in(ui->pushButton_9,count2,2000,m[1],group,xy);
        generic_move_in1(p,count2,2000,count1,group1,xy1);
        nn++;
        /*QTime t;
        t.start();
        while(t.elapsed()<5000)//{;}
            QCoreApplication::processEvents();*/
        //smoothed_generic_one_breath(ui->pushButton_9,this,1,0,1000);
    }
    start_group_animation(group,group1);
    connect(group, SIGNAL(currentAnimationChanged(QAbstractAnimation*)),
                this, SLOT(onCurrentAnimationChanged(QAbstractAnimation*)));
    connect(group1, SIGNAL(currentAnimationChanged(QAbstractAnimation*)),
                this, SLOT(onCurrentAnimationChanged1(QAbstractAnimation*)));
}
void MainWindow::onCurrentAnimationChanged(QAbstractAnimation *current)
{
    QPropertyAnimation *pAnimation = dynamic_cast<QPropertyAnimation *>(current);
    if (pAnimation == NULL)
        return;

    change_button(mm);
}

void MainWindow::change_button(vector<vector<int> > m)
{
    auto p=ui->pushButton_9;
    p->setGeometry(location[cou][2],location[cou][3],p->width(),p->height());
    cou++;
}

void MainWindow::onCurrentAnimationChanged1(QAbstractAnimation *current)
{
    QPropertyAnimation *pAnimation = dynamic_cast<QPropertyAnimation *>(current);
    if (pAnimation == NULL)
        return;

    change_button1(mm);
}

void MainWindow::change_button1(vector<vector<int> > m)
{
    auto p=find_p(m[cou1][0]);
    p->setGeometry(location[cou1][0],location[cou1][1],p->width(),p->height());
    cou1++;
}


