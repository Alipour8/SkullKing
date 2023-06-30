#include "skullgame.h"
#include "ui_skullgame.h"
#include<QTcpServer>
#include<QHostInfo>
#include<QList>
#include<QByteArray>
#include<QDataStream>
#include<QPixmap>
SkullGame::SkullGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SkullGame)
{
    ui->setupUi(this);
    QString localhostname=QHostInfo::localHostName();
    QString localhostIP;
    QList<QHostAddress>hostlist=QHostInfo::fromName(localhostname).addresses();
    foreach(const QHostAddress& address, hostlist){
        if(address.protocol()==QAbstractSocket::IPv4Protocol && address.isLoopback()==false){
            localhostIP=address.toString();
        }
    }
    QString ip="  "+localhostIP;
    ui->textEdit_2->setText(ip);
    server = new QTcpServer();
    if(server->listen(QHostAddress::Any,1234)){
        connect(server,&QTcpServer::newConnection,this,&SkullGame::connection);
        ui->textEdit_3->setText("  Wating...");
    }
    else{
       ui->textEdit_3->setText("  Error");
    }

}

SkullGame::~SkullGame()
{
    delete ui;
}


void SkullGame::connection(){
    while(server->hasPendingConnections()){
        socket=server->nextPendingConnection();
        connect(socket,&QTcpSocket::readyRead,this,&SkullGame::readSocket);
        ui->textEdit_3->setText("Connected");
        break;
    }
}
void SkullGame::readSocket(){
    QTcpSocket* socket=reinterpret_cast<QTcpSocket*>(sender());
    QByteArray Buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream>>Buffer;
    ui->textEdit_3->setText(Buffer);

}
void SkullGame::on_pushButton_15_clicked()
{
if(socket){
    if(socket->isOpen()){
        QString temp="Hello server";
        QDataStream socketstream(socket);
        socketstream.setVersion(QDataStream::Qt_5_15);

        QByteArray byteArray=temp.toUtf8();
        socketstream<<byteArray;
        //
        QPixmap pixmap("D:/SkullKing_Pat-Mat_19/login/Parrot1.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton_14->setIcon(ButtonIcon);
        ui->pushButton_14->setIconSize(QSize(130,330));
    }
}
}

