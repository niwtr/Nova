#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <list>
#include <map>
#include <QMessagebox.h>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QLayout>
#include <QVBoxLayout>
#include <QIcon>
#include "Path8.h"
#include "common_animation.h"
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;


int cou,cou1;
int xy[2],xy1[2];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    creatBlock();

    srand((unsigned)time(NULL));
    cou=0;
    cou1=0;
    this->setWindowTitle("八数码");
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height);
    setMouseTracking(true);
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
            }
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

void MainWindow::creatBlock() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            NumBlock *block = new NumBlock(this);
            if(i != 2 || j != 2)
                block->setText(QString::number(i*3+j+1));
            block->setGeometry(j*70,i*60,71,61);

            numBlock.push_back(block);
        }
    }
    QIcon icon0,icon1,icon2,icon3,icon4,icon5,icon6,icon7,icon8;
    icon0.addFile(tr(":/new/prefix1/res/test_0.jpg"));
    icon1.addFile(tr(":/new/prefix1/res/test_1.jpg"));
    icon2.addFile(tr(":/new/prefix1/res/test_2.jpg"));
    icon3.addFile(tr(":/new/prefix1/res/test_3.jpg"));
    icon4.addFile(tr(":/new/prefix1/res/test_4.jpg"));
    icon5.addFile(tr(":/new/prefix1/res/test_5.jpg"));
    icon6.addFile(tr(":/new/prefix1/res/test_6.jpg"));
    icon7.addFile(tr(":/new/prefix1/res/test_7.jpg"));
    icon8.addFile(tr(":/new/prefix1/res/test_8.jpg"));

    numBlock[0]->setIcon(icon0);
    numBlock[1]->setIcon(icon1);
    numBlock[2]->setIcon(icon2);
    numBlock[3]->setIcon(icon5);
    numBlock[4]->setIcon(icon8);
    numBlock[5]->setIcon(icon7);
    numBlock[6]->setIcon(icon6);
    numBlock[7]->setIcon(icon3);
    numBlock[8]->setIcon(icon4);
    numBlock[0]->setIconSize(QSize(71,61));
    numBlock[1]->setIconSize(QSize(71,61));
    numBlock[2]->setIconSize(QSize(71,61));
    numBlock[3]->setIconSize(QSize(71,61));
    numBlock[4]->setIconSize(QSize(71,61));
    numBlock[5]->setIconSize(QSize(71,61));
    numBlock[6]->setIconSize(QSize(71,61));
    numBlock[7]->setIconSize(QSize(71,61));
    numBlock[8]->setIconSize(QSize(71,61));
    numBlock[0]->setFlat(true);
    numBlock[1]->setFlat(true);
    numBlock[2]->setFlat(true);
    numBlock[3]->setFlat(true);
    numBlock[0]->setFlat(true);
    numBlock[4]->setFlat(true);
    numBlock[5]->setFlat(true);
    numBlock[6]->setFlat(true);
    numBlock[7]->setFlat(true);
    numBlock[8]->setFlat(true);
}

NumBlock* MainWindow::find_p(int n)
{
    if(n >= 1 && n <= 9)
        return numBlock[n-1];
    return NULL;
}

void MainWindow::init_button()
{
    int num=0;
    auto p = numBlock[0];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            num=INIT[i][j];
            TEMP[i][j]=INIT[i][j];
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
    auto p=numBlock[0];
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    QSequentialAnimationGroup *group1 = new QSequentialAnimationGroup;
    int nn=0;
    cou=0;
    cou1=0;
    for(auto m:move){
        p = find_p(m[0]);

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
        generic_move_in(numBlock[8],count2,2000,m[1],group,xy);
        generic_move_in1(p,count2,2000,count1,group1,xy1);
        nn++;
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
    auto p=numBlock[8];
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

    bool flag=true;

    for(int j = 0; j < 3; j++){
        for(int k = 0; k < 3; k++){
            flag = true;
            for(int m = 0; m < 3 && flag; m++){
                for(int n = 0; n < 3 && flag; n++){
                    if(INIT[j][k] == TEMP[m][n]){
                        change_location[j][k][1] = (m-j)*60;//(m-j)*60
                        change_location[j][k][0] = (n-k)*70;//(n-k)*70
                        flag=false;
                    }
                }
            }
        }
    }
}

auto MainWindow::findBut(QPoint point)
{
    for(int i = 0; i < 9; i++) {
        if(numBlock[i]->geometry().contains(point)) {
            curBut = i+1;
            if(curBut == 9)
                curBut = -1;

            for(int x=0;x<3;x++)
                for(int y=0;y<3;y++)
                {
                    curBut==INIT[x][y];
                    pointx=70*x;
                    pointy=60*y;
                }
            return numBlock[i];
        }
    }
}
//现在的问题的curpoint 一直停留在左上角的位置
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        qDebug() << "按下左键\n" << event->pos() << endl;
        curpoint=event->pos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        qDebug() << "释放左键\n" << event->pos() << endl;
        nextpoint=event->pos();
        if(nextpoint.y() >= 0 && nextpoint.y() <= 180 && nextpoint.x() >= 0 && nextpoint.x() <= 210){

            int num1,num2;

            NumBlock* block1 = findBut(curpoint);
            num1=curBut;
            NumBlock* block2 = findBut(nextpoint);
            num2=curBut;

            QPoint posChange = block1->pos() - block2->pos();
            if(num1 == num2)
                return;

            generic_move_in_4init(block1, -posChange.x(), -posChange.y(), 1000);
            generic_move_in_4init(block2, posChange.x(), posChange.y(), 1000);

            exchange(num1,num2);
        }
    }

}
void MainWindow::exchange(int num1, int num2)
{
    int num1x,num1y,num2x,num2y;
    for(int i=0;i<3;i++)
       for(int j=0;j<3;j++){
           if(num1==INIT[i][j]){
               num1x=i;
               num1y=j;
           }
           if(num2==INIT[i][j])
           {
               num2x=i;
               num2y=j;
           }
       }
    int temp=INIT[num1x][num1y];
    INIT[num1x][num1y]=INIT[num2x][num2y];
    INIT[num2x][num2y]=temp;
}

void MainWindow::on_pushButton_11_clicked()
{
    Path8 p = Path8(this->INIT);
    a_star<Path8> astar_digit8;
    astar_digit8.init_path(p);
    if(astar_digit8.search()==false)
    {
        QMessageBox::information(this,"warning","Having no path!");
    }
    else
    {

        astar_digit8.search();
        list<Path8> lp8;
        astar_digit8.get_all_paths(lp8);
        vector<vector<int> > draw;
        draw=astar_digit8.CHANGES;
        //w.init_button(init);
        init_button();
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

}

void MainWindow::on_pushButton_init_clicked()
{
    auto p=numBlock[0];
    init_button_location();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(INIT[i][j]!=-1){
                p=find_p(INIT[i][j]);
            }
            else{
                p=numBlock[8];
            }
            generic_move_in_4init(p, change_location[i][j][0], change_location[i][j][1],1000);
        }
    }
    for(int k=0;k<3;k++){
        for(int l=0;l<3;l++){
            INIT[k][l]=TEMP[k][l];
        }
    }
}
