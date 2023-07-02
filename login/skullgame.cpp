//it is server of game
#include "skullgame.h"
#include "ui_skullgame.h"
#include <QTcpServer>
#include <QHostInfo>
#include <QList>
#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QThread>
#include <QtMath>
#include "ground.h"
#include "deck.h"
#include"menu.h"

Deck deck;
Ground groundserver;

bool lockserver = false, clientplayed = false;
//ctr is counter
int roundgame = 1, handCanTakeserver, handTakenserver = 0, scoreserver = 0, j = 0, ctr = 0;

QLabel **lbllistserver = new QLabel*[14];
QPushButton **btnlistserver = new QPushButton*[14];

QList<QString> Handserver;
QList<QString>::Iterator itHandserver;


SkullGame::SkullGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SkullGame)
{
    ui->setupUi(this);
    setWindowTitle("Server");
    QString localhostname = QHostInfo::localHostName();
    QString localhostIP;
    QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
            localhostIP = address.toString();
        }
    }
    ui->label_4->setText(localhostIP);
    server = new QTcpServer();
    if(server->listen(QHostAddress::Any, 1234)){
        connect(server, &QTcpServer::newConnection, this, &SkullGame::connection);
        ui->lbl3->setText("  Waiting...");
    }
    else{
        ui->lbl3->setText("  Error!");
    }
}


SkullGame::SkullGame(user me,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SkullGame)
{
    ui->setupUi(this);
    setWindowTitle("Server");
    howAmI=me;
    QString localhostname = QHostInfo::localHostName();
    QString localhostIP;
    QList<QHostAddress> hostList = QHostInfo::fromName(localhostname).addresses();
    foreach (const QHostAddress& address, hostList) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address.isLoopback() == false) {
            localhostIP = address.toString();
        }
    }
    ui->label_4->setText(localhostIP);
    server = new QTcpServer();
    if(server->listen(QHostAddress::Any, 1234)){
        connect(server, &QTcpServer::newConnection, this, &SkullGame::connection);
        ui->lbl3->setText("  Waiting...");
    }
    else{
        ui->lbl3->setText("  Error!");
    }
}

SkullGame::~SkullGame()
{
    delete ui;
}


void SkullGame::connection(){
    while(server->hasPendingConnections()){
        socket = server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &SkullGame::readSocket);
        ui->lbl3->setText(" Connected");
        ui->label_4->hide();
        break;
    }
}


void SkullGame::readSocket(){
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray buffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream.startTransaction();
    socketStream >> buffer;
    QStringList command = QString(buffer).split(" ");
    if(command[0] == "server"){
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setEnabled(true);
    }
    if(command[0] == "lock")
        lockserver = true;
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
    if(command[0] == "serverwin"){
        handTakenserver++;
        scoreserver += command[1].toInt();
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        ui->lblscore->setText(QString::number(scoreserver));
        //call maindatabase for editing user score in json file
        maindatabase::score(howAmI,scoreserver);
        //call maindatabase for adding user win in json file
        maindatabase::addwin(howAmI);

        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setEnabled(true);
        ui->pushButton->setEnabled(true);
    }
    if(command[0] == "clientwin"){
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        ui->lblscore->setText(QString::number(scoreserver));
        ui->pushButton->setEnabled(true);
        //call maindatabase for adding user lost in json file
        maindatabase::addlost(howAmI);
    }
    if(command[0] == "enable"){
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setEnabled(true);
    }
    if(command[0] == "play"){
        clientplayed = true;
        Card tmp(command[2].toInt(), command[1]);
        tmp.setOwner("client");
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setEnabled(true);
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
        groundserver.ground.push_back(tmp);
    }
}


void sendMessageserver(QString tmp, QTcpSocket* socket){
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


void SkullGame::on_pushButton_clicked()
{
    if(j == 2 * roundgame || (j == 0 && roundgame == 1)){
        if(roundgame != 1 || j != 0){
            deck.refresh();
            if(handTakenserver == handCanTakeserver){
                scoreserver += (10 * handCanTakeserver);
                ui->lblscore->setText(QString::number(scoreserver));
            }
            else{
                scoreserver -= (abs((handCanTakeserver - handTakenserver)) * 10);
                ui->lblscore->setText(QString::number(scoreserver));
            }
            handTakenserver = 0;
            ui->lblhandtaken->setText(QString::number(handTakenserver));
        }
        for(;!Handserver.isEmpty();){
            itHandserver = Handserver.begin();
            Handserver.erase(itHandserver);
        }
        if(ctr){
            sendMessageserver("free", socket);
            roundgame++;
        }
        ctr++;
        j = 1;
        ui->pushButton_2->setEnabled(true);
        ui->cmb->setEnabled(true);
        QStringList list;
        ui->cmb->clear();
        for(int i = 0; i <= 2 * roundgame; i++)
            list.push_back(QString::number(i));
        ui->cmb->addItems(list);
        lbllistserver[0] = ui->lb1;
        lbllistserver[1] = ui->lb2;
        lbllistserver[2] = ui->lb3;
        lbllistserver[3] = ui->lb4;
        lbllistserver[4] = ui->lb5;
        lbllistserver[5] = ui->lb6;
        lbllistserver[6] = ui->lb7;
        lbllistserver[7] = ui->lb8;
        lbllistserver[8] = ui->lb9;
        lbllistserver[9] = ui->lb10;
        lbllistserver[10] = ui->lb11;
        lbllistserver[11] = ui->lb12;
        lbllistserver[12] = ui->lb13;
        lbllistserver[13] = ui->lb14;
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        if(socket->isOpen()){
           ui->pushButton->setDisabled(true);
           int i = 0;
           for(; i < 2 * roundgame; i++){
               btnlistserver[i]->show();
               lbllistserver[i]->show();
               Card tmp = deck.deck.front();
               deck.deck.erase(deck.deck.begin());
               QString type = tmp.get_type();
               Handserver.push_back(type);
               if(type == "flag")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);\n");
               if(type == "parrot")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);\n");
               if(type == "map")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);\n");
               if(type == "jack")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);\n");
               if(type == "queen")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);\n");
               if(type == "treasure")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);\n");
               if(type == "skull")
                    btnlistserver[i]->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);\n");
               lbllistserver[i]->setText(QString::number(tmp.get_value()));
           }
           for(; i < 14; i++)
               btnlistserver[i]->hide();
           QString type2 = "hand ";
           for(i = 0; i < 2 * roundgame; i++){
               Card tmp2 = deck.deck.front();
               deck.deck.erase(deck.deck.begin());
               type2 += tmp2.get_type() + " ";
               int val = tmp2.get_value();
               type2 += QString::number(val) + " ";
           }
           sendMessageserver(type2, socket);
        }
    }
    else
        j++;
    ui->enemylbl->setStyleSheet("border-image: url(:/new/prefix1/CardFrame.jpg);\nborder-radius:10px;");
    ui->enemyvaluelbl->clear();
    ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/CardFrame.jpg);\nborder-radius:10px;");
    ui->mycardvaluelbl->clear();
}


void SkullGame::on_pushButton_2_clicked()
{
    ui->cmb->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    if(lockserver){
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setEnabled(true);
        QString tmp = "enable";
        sendMessageserver(tmp, socket);
    }
    else{
        QString tmp = "lock";
        sendMessageserver(tmp, socket);
    }
    handCanTakeserver = ui->cmb->itemText(ui->cmb->currentIndex()).toInt();
}


void SkullGame::on_btn1_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        QString command = "play " + *itHandserver + " " + ui->lb1->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[0]->hide();
        ui->lb1->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb1->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        QString command = "last " + *itHandserver + " " + ui->lb1->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[0]->hide();
        ui->lb1->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb1->text());
        Card tmp(ui->lb1->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn2_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 1);
        QString command = "play " + *itHandserver + " " + ui->lb2->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[1]->hide();
        ui->lb2->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb2->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 1);
        QString command = "last " + *itHandserver + " " + ui->lb2->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[1]->hide();
        ui->lb2->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb2->text());
        Card tmp(ui->lb2->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn5_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 4);
        QString command = "play " + *itHandserver + " " + ui->lb5->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[4]->hide();
        ui->lb5->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb5->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 4);
        QString command = "last " + *itHandserver + " " + ui->lb5->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[4]->hide();
        ui->lb5->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb5->text());
        Card tmp(ui->lb5->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn3_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 2);
        QString command = "play " + *itHandserver + " " + ui->lb3->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[2]->hide();
        ui->lb3->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb3->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 2);
        QString command = "last " + *itHandserver + " " + ui->lb3->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[2]->hide();
        ui->lb3->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb3->text());
        Card tmp(ui->lb3->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn4_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 3);
        QString command = "play " + *itHandserver + " " + ui->lb4->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[3]->hide();
        ui->lb4->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb4->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 3);
        QString command = "last " + *itHandserver + " " + ui->lb4->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[3]->hide();
        ui->lb4->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb4->text());
        Card tmp(ui->lb4->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn6_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 5);
        QString command = "play " + *itHandserver + " " + ui->lb6->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[5]->hide();
        ui->lb6->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb6->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 5);
        QString command = "last " + *itHandserver + " " + ui->lb6->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[5]->hide();
        ui->lb6->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb6->text());
        Card tmp(ui->lb6->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn7_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 6);
        QString command = "play " + *itHandserver + " " + ui->lb7->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[6]->hide();
        ui->lb7->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb7->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 6);
        QString command = "last " + *itHandserver + " " + ui->lb7->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[6]->hide();
        ui->lb7->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb7->text());
        Card tmp(ui->lb7->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn8_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 7);
        QString command = "play " + *itHandserver + " " + ui->lb8->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[7]->hide();
        ui->lb8->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb8->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 7);
        QString command = "last " + *itHandserver + " " + ui->lb8->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[7]->hide();
        ui->lb8->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb8->text());
        Card tmp(ui->lb8->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn9_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 8);
        QString command = "play " + *itHandserver + " " + ui->lb9->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[8]->hide();
        ui->lb9->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb9->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 8);
        QString command = "last " + *itHandserver + " " + ui->lb9->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[8]->hide();
        ui->lb9->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb9->text());
        Card tmp(ui->lb9->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn10_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 9);
        QString command = "play " + *itHandserver + " " + ui->lb10->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[9]->hide();
        ui->lb10->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb10->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 9);
        QString command = "last " + *itHandserver + " " + ui->lb10->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[9]->hide();
        ui->lb10->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb10->text());
        Card tmp(ui->lb10->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1;
            btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3;
            btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5;
            btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7;
            btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9;
            btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11;
            btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13;
            btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn11_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 10);
        QString command = "play " + *itHandserver + " " + ui->lb11->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[10]->hide();
        ui->lb11->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb11->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 10);
        QString command = "last " + *itHandserver + " " + ui->lb11->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1;
        btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3;
        btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5;
        btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7;
        btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9;
        btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11;
        btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13;
        btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[10]->hide();
        ui->lb11->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb11->text());
        Card tmp(ui->lb11->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn12_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 11);
        QString command = "play " + *itHandserver + " " + ui->lb12->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[11]->hide();
        ui->lb12->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb12->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 11);
        QString command = "last " + *itHandserver + " " + ui->lb12->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[11]->hide();
        ui->lb12->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb12->text());
        Card tmp(ui->lb12->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn13_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 12);
        QString command = "play " + *itHandserver + " " + ui->lb13->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[12]->hide();
        ui->lb13->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb13->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 12);
        QString command = "last " + *itHandserver + " " + ui->lb13->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[12]->hide();
        ui->lb13->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb13->text());
        Card tmp(ui->lb13->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}


void SkullGame::on_btn14_clicked()
{
    ui->pushButton->setEnabled(true);
    if(!clientplayed){
        itHandserver = Handserver.begin();
        std::advance(itHandserver, 13);
        QString command = "play " + *itHandserver + " " + ui->lb14->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[13]->hide();
        ui->lb14->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb14->text());
    }
    else{
        clientplayed = false;
        itHandserver = Handserver.begin();
        advance(itHandserver, 13);
        QString command = "last " + *itHandserver + " " + ui->lb14->text();
        sendMessageserver(command, socket);
        btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
        btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
        btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
        btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
        btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
        btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
        btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
        for(int i = 0; i < 14; i++)
            btnlistserver[i]->setDisabled(true);
        btnlistserver[13]->hide();
        ui->lb14->hide();
        if(*itHandserver == "flag")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/flag.JPG);");
        if(*itHandserver == "treasure")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/treasure.JPG);");
        if(*itHandserver == "map")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/map.JPG);");
        if(*itHandserver == "skull")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/skullking.JPG);");
        if(*itHandserver == "jack")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/pirate.JPG);");
        if(*itHandserver == "queen")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/queen.JPG);");
        if(*itHandserver == "parrot")
            ui->mycardlbl->setStyleSheet("border-image: url(:/new/prefix1/parot.JPG);");
        ui->mycardvaluelbl->setText(ui->lb14->text());
        Card tmp(ui->lb14->text().toInt(), *itHandserver);
        tmp.setOwner("server");
        groundserver.ground.push_back(tmp);
        QPair<QString, int> winner = groundserver.GroundWinner();
        QString order = winner.first + "win" + " " + QString::number(winner.second);
        sendMessageserver(order, socket);
        if(winner.first == "server"){
            scoreserver += winner.second;
            handTakenserver++;
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setEnabled(true);
        }
        else{
            btnlistserver[0] = ui->btn1; btnlistserver[1] = ui->btn2;
            btnlistserver[2] = ui->btn3; btnlistserver[3] = ui->btn4;
            btnlistserver[4] = ui->btn5; btnlistserver[5] = ui->btn6;
            btnlistserver[6] = ui->btn7; btnlistserver[7] = ui->btn8;
            btnlistserver[8] = ui->btn9; btnlistserver[9] = ui->btn10;
            btnlistserver[10] = ui->btn11; btnlistserver[11] = ui->btn12;
            btnlistserver[12] = ui->btn13; btnlistserver[13] = ui->btn14;
            for(int i = 0; i < 14; i++)
                btnlistserver[i]->setDisabled(true);
        }
        ui->lblscore->setText(QString::number(scoreserver));
        ui->lblhandtaken->setText(QString::number(handTakenserver));
        QList<Card>::Iterator itground;
        for(; !groundserver.ground.isEmpty();){
            itground = groundserver.ground.begin();
            groundserver.ground.erase(itground);
        }
    }
}

