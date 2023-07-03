//it is play server
#ifndef SKULLGAME_H
#define SKULLGAME_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>
#include"user.h"
#include"maindatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SkullGame; }
QT_END_NAMESPACE

class SkullGame : public QMainWindow
{
    Q_OBJECT

public:
   explicit SkullGame(QWidget *parent = nullptr);
    SkullGame(user me,QWidget *parent = nullptr);
    ~SkullGame();
public slots:
    void connection();
        void readSocket();

private slots:
    void on_pushButton_clicked();

       void on_pushButton_2_clicked();

       void on_btn1_clicked();

       void on_btn2_clicked();

       void on_btn5_clicked();

       void on_btn3_clicked();

       void on_btn4_clicked();

       void on_btn6_clicked();

       void on_btn7_clicked();

       void on_btn8_clicked();

       void on_btn9_clicked();

       void on_btn10_clicked();

       void on_btn11_clicked();

       void on_btn12_clicked();

       void on_btn13_clicked();

       void on_btn14_clicked();

       void on_pushButton_3_clicked();

       void on_pushButton_17_clicked();


private:
    Ui::SkullGame *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    user howAmI;
    QString name;
    QTimer*mytimer;
};
#endif // SKULLGAME_H
