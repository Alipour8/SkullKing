#include "playclient.h"
#include "ui_playclient.h"
#include <QThread>
#include "deck.h"
#include "menu.h"
#include "massagewin.h"
#include "massagelose.h"
#include <QPushButton>
#include "ground.h"
#include<QTimer>
#include<QDebug>
#include"timer.h"

QPushButton **btnlistclient = new QPushButton*[14];
QLabel **lbllistclient = new QLabel*[14];

bool lockclient = false, serverplayed = false;

int handCanTakeclient, scoreclient = 0, handTakenclient = 0;
Ground groundclient;
QString whoStarts;

QList<QString> Handclient;
QList<QString>::Iterator itHandclient;

PlayClient::PlayClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayClient)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &PlayClient::readsocket);

}

PlayClient::PlayClient(user me,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayClient)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    howAmI=me;
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &PlayClient::readsocket);

}


PlayClient::~PlayClient()
{
    delete ui;
}


void sendMessageclient(QString tmp, QTcpSocket *socket){
    if(socket){
        if(socket->isOpen()){
            QDataStream socketstream(socket);
            socketstream.setVersion(QDataStream::Qt_5_15);
            QByteArray byteArray = tmp.toUtf8();
            socketstream << byteArray;
            socket->waitForBytesWritten(5000);
        }
    }
}


void PlayClient::on_pushButton_clicked()
{
    socket->connectToHost(ui->lineEdit->text(), 1234);
    if(socket->waitForConnected())
         ui->label_2->setText("connected");
    else
        ui->label_2->setText("error");
    ui->pushButton->hide();
    ui->lineEdit->hide();
}


int roundgame2 = 0;


void shareHand(QLabel **lbllist, QPushButton **btnlist, QComboBox * cmb, QStringList carddata){
    cmb->clear();
    roundgame2++;
    for(; !Handclient.isEmpty();)
        Handclient.erase(Handclient.begin());
    QStringList list;
    for(int i = 0; i <= 2 * roundgame2; i++)
        list.push_back(QString::number(i));
    cmb->addItems(list);
    int i = 1;
    for(; i <= 2 * roundgame2; i++){
        btnlistclient[i - 1]->show();
        lbllistclient[i - 1]->show();
        Card tmp(carddata[i * 2].toInt(), carddata[i * 2 - 1]);
        QString type = tmp.get_type();
        Handclient.push_back(type);
        if(type == "flag")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);\n");
        if(type == "parrot")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);\n");
        if(type == "map")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);\n");
        if(type == "jack")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);\n");
        if(type == "queen")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);\n");
        if(type == "treasure")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);\n");
        if(type == "skull")
            btnlist[i - 1]->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);\n");
        lbllist[i - 1]->setText(carddata[i * 2]);
    }
    for(; i <= 14; i++)
        btnlist[i - 1]->hide();
}

void PlayClient::readsocket(){

    lbllistclient[0] = ui->lb1; lbllistclient[1] = ui->lb2;
    lbllistclient[2] = ui->lb3; lbllistclient[3] = ui->lb4;
    lbllistclient[4] = ui->lb5; lbllistclient[5] = ui->lb6;
    lbllistclient[6] = ui->lb7; lbllistclient[7] = ui->lb8;
    lbllistclient[8] = ui->lb9; lbllistclient[9] = ui->lb10;
    lbllistclient[10] = ui->lb11; lbllistclient[11] = ui->lb12;
    lbllistclient[12] = ui->lb13; lbllistclient[13] = ui->lb14;
    btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
    btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
    btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
    btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
    btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
    btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
    btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream >> buffer;
    QStringList command = QString(buffer).split(" ");
    if(command[0] == "hand"){
        if(roundgame2 != 0){
            if(handTakenclient == handCanTakeclient){
                scoreclient += (10 * handCanTakeclient);
                ui->lblscore->setText(QString::number(scoreclient));
            }
            else{
                scoreclient -= (abs((handCanTakeclient - handTakenclient)) * 10);
                ui->lblscore->setText(QString::number(scoreclient));
            }
            handTakenclient = 0;
            ui->lblhandtaken->setText(QString::number(handTakenclient));
        }
        ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/CardFrame.jpg);\nborder-radius:10px;");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/CardFrame.jpg);\nborder-radius:10px;");
        ui->mycardvaluelbl->clear();
        shareHand(lbllistclient, btnlistclient, ui->cmb, command);
        ui->pushButton_2->setEnabled(true);
        ui->cmb->setEnabled(true);
        return;
    }
    if(command[0] == "lock"){
        lockclient = true;
    }
    if(command[0] == "win"){

        //call maindatabase for adding user win in json file
        maindatabase::addwin(howAmI);

        maindatabase::addcoin(howAmI);//dicrease 100 coins

        massagewin *form  = new massagewin;
        form->show();
        this->hide();
        menu *form2 = new menu(howAmI);
        form2->show();
    }
    if(command[0] == "lose"){

        //call maindatabase for adding user lost in json file
        maindatabase::addlost(howAmI);

        massagelose *form = new massagelose;
        form->show();
        this->hide();
        menu *form3 = new menu(howAmI);
        form3->show();
    }
    if(command[0] == "enable" && roundgame2 != 0){
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        ui->cmb->setDisabled(true);
        ui->pushButton_2->setDisabled(true);
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setEnabled(true);
        return;
    }
    if(command[0] == "score"){

        //call maindatabase for adding user score in json file
        maindatabase::score(howAmI,scoreclient);

        sendMessageclient("score " + QString::number(scoreclient), socket);
    }
    if(command[0] == "last"){
        if(command[1] == "flag")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);\n");
        if(command[1] == "parrot")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);\n");
        if(command[1] == "map")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);\n");
        if(command[1] == "treasure")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);\n");
        if(command[1] == "skull")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);\n");
        if(command[1] == "queen")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);\n");
        if(command[1] == "jack")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);\n");
        ui->enemyvaluelbl->setText(command[2]);
    }
    if(command[0] == "play"){
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        Card tmp(command[2].toInt(), command[1]);
        tmp.setOwner("server");
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setEnabled(true);
        if(command[1] == "flag")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(command[1] == "treasure")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(command[1] == "map")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(command[1] == "skull")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(command[1] == "jack")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(command[1] == "queen")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(command[1] == "parrot")
            ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->enemyvaluelbl->setText(command[2]);
        serverplayed = true;
        groundclient.ground.push_back(tmp);
        int i = 0;
        if(command[1] != "jack" && command[1] != "queen" && command[1] != "skull")
            for(itHandclient = Handclient.begin(); itHandclient != Handclient.end(); itHandclient++)
                if(*itHandclient == command[1]){
                    for(itHandclient = Handclient.begin(); itHandclient != Handclient.end(); itHandclient++, i++)
                        if(*itHandclient != command[1] && *itHandclient != "jack" && *itHandclient != "queen" && *itHandclient != "skull")
                            btnlistclient[i]->setDisabled(true);
                    break;
                }
        return;
    }
    if(command[0] == "clientwin"){
        handTakenclient++;
        scoreclient += command[1].toInt();
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        ui->lblscore->setText(QString::number(scoreclient));
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setEnabled(true);
    }
    if(command[0] == "serverwin"){
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        ui->lblscore->setText(QString::number(scoreclient));
        ui->pushButton->setEnabled(true);
    }
}


void PlayClient::on_pushButton_2_clicked()
{
    ui->cmb->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    if(lockclient){
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setEnabled(true);
        QString tmp = "enable";
        sendMessageclient(tmp, socket);
        QThread::sleep(1);
        if(roundgame2 == 1){
            sendMessageclient("server", socket);
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
    }
    else{
        QString tmp = "lock";
        sendMessageclient(tmp, socket);
    }
    handCanTakeclient = ui->cmb->itemText(ui->cmb->currentIndex()).toInt();
}


void PlayClient::on_btn1_clicked()
{
    if(serverplayed){
        serverplayed= false;
        itHandclient = Handclient.begin();
        QString command = "last " + *itHandclient + " " + ui->lb1->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[0]->hide();
        ui->lb1->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb1->text());
        Card tmp(ui->lb1->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        QString command = "play " + *itHandclient + " " + ui->lb1->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[0]->hide();
        ui->lb1->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb1->text());
    }
}


void PlayClient::on_btn2_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 1);
        QString command = "last " + *itHandclient + " " + ui->lb2->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[1]->hide();
        ui->lb2->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb2->text());
        Card tmp(ui->lb2->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 1);
        QString command = "play " + *itHandclient + " " + ui->lb2->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[1]->hide();
        ui->lb2->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb2->text());
    }
}


void PlayClient::on_btn3_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 2);
        QString command = "last " + *itHandclient + " " + ui->lb3->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[2]->hide();
        ui->lb3->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb3->text());
        Card tmp(ui->lb3->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 2);
        QString command = "play " + *itHandclient + " " + ui->lb3->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[2]->hide();
        ui->lb3->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb3->text());
    }
}


void PlayClient::on_btn4_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 3);
        QString command = "last " + *itHandclient + " " + ui->lb4->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[3]->hide();
        ui->lb4->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb4->text());
        Card tmp(ui->lb4->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 3);
        QString command = "play " + *itHandclient + " " + ui->lb4->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[3]->hide();
        ui->lb4->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb4->text());
    }
}


void PlayClient::on_btn5_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 4);
        QString command = "last " + *itHandclient + " " + ui->lb5->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[4]->hide();
        ui->lb5->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb5->text());
        Card tmp(ui->lb5->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 4);
        QString command = "play " + *itHandclient + " " + ui->lb5->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[4]->hide();
        ui->lb5->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb5->text());
    }
}


void PlayClient::on_btn6_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 5);
        QString command = "last " + *itHandclient + " " + ui->lb6->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[5]->hide();
        ui->lb6->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb6->text());
        Card tmp(ui->lb6->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 5);
        QString command = "play " + *itHandclient + " " + ui->lb6->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[5]->hide();
        ui->lb6->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb6->text());
    }
}


void PlayClient::on_btn7_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 6);
        QString command = "last " + *itHandclient + " " + ui->lb7->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[6]->hide();
        ui->lb7->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb7->text());
        Card tmp(ui->lb7->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 6);
        QString command = "play " + *itHandclient + " " + ui->lb7->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[6]->hide();
        ui->lb7->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb7->text());
    }
}


void PlayClient::on_btn8_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 7);
        QString command = "last " + *itHandclient + " " + ui->lb8->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[7]->hide();
        ui->lb8->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb8->text());
        Card tmp(ui->lb8->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 7);
        QString command = "play " + *itHandclient + " " + ui->lb8->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[7]->hide();
        ui->lb8->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb8->text());
    }
}


void PlayClient::on_btn9_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 8);
        QString command = "last " + *itHandclient + " " + ui->lb9->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[8]->hide();
        ui->lb9->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb9->text());
        Card tmp(ui->lb9->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 8);
        QString command = "play " + *itHandclient + " " + ui->lb9->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[8]->hide();
        ui->lb9->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb9->text());
    }
}


void PlayClient::on_btn10_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 9);
        QString command = "last " + *itHandclient + " " + ui->lb10->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[9]->hide();
        ui->lb10->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb10->text());
        Card tmp(ui->lb10->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 9);
        QString command = "play " + *itHandclient + " " + ui->lb10->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[9]->hide();
        ui->lb10->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb10->text());
    }
}


void PlayClient::on_btn11_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 10);
        QString command = "last " + *itHandclient + " " + ui->lb11->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[10]->hide();
        ui->lb11->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb11->text());
        Card tmp(ui->lb11->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 10);
        QString command = "play " + *itHandclient + " " + ui->lb11->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[10]->hide();
        ui->lb11->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb11->text());
    }
}


void PlayClient::on_btn12_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 11);
        QString command = "last " + *itHandclient + " " + ui->lb12->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[11]->hide();
        ui->lb12->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb12->text());
        Card tmp(ui->lb12->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 11);
        QString command = "play " + *itHandclient + " " + ui->lb12->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[11]->hide();
        ui->lb12->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb12->text());
    }
}


void PlayClient::on_btn13_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 12);
        QString command = "last " + *itHandclient + " " + ui->lb13->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[12]->hide();
        ui->lb13->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb13->text());
        Card tmp(ui->lb13->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 12);
        QString command = "play " + *itHandclient + " " + ui->lb13->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[12]->hide();
        ui->lb13->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb13->text());
    }
}


void PlayClient::on_btn14_clicked()
{
    if(serverplayed){
        serverplayed = false;
        itHandclient = Handclient.begin();
        advance(itHandclient, 13);
        QString command = "last " + *itHandclient + " " + ui->lb14->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[13]->hide();
        ui->lb14->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb14->text());
        Card tmp(ui->lb14->text().toInt(), *itHandclient);
        tmp.setOwner("client");
        groundclient.ground.push_back(tmp);
        QPair<QString, int> winner = groundclient.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageclient(order, socket);
        if(winner.first == "client"){
            scoreclient += winner.second;
            handTakenclient++;
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setEnabled(true);
        }
        else{
            btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
            btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
            btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
            btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
            btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
            btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
            btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistclient[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreclient));
        ui->lblhandtaken->setText(QString::number(handTakenclient));
        QList<Card>::Iterator itground;
        for(; !groundclient.ground.isEmpty();){
            itground = groundclient.ground.begin();
            groundclient.ground.erase(itground);
        }
    }
    else{
        ui->enemylbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->enemyvaluelbl->clear();
        ui->mycardlbl->setStyleSheet("border-radius:10px;\nborder:5px solid rgb(156, 0, 0);");
        ui->mycardvaluelbl->clear();
        itHandclient = Handclient.begin();
        advance(itHandclient, 13);
        QString command = "play " + *itHandclient + " " + ui->lb14->text();
        sendMessageclient(command, socket);
        btnlistclient[0] = ui->btn1; btnlistclient[1] = ui->btn2;
        btnlistclient[2] = ui->btn3; btnlistclient[3] = ui->btn4;
        btnlistclient[4] = ui->btn5; btnlistclient[5] = ui->btn6;
        btnlistclient[6] = ui->btn7; btnlistclient[7] = ui->btn8;
        btnlistclient[8] = ui->btn9; btnlistclient[9] = ui->btn10;
        btnlistclient[10] = ui->btn11; btnlistclient[11] = ui->btn12;
        btnlistclient[12] = ui->btn13; btnlistclient[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistclient[i]->setDisabled(true);
        btnlistclient[13]->hide();
        ui->lb14->hide();
        if(*itHandclient == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandclient == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandclient == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandclient == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandclient == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandclient == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandclient == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb14->text());
    }
}


void PlayClient::on_pushButton_3_clicked()
{
    if(socket->isOpen()){
        sendMessageclient("win", socket);
        socket->close();
    }
    menu *form = new menu(howAmI);
    form->show();
    this->hide();
}


void PlayClient::on_pushButton_17_clicked()
{
    timer*tim=new timer();
    tim->show();
}

