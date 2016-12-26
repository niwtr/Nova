#include "maze_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MazeWidget w;
    //w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    a.setWindowIcon(QIcon("s.ico"));
    return a.exec();
}
