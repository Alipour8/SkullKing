#include "playclient.h"
#include "ui_playclient.h"
#include<QThread>
#include <QPushButton>
#include "deckcard.h"
#include "groundgame.h"
QPushButton **btnlist1=new QPushButton *[14];
bool ConfirmClient=false;
bool serverplayed=false;
int scoreClient=0;
int HandTakenClient=0;
int HandCanTakenClient;
QString WhoStart;
GroundGame groundgame;
QString Starter;
QList<QString> HandClient;
QList<QString>::Iterator itClient;
int roundgame2=1;

PlayClient::PlayClient(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PlayClient)
{
    ui->setupUi(this);
    setWindowTitle("Client");
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
int i=1;
    for(;i<=2*roundgame2;i++){
        Card temp(cardData[i*2].toInt(),cardData[i*2-1]);
        QString type=temp.getCardName();
        int value=temp.getCardNumber();
        HandClient.push_back(type);
        if(type=="PirateFlag" && value ==1)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(type=="PirateFlag" && value ==2)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(type=="PirateFlag" && value ==3)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(type=="PirateFlag" && value ==4)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(type=="PirateFlag" && value ==5)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(type=="PirateFlag" && value ==6)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(type=="PirateFlag" && value ==7)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(type=="PirateFlag" && value ==8)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(type=="Parrot" && value ==1)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(type=="Parrot" && value ==2)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(type=="Parrot" && value ==3)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(type=="Parrot" && value ==4)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(type=="Parrot" && value ==5)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(type=="Parrot" && value ==6)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(type=="Parrot" && value ==7)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(type=="Parrot" && value ==8)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(type=="Map" && value ==1)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(type=="Map" && value ==2)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(type=="Map" && value ==3)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(type=="Map" && value ==4)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(type=="Map" && value ==5)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(type=="Map" && value ==6)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(type=="Map" && value ==7)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(type=="Map" && value ==8)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(type=="Treasure" && value ==1)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(type=="Treasure" && value ==2)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(type=="Treasure" && value ==3)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(type=="Treasure" && value ==4)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(type=="Treasure" && value ==5)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(type=="Treasure" && value ==6)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(type=="Treasure" && value ==7)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(type=="Treasure" && value ==8)
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(type=="King")
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(type=="Queen")
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(type=="Pirate")
        btnlist[i-1]->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");
    }
    for(; i<=14;i++)
        btnlist[i-1]->hide();
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
        Card temp(cardData[2].toInt(),cardData[1]);
        temp.setOwnerCard("server");
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
       /* if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(1))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(2) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(3))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(4) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(6) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(7))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(cardData[1]=="PirateFlag" && cardData[2]==QString::number(8))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(1) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(2) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(3) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(4) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(7) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(cardData[1]=="Parrot" && cardData[2]==QString::number(8) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(1) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(2) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(3) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(4))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(7) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(cardData[1]=="Map" && cardData[2]==QString::number(8) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(1) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(2))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(3) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(4) )
       ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(5))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(6))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(7) )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(cardData[1]=="Treasure" && cardData[2]==QString::number(8))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(cardData[1]=="King" &&  cardData[2]==QString::number(0))
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(cardData[1]=="Queen" && cardData[2]==QString::number(0))
       ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(cardData[1]=="Pirate" && cardData[2]==QString::number(0))
       ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");*/
 if(cardData[1]=="PirateFlag 1")
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
         if(cardData[1]=="PirateFlag 2"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
         if(cardData[1]=="PirateFlag 3" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
         if(cardData[1]=="PirateFlag 4" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
         if(cardData[1]=="PirateFlag 5" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
         if(cardData[1]=="PirateFlag 6"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
         if(cardData[1]=="PirateFlag 7" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
         if(cardData[1]=="PirateFlag 8" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
         if(cardData[1]=="Parrot 1"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
         if(cardData[1]=="Parrot 2"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
         if(cardData[1]=="Parrot 3"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
         if(cardData[1]=="Parrot 4"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
         if(cardData[1]=="Parrot 5" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
         if(cardData[1]=="Parrot 6" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
         if(cardData[1]=="Parrot 7"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
         if(cardData[1]=="Parrot 8"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
         if(cardData[1]=="Map 1" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
         if(cardData[1]=="Map 2"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
         if(cardData[1]=="Map 3"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
         if(cardData[1]=="Map 4" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
         if(cardData[1]=="Map 5" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
         if(cardData[1]=="Map 6" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
         if(cardData[1]=="Map 7" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
         if(cardData[1]=="Map 8"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
         if(cardData[1]=="Treasure 1"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
         if(cardData[1]=="Treasure 2" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
         if(cardData[1]=="Treasure 3"  )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
         if(cardData[1]=="Treasure 4"  )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
         if(cardData[1]=="Treasure 5" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
         if(cardData[1]=="Treasure 6" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
         if(cardData[1]=="Treasure 7" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
         if(cardData[1]=="Treasure 8" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
         if(cardData[1]=="King 0" )
         ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
         if(cardData[1]=="Queen 0" )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
         if(cardData[1]=="Pirate 0" )
        ui->RivalClient->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");
    serverplayed=true;
    groundgame.Ground.push_back(temp);
        return;
    }
    if(cardData[0]=="erase"){
        ui->RivalClient->setStyleSheet("border-radius:10px;\nborder-image: url(:/new/prefix1/CardFrame.jpg);");
        ui->MyCard->setStyleSheet("border-radius:10px;\nborder-image: url(:/new/prefix1/CardFrame.jpg);");
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
    ui->comboBox->setDisabled(true);
    ui->pushButton_15->setDisabled(true);
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
    HandCanTakenClient=ui->comboBox->itemText(ui->comboBox->currentIndex()).toInt();
}


void PlayClient::on_btn1_clicked()
{
    if(serverplayed){
        itClient=HandClient.begin();
        QString cardData="Last "+*itClient+" ";
        if(socket){
            if(socket->isOpen()){
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_5_15);
                QByteArray byteArray = cardData.toUtf8();
                socketstream<<byteArray;
                socket->waitForBytesWritten(6000);

            }
        }
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
            btnlist1[i]->setDisabled(true);
        btnlist1[0]->hide();
        if(*itClient=="PirateFlag 1")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(*itClient=="PirateFlag 2")
       ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(*itClient=="PirateFlag 3")
       ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(*itClient=="PirateFlag 4")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(*itClient=="PirateFlag 5")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(*itClient=="PirateFlag 6")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(*itClient=="PirateFlag 7")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(*itClient=="PirateFlag 8")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(*itClient=="Parrot 1")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(*itClient=="Parrot 2")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(*itClient=="Parrot 3")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(*itClient=="Parrot 4")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(*itClient=="Parrot 5")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(*itClient=="Parrot 6")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(*itClient=="Parrot 7")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(*itClient=="Parrot 8")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(*itClient=="Map 1")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(*itClient=="Map 2")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(*itClient=="Map 3")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(*itClient=="Map 4")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(*itClient=="Map 5")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(*itClient=="Map 6")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(*itClient=="Map 7")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(*itClient=="Map 8")
         ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(*itClient=="Treasure 1")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(*itClient=="Treasure 2")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(*itClient=="Treasure 3")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(*itClient=="Treasure 4")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(*itClient=="Treasure 5")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(*itClient=="Treasure 6")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(*itClient=="Treasure 7")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(*itClient=="Treasure 8")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(*itClient=="King 0")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(*itClient=="Queen 0")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(*itClient=="Pirate 0")
        ui->MyCard->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");
         QStringList temp=QString(*itClient).split(" ");
        int x= temp[1].toInt();
        QString y= temp[0];
        Card tmp(x,y);
        tmp.setOwnerCard("client");
        groundgame.Ground.push_back(tmp);
       pair<QString,int> winner=groundgame.GroundWinner();
       QString order=winner.first+"win"+" "+QString::number(winner.second);
       if(socket){
           if(socket->isOpen()){
               QDataStream socketstream(socket);
               socketstream.setVersion(QDataStream::Qt_5_15);
               QByteArray byteArray = order.toUtf8();
               socketstream<<byteArray;
               socket->waitForBytesWritten(6000);

           }
       }
       if(winner.first=="client"){
           scoreClient+=winner.second;
           HandTakenClient++;
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
       }

       list<Card>::iterator itground;
       for(;!groundgame.Ground.empty();){
           itground=groundgame.Ground.begin();
           groundgame.Ground.erase(itground);
       }
    }
}


