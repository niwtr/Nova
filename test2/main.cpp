#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include <QRect>
#include <QFont>
#include <QPushButton>
#include "PushBtn.h"
#include <QLineEdit>

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    QApplication a(argc, argv);
        QDialog *mainWindow = new QDialog;


        PushBtn *btn1 = new PushBtn(mainWindow);
        btn1->setText("1");
        btn1->setGeometry(QRect(30, 30, 40, 40));

        PushBtn *btn2 = new PushBtn(mainWindow);
        btn2->setText("2");
        btn2->setGeometry(QRect(30, 70, 40, 40));

        PushBtn *btn3 = new PushBtn(mainWindow);
        btn3->setText("3");
        btn3->setGeometry(QRect(30, 110, 40, 40));

        PushBtn *btn4 = new PushBtn(mainWindow);
        btn4->setText("4");
        btn4->setGeometry(QRect(70, 30, 40, 40));

        PushBtn *btn5 = new PushBtn(mainWindow);
        btn5->setText("5");
        btn5->setGeometry(QRect(70, 70, 40, 40));

        PushBtn *btn6 = new PushBtn(mainWindow);
        btn6->setText("6");
        btn6->setGeometry(QRect(70, 110, 40, 40));

        PushBtn *btn7 = new PushBtn(mainWindow);
        btn7->setText("7");
        btn7->setGeometry(QRect(110, 30, 40, 40));

        PushBtn *btn8 = new PushBtn(mainWindow);
        btn8->setText("8");
        btn8->setGeometry(QRect(110, 70, 40, 40));

        PushBtn *btn9 = new PushBtn(mainWindow);
        btn9->setText("  ");
        btn9->setGeometry(QRect(110, 110, 40, 40));



        mainWindow->resize(180, 180);
        mainWindow->setWindowTitle("Qt Test");
        mainWindow->show();




        return a.exec();
}*/
//
//  main.cpp
//  Nova-Kern
//
//  Created by 牛天睿 on 16/12/5.
//  Copyright (c) 2016 Anzalized. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
//#include "astar.hpp"
#include "path_pacman.h"
//#include "Path8.h"
using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;

using namespace nova_kernel;



/******************************************/




int main(int argc,char * argv[]) {

    /* digit 8 */

    QApplication a(argc, argv);
    MainWindow w;

    int init[3][3] = {{1, 2, 3}, {-1, 8, 4}, {7, 6, 5}};
    //int init[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            //init[i][j]=w.INIT[i][j];
            w.INIT[i][j]=init[i][j];
        }
    }
    w.init_button();
    w.init_INIT();
    //int init[3][3]={{2,3,8},{1,6,4},{7,-1,5}};
    /*Path8 p = Path8(init);
    a_star<Path8> astar_digit8;
    astar_digit8.init_path(p);
    astar_digit8.search();
    list<Path8> lp8;
    //int temp[3][3];
    //temp=astar_digit8.get_all_paths(lp8);//get all the paths to go.
    astar_digit8.get_all_paths(lp8);
    vector<vector<int> > draw;
    draw=astar_digit8.CHANGES;
    //w.init_button(init);
    w.init_button();
    w.location=astar_digit8.calculate_location(astar_digit8.CHANGES,init);
    w.mm=astar_digit8.CHANGES;
    w.move_button(astar_digit8.CHANGES);

    for(auto _p : lp8){
        _p.output();
    }
    */
    w.show();
    //w.init_INIT();




    return a.exec();
    return 0;
}
