#include "mainwindow.h"
#include <QApplication>
#include <QDialog>
#include <QRect>
#include <QFont>
#include <QPushButton>
#include "PushBtn.h"
#include <QLineEdit>

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include "path_pacman.h"

using std::vector;
using std::merge;
using std::list;
using std::map;
using std::cout;
using std::endl;

using namespace nova_kernel;


int main(int argc,char * argv[]) {

    /* digit 8 */

    QApplication a(argc, argv);
    MainWindow w;

    int init[3][3] = {{1, 2, 3}, {-1, 8, 4}, {7, 6, 5}};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            w.INIT[i][j]=init[i][j];
        }
    }
    w.init_button();
    w.init_INIT();
    w.show();

    return a.exec();
    return 0;
}
