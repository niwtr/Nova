#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H
#include "astar.hpp"
#include "path_maze.h"
#include <QWidget>
#include <iostream>
#include <stack>
#include <QTime>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QPixmap>
#include <QTimer>
using namespace std;




class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    MazeWidget(QWidget *parent = 0);
    ~MazeWidget();
    void paintEvent(QPaintEvent *);
    bool oddp();
    void create_maze();
    void keyPressEvent(QKeyEvent *);
    void find_path();
private:


    int magic;
    int films;
    nova_kernel::a_star<path_maze> Agent;
    Maze **matrix;
    stack<Maze> *MazeStack;//a stack to storage the maze node
    vector<Maze> *FinalPath;//a vector to storage the maze path.
    int M;//rows
    int N;//cols
    bool first;
    bool cheat_mode;//is in cheat mode?
    QLineEdit *Xline;
    QLineEdit *Yline;
    QPushButton *create_maze_button;
    QPushButton *cheat_mode_button;
    QPushButton *cancel_button;
    QPushButton *find_short_path_button;
    QPushButton *invert_button;
    QLabel * film_rest;
    QLabel * magic_rest;
    QLabel * stepn;
    QLabel * zerostepn;
    QTimer * timer;

    int X;
    int Y;

    int steps;

    int zerosteps;

    constexpr static unsigned pixel_size=10;


    void fresh_films();
    void fresh_magic();

private slots:
    void create_maze_button_slot();
    void cheat_mode_button_slot();
    void cancel_button_slot();
    void find_path_button_slot();
    void invert_button_slot();
    void invert_timeout_slot();
};

#endif // MAZEWIDGET_H
