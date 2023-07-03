#ifndef PLAYCLIENT_H
#define PLAYCLIENT_H

#include <QWidget>
#include<QMainWindow>
#include<QHostAddress>
#include<QTcpSocket>
#include"user.h"
#include"maindatabase.h"

namespace Ui {
class PlayClient;
}

class PlayClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayClient(QWidget *parent = nullptr);
    PlayClient(user me,QWidget *parent = nullptr);
    ~PlayClient();
QTcpSocket*socket;
private slots:
void readsocket();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

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
    Ui::PlayClient *ui;
    user howAmI;
    QString name;
    QTimer*mytimer;
};

#endif // PLAYCLIENT_H
