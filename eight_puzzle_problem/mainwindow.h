#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <vector>
#include "common_animation.h"
#include <QAbstractAnimation>
#include "numblock.h"

using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void creatBlock();
    void init_button();
    NumBlock* find_p(int);
    void move_button(vector<vector<int> >  m);
    void change_button(vector<vector<int> >);
    void change_button1(vector<vector<int> >);
    void init_button_location();
    vector<vector<int> > mm;
    vector<vector<int> > location;
    int INIT[3][3];
    int TEMP[3][3];
    int change_location[3][3][2];
    void init_INIT();
    int Solvable[81][3][3];

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    auto findBut(QPoint point);
    void exchange(int num1,int num2);
    QPoint curpoint;
    QPoint nextpoint;
    int curBut;
    int pointx,pointy;
private slots:
    void onCurrentAnimationChanged(QAbstractAnimation *current);
    void onCurrentAnimationChanged1(QAbstractAnimation *current);
   /* void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();
*/

    void on_pushButton_11_clicked();
    void on_pushButton_init_clicked();

private:
    Ui::MainWindow *ui;
    vector<NumBlock*> numBlock;
};

#endif // MAINWINDOW_H
