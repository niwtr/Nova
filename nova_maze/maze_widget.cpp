#include "maze_widget.h"
#include <list>
#include <cmath>
using std::list;

long long path_maze::_id=0;

MazeWidget::MazeWidget(QWidget *parent)
    : QWidget(parent)
{
    first=true;
    M=51;
    N=51;
    magic=3;
    films=3;
    steps=0;
    zerostepn=0;
    this->setWindowTitle("Maze A*");
    this->resize(N*pixel_size+7*20,M*pixel_size+4*20);
    this->setFocus(Qt::MouseFocusReason);
    Xline=new QLineEdit(this);
    Yline=new QLineEdit(this);
    Xline->setText("51");
    Yline->setText("51");
    Xline->setGeometry(30,(M+2)*pixel_size,40,20);
    Yline->setGeometry(90,(M+2)*pixel_size,40,20);




    film_rest=new QLabel(this);
    film_rest->setText("Films remain: "+QString::number(this->films));
    film_rest->setGeometry((N+2)*pixel_size,180,120,20);
    magic_rest=new QLabel(this);
    magic_rest->setText("Foresees remain: "+QString::number(this->magic));
    magic_rest->setGeometry((N+2)*pixel_size,210,120,20);

    stepn=new QLabel(this);
    stepn->setText("Your steps: "+QString::number(this->steps));
    stepn->setGeometry((N+2)*pixel_size,240,120,20);

    zerostepn=new QLabel(this);
    zerostepn->setGeometry((N+2)*pixel_size,270,120,20);



    create_maze_button=new QPushButton(this);
    create_maze_button->setText("Create");
    create_maze_button->setGeometry(150,(M+2)*pixel_size,60,20);


    find_short_path_button=new QPushButton(this);
    find_short_path_button->setText("Foresee");
    find_short_path_button->setGeometry((N+2)*pixel_size,60,60,20);
    find_short_path_button->setEnabled(false);

    cheat_mode_button=new QPushButton(this);
    cheat_mode_button->setText("Cheat");
    cheat_mode_button->setGeometry((N+2)*pixel_size,90,60,20);
    cheat_mode_button->setEnabled(false);

    cancel_button=new QPushButton(this);
    cancel_button->setText("Uncheat");
    cancel_button->setGeometry((N+2)*pixel_size,120,60,20);
    cancel_button->setEnabled(false);

    invert_button=new QPushButton(this);
    invert_button->setText("Snap!");
    invert_button->setGeometry((N+2)*pixel_size,150,60,20);
    invert_button->setEnabled(false);


    timer=NULL;
    //创建迷宫矩阵
    matrix=new Maze*[M];
    for(int i=0;i<M;i++)
    {
        matrix[i]=new Maze[N];
    }
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
        {
            matrix[i][j].state=pixel_type::wall;//初始化迷宫矩阵，将所有节点设置为墙
            matrix[i][j].i=i;
            matrix[i][j].j=j;
        }
    //随机生成种子数
    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    MazeStack=new stack<Maze>;
    FinalPath=new vector<Maze>;
    X=1;
    Y=1;
    cheat_mode=false;



    connect(create_maze_button,SIGNAL(clicked()),this,SLOT(create_maze_button_slot()));
    connect(cheat_mode_button,SIGNAL(clicked()),this,SLOT(cheat_mode_button_slot()));
    connect(cancel_button,SIGNAL(clicked()),this,SLOT(cancel_button_slot()));
    connect(find_short_path_button,SIGNAL(clicked()),this,SLOT(find_path_button_slot()));
    connect(invert_button,SIGNAL(clicked(bool)),this,SLOT(invert_button_slot()));
}

MazeWidget::~MazeWidget()
{

}

void MazeWidget::keyPressEvent(QKeyEvent *e)
{
    if(cheat_mode)//如果拆墙
    {
        if(e->key()==87||e->key()==16777235)//上
        {
            if(X>1)
            {
                X=X-1;
                steps++;
            }
        }
        else if(e->key()==83||e->key()==16777237)//下
        {
            if(X<M-2)
            {
                X=X+1;
                steps++;
            }
        }
        else if(e->key()==65||e->key()==16777234)//左
        {
            if(Y>1)
            {
                Y=Y-1;
                steps++;
            }
        }
        else if(e->key()==68||e->key()==16777236)//右
        {

            if(Y<N-2)
            {
                Y=Y+1;
                steps++;
            }
        }

        if(matrix[X][Y].state==pixel_type::film){
            films++;
            fresh_films();
        }
        else if (matrix[X][Y].state==pixel_type::magic)
        {
            magic++;
            fresh_magic();
        }


        matrix[X][Y].state=pixel_type::pass;
        //当老鼠到达粮仓时，重新构建迷宫地图，使得存放路劲的容器置为空
        if(X==M-2&&Y==N-2)
        {
            QMessageBox::information(this,"Congratulations!","You've found your way out!",QMessageBox::Yes);
            QMessageBox::information(this,"Congratulations!","Your score: "+QString::number((zerosteps-steps)*zerosteps),QMessageBox::Yes);

            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    matrix[i][j].state=pixel_type::wall;
            this->create_maze();
            cheat_mode=false;
            cancel_button->setEnabled(false);
            cheat_mode_button->setEnabled(true);
            find_short_path_button->setEnabled(true);
            create_maze_button->setEnabled(true);
            invert_button->setEnabled(true);
            FinalPath->clear();
            X=M/2;
            Y=N/2;
            if(X%2==0)
                X+=1;
            if(Y%2==0)
                Y+=1;
        }
    }
    else
    {
        int k;
        if(e->key()==87||e->key()==16777235)//上
        {
            k=X-1;
            if(k>0&&matrix[k][Y].state!=pixel_type::wall){
                X=k;
                steps++;
            }
        }
        else if(e->key()==83||e->key()==16777237)//下
        {
            k=X+1;
            if(k<M-1&&matrix[k][Y].state!=pixel_type::wall){
                X=k;
                steps++;
            }
        }
        else if(e->key()==65||e->key()==16777234)//左
        {
            k=Y-1;
            if(k>0&&matrix[X][k].state!=pixel_type::wall){
                Y=k;
                steps++;
            }
        }
        else if(e->key()==68||e->key()==16777236)//右
        {
            k=Y+1;
            if(k<N-1&&matrix[X][k].state!=pixel_type::wall){
                Y=k;
                steps++;
            }
        }


        if(matrix[X][Y].state==pixel_type::film){
            films++;
            fresh_films();
        }
        else if (matrix[X][Y].state==pixel_type::magic)
        {
            magic++;
            fresh_magic();
        }



        if(X==M-2&&Y==N-2)
        {
            QMessageBox::information(this,"Congratulations!","You've found your way out!",QMessageBox::Yes);
             QMessageBox::information(this,"Congratulations!","Your score: "+QString::number((zerosteps-steps)*zerosteps),QMessageBox::Yes);
            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                    matrix[i][j].state=pixel_type::wall;
            this->create_maze();
            FinalPath->clear();
            X=M/2;
            Y=N/2;
            if(X%2==0)
                X+=1;
            if(Y%2==0)
                Y+=1;
        }

    }
    update();
}
void MazeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    film_rest->setText("Films remain: "+QString::number(this->films));
    stepn->setText("Your steps: "+QString::number(this->steps));
    magic_rest->setText("Foresees remain: "+QString::number(this->magic));
    matrix[X][Y].state=pixel_type::pass;

    if(!first)
    {
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++)
            {
                if(i==X&&j==Y)//画老鼠
                {
                    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                    painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                }
                else if(i==M-2&&j==N-2)//画粮仓
                {
                    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                    painter.drawRect(QRect(j*pixel_size, i*pixel_size, pixel_size, pixel_size));
                }
                else
                {
                    switch(matrix[i][j].state)
                    {
                    case pixel_type::wall://画墙壁
                        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
                        painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                        break;
                    case pixel_type::pass://画通路
                        painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
                        painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                        break;
                    case pixel_type::colored://画迷宫寻找路径
                        painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                        painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                        break;

                    case pixel_type::checked:
                        painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                        painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                        break;
                    case pixel_type::film:
                        painter.setBrush(QBrush(Qt::magenta,Qt::SolidPattern));
                        painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                        break;
                    case pixel_type::magic:
                        painter.setBrush(QBrush(Qt::cyan,Qt::SolidPattern));
                        painter.drawRect(QRect(j*pixel_size,i*pixel_size,pixel_size,pixel_size));
                        break;

                    }
                }
            }
    }
}
void MazeWidget::create_maze_button_slot()
{
    if(oddp())
    {
        if(Xline->text().toInt()>5&&Yline->text().toInt()>5)
        {
            //删除原先matrix数组
            for(int i=0;i<M;i++)
            delete [] matrix[i];
            delete [] matrix;
            M=Xline->text().toInt();
            N=Yline->text().toInt();
            this->resize((N*pixel_size+7*20),(M*pixel_size+4*20));
            Xline->setGeometry(30,(M+2)*pixel_size,40,20);
            Yline->setGeometry(90,(M+2)*pixel_size,40,20);
            create_maze_button->setGeometry(150,(M+2)*pixel_size,60,20);
            find_short_path_button->setGeometry((N+2)*pixel_size,60,60,20);
            cheat_mode_button->setGeometry((N+2)*pixel_size,90,60,20);
            cancel_button->setGeometry((N+2)*pixel_size,120,60,20);
            invert_button->setGeometry((N+2)*pixel_size,150,60,20);
            film_rest->setGeometry((N+2)*pixel_size,180,120,20);
            magic_rest->setGeometry((N+2)*pixel_size,210,120,20);
            stepn->setGeometry((N+2)*pixel_size,240,120,20);
            zerostepn->setGeometry((N+2)*pixel_size,270,120,20);
            FinalPath->clear();
            cheat_mode_button->setEnabled(true);
            find_short_path_button->setEnabled(true);
            invert_button->setEnabled(true);
            cheat_mode=false;
            this->setFocus(Qt::MouseFocusReason);
            //初始老鼠的位置，在迷宫的中央
            X=M/2;
            Y=N/2;
            if(X%2==0)
                X+=1;
            if(Y%2==0)
                Y+=1;
            //重新创建新matrix数组，因为M和N发生了改变
            matrix=new Maze*[M];
            for(int i=0;i<M;i++)
            {
                matrix[i]=new Maze[N];
            }
            for(int i=0;i<M;i++)
                for(int j=0;j<N;j++)
                {
                    matrix[i][j].state=pixel_type::wall;//初始化迷宫矩阵，将所有节点设置为墙
                    matrix[i][j].i=i;
                    matrix[i][j].j=j;
                }
            this->create_maze();
            first=false;
            update();
        }
        else
        {
            QMessageBox::information(this,"Alert","Size's too small.",QMessageBox::Yes);
            Xline->clear();
            Yline->clear();
        }
    }
    else
    {
        QMessageBox::information(this,"Alert","Input odd number,please!",QMessageBox::Yes);
        Xline->clear();
        Yline->clear();
    }

    Agent.clear();
    cell cur, achieve;cur.i=X;cur.j=Y;
    achieve.i=M-2;achieve.j=N-2;
    path_maze path=path_maze(cur,this->matrix);
    path.set_destination(achieve);
    Agent.init_path(path);

    if(!Agent.search()){
        return;
    }
    list<path_maze> pl;
    Agent.get_all_paths(pl);
    for(path_maze p : pl){
        this->zerosteps++;
    }

    zerostepn->setText("Goal steps: "+QString::number(this->zerosteps));

    Agent.clear();

    fresh_films();
    fresh_magic();
}
bool MazeWidget::oddp()
{
    if(Xline->text().toInt()%2==0||Yline->text().toInt()%2==0)
        return false;
    return true;
}
//创建迷宫节点矩阵
void MazeWidget::create_maze()
{
    //先设置初始点为(3,3)
    int i=3,j=3;
    //设置随机数
    int randNum=0;
    //设置迷宫节点矩阵初始点位置为通路
    matrix[i][j].state=pixel_type::pass;
    //定义一个临时节点
    Maze temp;
    temp.i=i;
    temp.j=j;
    temp.state=pixel_type::pass;
    //false表示访问的方向，
    bool Up=false;
    bool Down=false;
    bool Right=false;
    bool Left=false;
    //进入循环，不断生成迷宫矩阵，直至栈为空
    while(1)
    {
        temp.i=i;
        temp.j=j;
        randNum=qrand()%4;
        switch(randNum)
        {
        case 0://上
            if(!Up&&i>2&&matrix[i-2][j].state==pixel_type::wall)
            {
                MazeStack->push(temp);
                matrix[i-2][j].state=pixel_type::pass;
                matrix[i-1][j].state=pixel_type::pass;
                i=i-2;
                Up=false;
                Down=false;
                Right=false;
                Left=false;
            }
            else
                Up=true;
            break;
        case 1://下
            if(!Down&&i<M-3&&matrix[i+2][j].state==pixel_type::wall)
            {
                MazeStack->push(temp);
                matrix[i+2][j].state=pixel_type::pass;
                matrix[i+1][j].state=pixel_type::pass;
                i=i+2;
                Up=false;
                Down=false;
                Right=false;
                Left=false;
            }
            else
                Down=true;
            break;
        case 2://左
            if(!Left&&j>2&&matrix[i][j-2].state==pixel_type::wall)
            {
                MazeStack->push(temp);
                matrix[i][j-2].state=pixel_type::pass;
                matrix[i][j-1].state=pixel_type::pass;
                j=j-2;
                Up=false;
                Down=false;
                Right=false;
                Left=false;
            }
            else
                Left=true;
            break;
        case 3://右
            if(!Right&&j<N-3&&matrix[i][j+2].state==pixel_type::wall)
            {
                MazeStack->push(temp);
                matrix[i][j+2].state=pixel_type::pass;
                matrix[i][j+1].state=pixel_type::pass;
                j=j+2;
                Up=false;
                Down=false;
                Right=false;
                Left=false;
            }
            else
                Right=true;
            break;
        }
        if(Up&&Down&&Right&&Left)//如果当前访问节点四个方向都没有可拆的节点，回溯
        {
            if(!MazeStack->empty())
            {
                i=MazeStack->top().i;
                j=MazeStack->top().j;
                MazeStack->pop();
                Up=false;
                Down=false;
                Right=false;
                Left=false;
            }
            else//如果栈为空的话就返回，此时迷宫矩阵已经创建完毕
                return;
        }
    }
}


void MazeWidget::cheat_mode_button_slot()
{
    FinalPath->clear();
    //使得迷宫矩阵的state为2的值变为1
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].state==pixel_type::colored ||
                    matrix[i][j].state==pixel_type::checked
                    )
            {
                matrix[i][j].state=pixel_type::pass;
            }
        }
    update();
    cheat_mode=true;
    this->setFocus(Qt::MouseFocusReason);
    cancel_button->setEnabled(true);
    cheat_mode_button->setEnabled(false);
    create_maze_button->setEnabled(false);
    find_short_path_button->setEnabled(false);
    invert_button->setEnabled(false);
    QMessageBox::information(this,"Info","Cheat mode is on, move wherever you want!",QMessageBox::Yes);
}
void MazeWidget::cancel_button_slot()
{
    cheat_mode=false;
    this->setFocus(Qt::MouseFocusReason);
    cheat_mode_button->setEnabled(true);
    cancel_button->setEnabled(false);
    create_maze_button->setEnabled(true);
    find_short_path_button->setEnabled(true);
    invert_button->setEnabled(true);
}

using std::cout;using std::endl;
void MazeWidget::find_path(){
    Agent.clear();
    cell cur, achieve;cur.i=X;cur.j=Y;
    achieve.i=M-2;achieve.j=N-2;
    path_maze path=path_maze(cur,this->matrix);
    path.set_destination(achieve);
    Agent.init_path(path);

    if(!Agent.search()){
        cout<<"No path."<<endl;
        return;
    }
    list<path_maze> pl;
    Agent.get_all_paths(pl);
    for(path_maze p : pl){
        cell sp=p.get_state();
        this->matrix[sp.i][sp.j].state=pixel_type::colored;
    }

}

void MazeWidget::fresh_films()
{

    for(int i=1;i<M-1;i++){
        for(int j=1;j<N-2;j++){
            if(matrix[i][j].state==pixel_type::film)
                matrix[i][j].state=pixel_type::pass;
        }
    }


    int beans=int(sqrt(M*N))/10;
    vector<cell> clist;

    for(int i=1;i<M-1;i++){
        for(int j=1;j<N-2;j++){
            int nums=0;
            nums+=matrix[i-1][j].state==pixel_type::wall?1:0;
            nums+=matrix[i+1][j].state==pixel_type::wall?1:0;
            nums+=matrix[i][j-1].state==pixel_type::wall?1:0;
            nums+=matrix[i][j+1].state==pixel_type::wall?1:0;
            if(nums==3)
                clist.push_back(cell({i,j}));
        }
    }

    while(beans>0 && clist.size()>0){
        int randind=qrand()%clist.size();
        cell u=clist.at(randind);
        matrix[u.i][u.j].state=pixel_type::film;
        beans--;
        clist.erase(clist.begin()+randind);
    }


}

void MazeWidget::fresh_magic()
{
    for(int i=1;i<M-1;i++){
        for(int j=1;j<N-2;j++){
            if(matrix[i][j].state==pixel_type::magic)
                matrix[i][j].state=pixel_type::pass;
        }
    }


    int beans=int(sqrt(M*N))/20;
    vector<cell> clist;

    for(int i=1;i<M-1;i++){
        for(int j=1;j<N-2;j++){
            int nums=0;
            nums+=matrix[i-1][j].state==pixel_type::wall?1:0;
            nums+=matrix[i+1][j].state==pixel_type::wall?1:0;
            nums+=matrix[i][j-1].state==pixel_type::wall?1:0;
            nums+=matrix[i][j+1].state==pixel_type::wall?1:0;
            if(nums==3)
                clist.push_back(cell({i,j}));
        }
    }

    while(beans>0 && clist.size()>0){
        int randind=qrand()%clist.size();
        cell u=clist.at(randind);
        matrix[u.i][u.j].state=pixel_type::magic;
        beans--;
        clist.erase(clist.begin()+randind);
    }
}


void MazeWidget::find_path_button_slot()
{



    if(magic==0)
    {
        QMessageBox::information(this,"Alert","No more magic available!",QMessageBox::Yes);
        return;
    }
    magic--;
    //使得迷宫矩阵的state为2的值变为1
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
        {
            if(matrix[i][j].state==pixel_type::colored ||
                    matrix[i][j].state==pixel_type::checked)
            {
                matrix[i][j].state=pixel_type::pass;
            }
        }
    this->find_path();

    this->setFocus(Qt::MouseFocusReason);
    update();
}

void MazeWidget::invert_button_slot()
{

    if(magic==0){
     QMessageBox::information(this,"Alert","No more films available!",QMessageBox::Yes);
     return;
    }

    films--;

    for(int i=1;i<M-1;i++)
        for(int j=1;j<N-1;j++){
            if(matrix[i][j].state==pixel_type::wall)
                matrix[i][j].state=pixel_type::pass;
            else if(matrix[i][j].state==pixel_type::film && matrix[i][j].state==pixel_type::magic)
                ;
            else
                matrix[i][j].state=pixel_type::wall;
        }
    matrix[X][Y].state=pixel_type::pass;
    matrix[M-2][N-2].state=pixel_type::pass;
    this->setFocus(Qt::MouseFocusReason);
    update();
    timer=new QTimer(this);
    if(timer==NULL){
        QMessageBox::information(this,"Alert","Timer failed!",QMessageBox::Yes);
        exit(-1);
    } else {
        timer->setInterval(5000);
        connect(this->timer,SIGNAL(timeout()), this,SLOT(invert_timeout_slot()));
        timer->start();
    }

}

void MazeWidget::invert_timeout_slot()
{

    timer->stop();
    for(int i=1;i<M-1;i++)
        for(int j=1;j<N-1;j++){
            if(matrix[i][j].state==pixel_type::wall)
                matrix[i][j].state=pixel_type::pass;
            else if(matrix[i][j].state==pixel_type::film && matrix[i][j].state==pixel_type::magic)
                ;
            else
                matrix[i][j].state=pixel_type::wall;
        }
    matrix[X][Y].state=pixel_type::pass;
    matrix[M-2][N-2].state=pixel_type::pass;
    this->setFocus(Qt::MouseFocusReason);
    update();

}















