#include "playclient.h"
#include "ui_playclient.h"

PlayClient::PlayClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayClient)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&PlayClient::readsocket);
}

PlayClient::~PlayClient()
{
    delete ui;
}


void PlayClient::on_pushButton_15_clicked()
{
socket->connectToHost(ui->lineEdit_3->text(),1234);
if(socket->waitForConnected())
    ui->label_6->setText("   Connected");
else
    ui->label_6->setText("   Error");
}

void PlayClient::readsocket(){
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream>>buffer;
    ui->label_6->setText(buffer);
}
void PlayClient::on_pushButton_18_clicked()
{
    if(socket){
        if(socket->isOpen()){
            QString temp="Hello client";
            QDataStream socketstream(socket);
            socketstream.setVersion(QDataStream::Qt_5_15);

            QByteArray byteArray=temp.toUtf8();
            socketstream<<byteArray;
        }
}
}

