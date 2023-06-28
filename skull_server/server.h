#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include<QMainWindow>
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include<QTime>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class server; }
QT_END_NAMESPACE

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

private:
    Ui::server *ui;
        QTcpServer *Server;
        QTcpSocket *socket;
        QTime time;

    public slots:
        void readyRead();
        void newConnectionSlot();
    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
};
#endif // SERVER_H
