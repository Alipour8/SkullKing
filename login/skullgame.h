//it is play server
#ifndef SKULLGAME_H
#define SKULLGAME_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class SkullGame; }
QT_END_NAMESPACE

class SkullGame : public QMainWindow
{
    Q_OBJECT

public:
    SkullGame(QWidget *parent = nullptr);
    ~SkullGame();
public slots:
    void connection();
    void readSocket();

private slots:
    void on_pushButton_15_clicked();

private:
    Ui::SkullGame *ui;
    QTcpServer *server;
    QTcpSocket *socket;
};
#endif // SKULLGAME_H
