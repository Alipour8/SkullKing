#ifndef PLAYCLIENT_H
#define PLAYCLIENT_H

#include <QWidget>
#include<QMainWindow>
#include<QHostAddress>
#include<QTcpSocket>

namespace Ui {
class PlayClient;
}

class PlayClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayClient(QWidget *parent = nullptr);
    ~PlayClient();
QTcpSocket*socket;
private slots:
    void readsocket();
    void on_pushButton_15_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_clicked();

private:
    Ui::PlayClient *ui;

};

#endif // PLAYCLIENT_H
