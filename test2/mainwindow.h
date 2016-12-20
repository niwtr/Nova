#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "common_animation.h"
#include <QAbstractAnimation>
using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init_button(int[3][3]);
    auto find_p(int);
    void move_button(vector<vector<int> >  m);
    void change_button(vector<vector<int> >);
    void change_button1(vector<vector<int> >);
    vector<vector<int> > mm;
    vector<vector<int> > location;
  //  auto generic_move_in(auto any, auto margin, auto duration, int dir, auto group);
   // auto generic_move_in1(auto any, auto margin, auto duration, int dir, auto group1);

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

};

#endif // MAINWINDOW_H
