#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//#include <iostream>
//#include <vector>
#include <algorithm>
#include <list>
#include <map>
//#include "astar.hpp"
//#include "path_pacman.h"
#include "Path8.h"
#include "common_animation.h"

//using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;

//using namespace nova_kernel;
//using namespace std;


int cou,cou1;
int xy[2],xy1[2];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand((unsigned)time(NULL));

    /*for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            INIT[i][j]=3*i+j+1;
        }
    }
    INIT[2][2]=-1;*/
    cou=0;
    cou1=0;
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height);
    //init_INIT();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_INIT()
{
    Solvable[0][0][0]=1;
    Solvable[0][0][1]=2;
    Solvable[0][0][2]=3;
    Solvable[0][1][0]=8;
    Solvable[0][1][1]=-1;
    Solvable[0][1][2]=4;
    Solvable[0][2][0]=7;
    Solvable[0][2][1]=6;
    Solvable[0][2][2]=5;
    int dir[201];
    dir[0]=0;
    int i=0,j=0,k=0,m=0,n=0,I=0;
    int num1=0,num2=0,num3=0,num4=1;
    bool flag=true;
    i=0;
    while(i<=79){
        I=i;
        j=k=0;
        flag=true;
        for(j=0;j<3&&flag;j++){
            for(k=0;k<3&&flag;k++){//cout<<Solvable[I][j][k]<<"**";
                if(Solvable[I][j][k]==-1){
                    num1=j;
                    num2=k;
                    flag=false;
                }
            }
        }//cout<<endl;
        if(num1>0&&dir[I]!=2){
            m=n=0;
            for(m=0;m<3;m++){
                for(n=0;n<3;n++){
                    Solvable[i+1][m][n]=Solvable[I][m][n];
                }
            }S
            num3=Solvable[i+1][num1-1][num2];
            Solvable[i+1][num1-1][num2]=Solvable[i+1][num1][num2];
            Solvable[i+1][num1][num2]=num3;
            dir[i+1]=1;
            i++;
            if(i>=80){
                break;
            }
        }
        if(num1<2&&dir[I]!=1){
            m=n=0;
            for(m=0;m<3;m++){
                for(n=0;n<3;n++){
                    Solvable[i+1][m][n]=Solvable[I][m][n];
                }
            }
            num3=Solvable[i+1][num1+1][num2];
            Solvable[i+1][num1+1][num2]=Solvable[i+1][num1][num2];
            Solvable[i+1][num1][num2]=num3;
            i++;
            if(i>=80){
                break;
            }
        }
        if(num2>0&&dir[I]!=4){
            m=n=0;
            for(m=0;m<3;m++){
                for(n=0;n<3;n++){
                    Solvable[i+1][m][n]=Solvable[I][m][n];
                }
            }
            num3=Solvable[i+1][num1][num2-1];
            Solvable[i+1][num1][num2-1]=Solvable[i+1][num1][num2];
            Solvable[i+1][num1][num2]=num3;
            dir[i+1]=3;
            i++;
            if(i>=80){
                break;
            }
        }
        if(num2<2&&dir[I]!=3){
            m=n=0;
            for(m=0;m<3;m++){
                for(n=0;n<3;n++){
                    Solvable[i+1][m][n]=Solvable[I][m][n];
                }
            }
            num3=Solvable[i+1][num1][num2+1];
            Solvable[i+1][num1][num2+1]=Solvable[i+1][num1][num2];
            Solvable[i+1][num1][num2]=num3;
            dir[i+1]=4;
            i++;
            if(i>=80){
                break;
            }
        }

    }
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

void MainWindow::init_button()
{
    int num=0;
    auto p=ui->pushButton;
    //group = new QSequentialAnimationGroup;
    //group1 = new QSequentialAnimationGroup;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            num=INIT[i][j];
            //TEMP[i][j]=INIT[i][j];
           // num=init_arry[i][j];
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

void MainWindow::init_button_location()
{

    int num1=0;
    num1=rand()%78;
    num1++;
    for(int i1=0;i1<3;i1++){
        for(int i2=0;i2<3;i2++){
            if(Solvable[num1][i1][i2]>8){
                TEMP[i1][i2]=-1;
            }
            else{
                TEMP[i1][i2]=Solvable[num1][i1][i2];
            }
        }
    }
    /*for(int i=0;i<=9;i++){//随机更改后的坐标
        num1=rand()%3;
        num3=rand()%3;
        num2=(num1 +num3)%3;//cout<<num2<<"  "<<num2<<endl;
        temp=TEMP[num2][num1];
        TEMP[num2][num1]=TEMP[num1][num2];
        TEMP[num1][num2]=temp;
    }*/
    //int temp1=0;
    bool flag=true;cout<<endl;
    int m=0;
    int n=0;
    for(int j=0;j<3;j++){
        for(int k=0;k<3;k++){
            flag=true;//cout<<TEMP[j][k]<<"~~"<<INIT[j][k]<<endl;
            m=n=0;
            for(m=0;m<3&&flag;m++){
                for(n=0;n<3&&flag;n++){
                    if(INIT[j][k]==TEMP[m][n]){
                        change_location[j][k][0]=(m-j)*60;//(m-j)*60
                        change_location[j][k][1]=(n-k)*70;//(n-k)*70
                        flag=false;
                    }
                }
            }
        }
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    auto p=ui->pushButton;
    init_button_location();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(INIT[i][j]!=-1){
                p=find_p(INIT[i][j]);
            }
            else{
                p=ui->pushButton_9;
            }
            generic_move_in_4init(p, change_location[i][j][0], change_location[i][j][1],1000);
        }
    }
    /*for(int m=0;m<3;m++){
        for(int n=0;n<3;n++){
            p=find_p(INIT[m][n]);
            p->setGeometry(p->x()+change_location[m][n][0],p->y()+change_location[m][n][1],p->width(),p->height());
        }
    }*/
    for(int k=0;k<3;k++){
        for(int l=0;l<3;l++){
            INIT[k][l]=TEMP[k][l];
        }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    Path8 p = Path8(INIT);
    for(int i1=0;i1<3;i1++){
        for(int i2=0;i2<3;i2++){
            cout<<INIT[i1][i2];
        }
    }
    a_star<Path8> astar_digit8;
    astar_digit8.init_path(p);
    astar_digit8.search();
    list<Path8> lp8;
    //int temp[3][3];
    //temp=astar_digit8.get_all_paths(lp8);//get all the paths to go.
    astar_digit8.get_all_paths(lp8);
   /* for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            //init[i][j]=w.INIT[i][j];
            w.INIT[i][j]=temp[i][j];
        }
    }*/
    vector<vector<int> > draw;
    draw=astar_digit8.CHANGES;
    init_button();
    //init_button();
    location=astar_digit8.calculate_location(astar_digit8.CHANGES,INIT);
    mm=astar_digit8.CHANGES;
    move_button(astar_digit8.CHANGES);

    for(auto _p : lp8){
        _p.output();
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                INIT[i][j]=_p.return_value(i,j);
                TEMP[i][j]=INIT[i][j];
                //cout<<INIT[i][j]<<"&&&&";
            }
        }
    }
}
