#ifndef PUSHBTN_H
#define PUSHBTN_H
#include <QPushButton>
#include <QMessageBox>

class PushBtn : public QPushButton
{
    Q_OBJECT

public:
    PushBtn(QWidget *parent = NULL):QPushButton(parent)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
    }

private slots:
    void OnClicked()
    {
        QString str;
        str = "You press " + this->text();
        QMessageBox::information(this, tr("Information"), str);
    }

};
#endif // PUSHBTN_H
