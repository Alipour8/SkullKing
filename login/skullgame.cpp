#include "skullgame.h"
#include "ui_skullgame.h"
#include<QTcpServer>
#include<QHostInfo>
#include<QList>
#include<QByteArray>
#include<QDataStream>
#include<QPixmap>
#include<QThread>
#include "deckcard.h"
using namespace std;
bool Confirm2=false;
bool clientPlayed=false;

int HandCanTakeServer;
int HandTekenServer=0;
int ScoreServer=0;
int counter=0;
int j=0;
DeckCard Deck;
int roundgame=1;
QList<QString> HandServer;
QList<QString>::Iterator itServer;
QPushButton **btnlist=new QPushButton *[14];

SkullGame::SkullGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SkullGame)
{
    ui->setupUi(this);
    setWindowTitle("Server");
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
    QStringList cardData=QString(Buffer).split(" ");
    if(cardData[0]=="server"){
        btnlist[0]=ui->btn1;
        btnlist[1]=ui->btn2;
        btnlist[2]=ui->btn3;
        btnlist[3]=ui->btn4;
        btnlist[4]=ui->btn5;
        btnlist[5]=ui->btn6;
        btnlist[6]=ui->btn7;
        btnlist[7]=ui->btn8;
        btnlist[8]=ui->btn9;
        btnlist[9]=ui->btn10;
        btnlist[10]=ui->btn11;
        btnlist[11]=ui->btn12;
        btnlist[12]=ui->btn13;
        btnlist[13]=ui->btn14;
        for(int i=0;i<14;i++)
            btnlist[i]->setEnabled(true);
    }
    if(cardData[0]=="Confirm")
        Confirm2=true;
    if(cardData[0]=="Last"){
        if(cardData[1]=="PirateFlag 1")
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(cardData[1]=="PirateFlag 2" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(cardData[1]=="PirateFlag 3" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(cardData[1]=="PirateFlag 4" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(cardData[1]=="PirateFlag 5" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(cardData[1]=="PirateFlag 6" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(cardData[1]=="PirateFlag 7")
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(cardData[1]=="PirateFlag 8")
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(cardData[1]=="Parrot 1" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(cardData[1]=="Parrot 2" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(cardData[1]=="Parrot 3" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(cardData[1]=="Parrot 4" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(cardData[1]=="Parrot 5" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(cardData[1]=="Parrot 6" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(cardData[1]=="Parrot 7" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(cardData[1]=="Parrot 8" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(cardData[1]=="Map 1" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(cardData[1]=="Map 2" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(cardData[1]=="Map 3" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(cardData[1]=="Map 4" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(cardData[1]=="Map 5" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(cardData[1]=="Map 6")
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(cardData[1]=="Map 7" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(cardData[1]=="Map 8" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(cardData[1]=="Treasure 1" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(cardData[1]=="Treasure 2" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(cardData[1]=="Treasure 3" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(cardData[1]=="Treasure 4" )
       ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(cardData[1]=="Treasure 5" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(cardData[1]=="Treasure 6" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(cardData[1]=="Treasure 7" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(cardData[1]=="Treasure 8" )
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(cardData[1]=="King")
        ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(cardData[1]=="Queen")
       ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(cardData[1]=="Pirate")
       ui->RivalCard->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");

    }

    if(cardData[0]=="serverwin"){
        HandTekenServer++;
        ScoreServer+=cardData[1].toInt();
        ui->lblhandtaken->setText(QString::number(HandTekenServer));
        ui->lblscore->setText(QString::number(ScoreServer));
        btnlist[0]=ui->btn1;
        btnlist[1]=ui->btn2;
        btnlist[2]=ui->btn3;
        btnlist[3]=ui->btn4;
        btnlist[4]=ui->btn5;
        btnlist[5]=ui->btn6;
        btnlist[6]=ui->btn7;
        btnlist[7]=ui->btn8;
        btnlist[8]=ui->btn9;
        btnlist[9]=ui->btn10;
        btnlist[10]=ui->btn11;
        btnlist[11]=ui->btn12;
        btnlist[12]=ui->btn13;
        btnlist[13]=ui->btn14;
        for(int i=0;i<14;i++)
            btnlist[i]->setEnabled(true);
    }
    if(cardData[0]=="clientwin"){
        ui->lblhandtaken->setText(QString::number(HandTekenServer));
        ui->lblscore->setText(QString::number(ScoreServer));
    }

   // ui->textEdit_3->setText(Buffer);

}

void sendmassageserver(QString str,QTcpSocket*socket){
    if(socket){
        if(socket->isOpen()){
            QDataStream socketstream(socket);
            socketstream.setVersion(QDataStream::Qt_5_15);
            QByteArray byteArray = str.toUtf8();
            socketstream<<byteArray;
            socket->waitForBytesWritten(6000);

        }
    }
}

void SkullGame::on_pushButton_15_clicked()
{
    if(j+1==2*roundgame){
        if(counter)
            roundgame++;
    counter++;
    j=0;
    ui->pushButton->setEnabled(true);
    ui->comboBox->setEnabled(true);
    QStringList num;
    for(int i=0;i<=2*roundgame;i++)
        num.push_back(QString::number(i));
    ui->comboBox->addItems(num);

    btnlist[0]=ui->btn1;
    btnlist[1]=ui->btn2;
    btnlist[2]=ui->btn3;
    btnlist[3]=ui->btn4;
    btnlist[4]=ui->btn5;
    btnlist[5]=ui->btn6;
    btnlist[6]=ui->btn7;
    btnlist[7]=ui->btn8;
    btnlist[8]=ui->btn9;
    btnlist[9]=ui->btn10;
    btnlist[10]=ui->btn11;
    btnlist[11]=ui->btn12;
    btnlist[12]=ui->btn13;
    btnlist[13]=ui->btn14;

    if(socket->isOpen()){
        ui->pushButton_15->setDisabled(true);
        int i=0;
        for(;i<2*roundgame;i++){
                    Card tmp=Deck.card_list.front();
                    Deck.card_list.erase(Deck.card_list.begin());
                    QString type=tmp.getCardName();
                    int value=tmp.getCardNumber();
                    HandServer.push_back(type);

                    if(type=="PirateFlag" && value ==1)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
                    if(type=="PirateFlag" && value ==2)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
                    if(type=="PirateFlag" && value ==3)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
                    if(type=="PirateFlag" && value ==4)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
                    if(type=="PirateFlag" && value ==5)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
                    if(type=="PirateFlag" && value ==6)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
                    if(type=="PirateFlag" && value ==7)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
                    if(type=="PirateFlag" && value ==8)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
                    if(type=="Parrot" && value ==1)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
                    if(type=="Parrot" && value ==2)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
                    if(type=="Parrot" && value ==3)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
                    if(type=="Parrot" && value ==4)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
                    if(type=="Parrot" && value ==5)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
                    if(type=="Parrot" && value ==6)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
                    if(type=="Parrot" && value ==7)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
                    if(type=="Parrot" && value ==8)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
                    if(type=="Map" && value ==1)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
                    if(type=="Map" && value ==2)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
                    if(type=="Map" && value ==3)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
                    if(type=="Map" && value ==4)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
                    if(type=="Map" && value ==5)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
                    if(type=="Map" && value ==6)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
                    if(type=="Map" && value ==7)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
                    if(type=="Map" && value ==8)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
                    if(type=="Treasure" && value ==1)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
                    if(type=="Treasure" && value ==2)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
                    if(type=="Treasure" && value ==3)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
                    if(type=="Treasure" && value ==4)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
                    if(type=="Treasure" && value ==5)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
                    if(type=="Treasure" && value ==6)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
                    if(type=="Treasure" && value ==7)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
                    if(type=="Treasure" && value ==8)
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
                    if(type=="King")
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
                    if(type=="Queen")
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
                    if(type=="Pirate")
                    btnlist[i]->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");

                }

        for(;i<14;i++)
            btnlist[i]->hide();

        QString CardInHand="CardInHand ";
        for(int i=0;i<2*roundgame;i++){
            Card temp=Deck.card_list.front();
            Deck.card_list.erase(Deck.card_list.begin());
            CardInHand+=temp.getCardName()+" ";
            int val=temp.getCardNumber();
            CardInHand+=QString::number(val)+" ";

}
        if(socket){

            if(socket->isOpen()){
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_5_15);
                QByteArray byteArray = CardInHand.toUtf8();
                socketstream<<byteArray;
                socket->waitForBytesWritten(6000);

            }
        }
       // QString temp="Hello server";
        //QDataStream socketstream(socket);
        //socketstream.setVersion(QDataStream::Qt_5_15);

        //QByteArray byteArray=temp.toUtf8();
       // socketstream<<byteArray;
        //
}
    }
    else{
    QString tmp="erase";
    if(socket){

        if(socket->isOpen()){
            QDataStream socketstream(socket);
            socketstream.setVersion(QDataStream::Qt_5_15);
            QByteArray byteArray = tmp.toUtf8();
            socketstream<<byteArray;
            socket->waitForBytesWritten(6000);

        }
    }
    ui->RivalCard->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156,0,0);");
    ui->myCard->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156,0,0);");
    }
    }


void SkullGame::on_pushButton_clicked()
{
    ui->comboBox->setDisabled(true);
    ui->pushButton->setDisabled(true);
    if(Confirm2){
        btnlist[0]=ui->btn1;
        btnlist[1]=ui->btn2;
        btnlist[2]=ui->btn3;
        btnlist[3]=ui->btn4;
        btnlist[4]=ui->btn5;
        btnlist[5]=ui->btn6;
        btnlist[6]=ui->btn7;
        btnlist[7]=ui->btn8;
        btnlist[8]=ui->btn9;
        btnlist[9]=ui->btn10;
        btnlist[10]=ui->btn11;
        btnlist[11]=ui->btn12;
        btnlist[12]=ui->btn13;
        btnlist[13]=ui->btn14;
        ui->comboBox->setDisabled(true);
        ui->pushButton->setDisabled(true);
        for(int i=0;i<14;i++)
            btnlist[i]->setEnabled(true);
        QString tmp="NotConfirm";
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
    HandCanTakeServer=ui->comboBox->itemText(ui->comboBox->currentIndex()).toInt();

}


void SkullGame::on_btn1_clicked()
{
    if(!clientPlayed){
        itServer=HandServer.begin();

        QString cardData="Play "+*itServer+" ";
        if(socket){

            if(socket->isOpen()){
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_5_15);
                QByteArray byteArray = cardData.toUtf8();
                socketstream<<byteArray;
                socket->waitForBytesWritten(6000);

            }
        }
        btnlist[0]=ui->btn1;
        btnlist[1]=ui->btn2;
        btnlist[2]=ui->btn3;
        btnlist[3]=ui->btn4;
        btnlist[4]=ui->btn5;
        btnlist[5]=ui->btn6;
        btnlist[6]=ui->btn7;
        btnlist[7]=ui->btn8;
        btnlist[8]=ui->btn9;
        btnlist[9]=ui->btn10;
        btnlist[10]=ui->btn11;
        btnlist[11]=ui->btn12;
        btnlist[12]=ui->btn13;
        btnlist[13]=ui->btn14;
        for(int i=0;i<14;i++)
           btnlist[i]->setDisabled(true);

        btnlist[0]->hide();
        if(*itServer=="PirateFlag 1")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(*itServer=="PirateFlag 2")
       ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(*itServer=="PirateFlag 3")
       ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(*itServer=="PirateFlag 4")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(*itServer=="PirateFlag 5")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(*itServer=="PirateFlag 6")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(*itServer=="PirateFlag 7")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(*itServer=="PirateFlag 8")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(*itServer=="Parrot 1")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(*itServer=="Parrot 2")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(*itServer=="Parrot 3")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(*itServer=="Parrot 4")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(*itServer=="Parrot 5")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(*itServer=="Parrot 6")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(*itServer=="Parrot 7")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(*itServer=="Parrot 8")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(*itServer=="Map 1")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(*itServer=="Map 2")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(*itServer=="Map 3")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(*itServer=="Map 4")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(*itServer=="Map 5")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(*itServer=="Map 6")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(*itServer=="Map 7")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(*itServer=="Map 8")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(*itServer=="Treasure 1")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(*itServer=="Treasure 2")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(*itServer=="Treasure 3")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(*itServer=="Treasure 4")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(*itServer=="Treasure 5")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(*itServer=="Treasure 6")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(*itServer=="Treasure 7")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(*itServer=="Treasure 8")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(*itServer=="King")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(*itServer=="Queen")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(*itServer=="Pirate")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");

    }
}


void SkullGame::on_btn2_clicked()
{
    if(!clientPlayed){
        itServer=HandServer.begin();
    advance(itServer,1);
        QString cardData="Play "+*itServer+" ";
        if(socket){

            if(socket->isOpen()){
                QDataStream socketstream(socket);
                socketstream.setVersion(QDataStream::Qt_5_15);
                QByteArray byteArray = cardData.toUtf8();
                socketstream<<byteArray;
                socket->waitForBytesWritten(6000);

            }
        }
        btnlist[0]=ui->btn1;
        btnlist[1]=ui->btn2;
        btnlist[2]=ui->btn3;
        btnlist[3]=ui->btn4;
        btnlist[4]=ui->btn5;
        btnlist[5]=ui->btn6;
        btnlist[6]=ui->btn7;
        btnlist[7]=ui->btn8;
        btnlist[8]=ui->btn9;
        btnlist[9]=ui->btn10;
        btnlist[10]=ui->btn11;
        btnlist[11]=ui->btn12;
        btnlist[12]=ui->btn13;
        btnlist[13]=ui->btn14;
        for(int i=0;i<14;i++)
           btnlist[i]->setDisabled(true);

        btnlist[0]->hide();
        if(*itServer=="PirateFlag 1")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag1.jpg);\n");
        if(*itServer=="PirateFlag 2")
       ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag2.jpg);\n");
        if(*itServer=="PirateFlag 3")
       ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag3.jpg);\n");
        if(*itServer=="PirateFlag 4")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag4.jpg);\n");
        if(*itServer=="PirateFlag 5")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag5.jpg);\n");
        if(*itServer=="PirateFlag 6")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag6.jpg);\n");
        if(*itServer=="PirateFlag 7")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag7.jpg);\n");
        if(*itServer=="PirateFlag 8")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/PirateFlag8.jpg);\n");
        if(*itServer=="Parrot 1")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot1.jpg);\n");
        if(*itServer=="Parrot 2")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot2.jpg);\n");
        if(*itServer=="Parrot 3")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot3.jpg);\n");
        if(*itServer=="Parrot 4")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot4.jpg);\n");
        if(*itServer=="Parrot 5")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot5.jpg);\n");
        if(*itServer=="Parrot 6")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot6.jpg);\n");
        if(*itServer=="Parrot 7")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot7.jpg);\n");
        if(*itServer=="Parrot 8")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Parrot8.jpg);\n");
        if(*itServer=="Map 1")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map1.jpg);\n");
        if(*itServer=="Map 2")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map2.jpg);\n");
        if(*itServer=="Map 3")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map3.jpg);\n");
        if(*itServer=="Map 4")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map4.jpg);\n");
        if(*itServer=="Map 5")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map5.jpg);\n");
        if(*itServer=="Map 6")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map6.jpg);\n");
        if(*itServer=="Map 7")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map7.jpg);\n");
        if(*itServer=="Map 8")
         ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Map8.jpg);\n");
        if(*itServer=="Treasure 1")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure1.jpg);\n");
        if(*itServer=="Treasure 2")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure2.jpg);\n");
        if(*itServer=="Treasure 3")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure3.jpg);\n");
        if(*itServer=="Treasure 4")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure4.jpg);\n");
        if(*itServer=="Treasure 5")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure5.jpg);\n");
        if(*itServer=="Treasure 6")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure6.jpg);\n");
        if(*itServer=="Treasure 7")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure7.jpg);\n");
        if(*itServer=="Treasure 8")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Treasure8.jpg);\n");
        if(*itServer=="King")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/King.jpg);\n");
        if(*itServer=="Queen")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/Queen.jpg);\n");
        if(*itServer=="Pirate")
        ui->myCard->setStyleSheet("border-image:url(:/new/prefix1/TheGiant.jpg);\n");

    }
}

