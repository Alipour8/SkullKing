#include "playclient.h"
#include "ui_playclient.h"
#include<QThread>
#include <QPushButton>
#include "deckcard.h"

QPushButton **btnlist1=new QPushButton *[14];
bool ConfirmClient=false;
int HandTakenClient;
QString Starter;
QList<QString> HandClient;
QList<QString>::Iterator itClient;
int roundgame2=7;

PlayClient::PlayClient(QWidget *parent):
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


void play(){}

void PlayClient::on_pushButton_15_clicked()
{
socket->connectToHost(ui->lineEdit_3->text(),1234);
if(socket->waitForConnected())
    ui->label_6->setText("   Connected");
else
    ui->label_6->setText("   Error");

ui->pushButton_15->hide();
ui->lineEdit_3->hide();
ui->label_4->hide();
ui->label_6->hide();

}

void shareHand(QPushButton **btnlist,QComboBox *cmb,QStringList cardData){
    QStringList list;
    for(int i=0;i<=2*roundgame2;i++)
        list.push_back(QString::number(i));
    cmb->addItems(list);

    for(int i=1;i<=2*roundgame2;i++){
        Card temp(cardData[i*2].toInt(),cardData[i*2-1]);
        QString type=temp.getCardName();
        int value=temp.getCardNumber();
        HandClient.push_back(type);
        if(type=="PirateFlag" && value ==1)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(type=="PirateFlag" && value ==2)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(type=="PirateFlag" && value ==3)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(type=="PirateFlag" && value ==4)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(type=="PirateFlag" && value ==5)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(type=="PirateFlag" && value ==6)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(type=="PirateFlag" && value ==7)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(type=="PirateFlag" && value ==8)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(type=="Parrot" && value ==1)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(type=="Parrot" && value ==2)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(type=="Parrot" && value ==3)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(type=="Parrot" && value ==4)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(type=="Parrot" && value ==5)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(type=="Parrot" && value ==6)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(type=="Parrot" && value ==7)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(type=="Parrot" && value ==8)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(type=="Map" && value ==1)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(type=="Map" && value ==2)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(type=="Map" && value ==3)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(type=="Map" && value ==4)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(type=="Map" && value ==5)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(type=="Map" && value ==6)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(type=="Map" && value ==7)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(type=="Map" && value ==8)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(type=="Treasure" && value ==1)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(type=="Treasure" && value ==2)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(type=="Treasure" && value ==3)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(type=="Treasure" && value ==4)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(type=="Treasure" && value ==5)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(type=="Treasure" && value ==6)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(type=="Treasure" && value ==7)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(type=="Treasure" && value ==8)
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(type=="King")
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(type=="Queen")
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(type=="Pirate")
        btnlist1[i-1]->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");
    }
}

void PlayClient::readsocket(){
    btnlist1[0]=ui->btn1;
    btnlist1[1]=ui->btn2;
    btnlist1[2]=ui->btn3;
    btnlist1[3]=ui->btn4;
    btnlist1[4]=ui->btn5;
    btnlist1[5]=ui->btn6;
    btnlist1[6]=ui->btn7;
    btnlist1[7]=ui->btn8;
    btnlist1[8]=ui->btn9;
    btnlist1[9]=ui->btn10;
    btnlist1[10]=ui->btn11;
    btnlist1[11]=ui->btn12;
    btnlist1[12]=ui->btn13;
    btnlist1[13]=ui->btn14;
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream>>buffer;
    QStringList cardData=QString(buffer).split(" ");
    if(cardData[0]=="CardInHand"){
       shareHand(btnlist1,ui->comboBox,cardData);
       ui->pushButton->setEnabled(true);
       ui->comboBox->setEnabled(true);
       return;
    }
    if(cardData[0]=="Confirm"){
        ConfirmClient=true;
        return;
    }
    if(cardData[0]=="NotConfirm"){
        btnlist1[0]=ui->btn1;
        btnlist1[1]=ui->btn2;
        btnlist1[2]=ui->btn3;
        btnlist1[3]=ui->btn4;
        btnlist1[4]=ui->btn5;
        btnlist1[5]=ui->btn6;
        btnlist1[6]=ui->btn7;
        btnlist1[7]=ui->btn8;
        btnlist1[8]=ui->btn9;
        btnlist1[9]=ui->btn10;
        btnlist1[10]=ui->btn11;
        btnlist1[11]=ui->btn12;
        btnlist1[12]=ui->btn13;
        btnlist1[13]=ui->btn14;
        ui->comboBox->setDisabled(true);
        ui->pushButton->setDisabled(true);
        for(int i=0;i<14;i++)
            btnlist1[i]->setEnabled(true);
        return;
    }
    if(cardData[0]=="Play"){
        btnlist1[0]=ui->btn1;
        btnlist1[1]=ui->btn2;
        btnlist1[2]=ui->btn3;
        btnlist1[3]=ui->btn4;
        btnlist1[4]=ui->btn5;
        btnlist1[5]=ui->btn6;
        btnlist1[6]=ui->btn7;
        btnlist1[7]=ui->btn8;
        btnlist1[8]=ui->btn9;
        btnlist1[9]=ui->btn10;
        btnlist1[10]=ui->btn11;
        btnlist1[11]=ui->btn12;
        btnlist1[12]=ui->btn13;
        btnlist1[13]=ui->btn14;
        for(int i=0;i<14;i++)
            btnlist1[i]->setEnabled(true);
 int value=cardData[2].toInt();
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(1))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(2) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(3))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(4))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(7))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2] == QString::number(8))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(1))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(2))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(3))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(4))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(7))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2] == QString::number(8))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(1))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(2))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(3))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(4))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(7))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(cardData[1]=="Map" && cardData[2] == QString::number(8))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(1))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(2))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(3))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(4))
       ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(7))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2] == QString::number(8))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(cardData[1]=="King")
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(cardData[1]=="Queen")
       ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(cardData[1]=="Pirate")
       ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");

        return;
    }
    //ui->label_6->setText(buffer);
}
/*void PlayClient::on_pushButton_18_clicked()
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
}*/


void PlayClient::on_pushButton_clicked()
{
    if(ConfirmClient){
    btnlist1[0]=ui->btn1;
    btnlist1[1]=ui->btn2;
    btnlist1[2]=ui->btn3;
    btnlist1[3]=ui->btn4;
    btnlist1[4]=ui->btn5;
    btnlist1[5]=ui->btn6;
    btnlist1[6]=ui->btn7;
    btnlist1[7]=ui->btn8;
    btnlist1[8]=ui->btn9;
    btnlist1[9]=ui->btn10;
    btnlist1[10]=ui->btn11;
    btnlist1[11]=ui->btn12;
    btnlist1[12]=ui->btn13;
    btnlist1[13]=ui->btn14;
    ui->comboBox->setDisabled(true);
    ui->pushButton->setDisabled(true);
    for(int i=0;i<14;i++)
        btnlist1[i]->setEnabled(true);
    QString temp="NotConfirm";
    if(socket){
        if(socket->isOpen()){
            QDataStream socketstream(socket);
            socketstream.setVersion(QDataStream::Qt_5_15);
            QByteArray byteArray = temp.toUtf8();
            socketstream<<byteArray;
            socket->waitForBytesWritten(6000);

        }
    }
    QThread::sleep(1);

    if(roundgame2==1){
        QString server="server";
        if(socket){
            if(socket->isOpen()){
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_5_15);
                QByteArray byteArray = server.toUtf8();
                socketstream<<byteArray;
                socket->waitForBytesWritten(6000);

            }
        }
        for(int i=0;i<14;i++)
            btnlist1[i]->setDisabled(true);
    }
}
    else{
        QString tmp="Confirm";
        if(socket){
            if(socket->isOpen()){
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_5_15);
                QByteArray byteArray = tmp.toUtf8();
                socketstream<<byteArray;
                socket->waitForBytesWritten(6000);

            }
        }
    }
    HandTakenClient=ui->comboBox->itemText(ui->comboBox->currentIndex()).toInt();
}

