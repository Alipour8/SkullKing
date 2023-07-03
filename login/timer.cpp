#include "timer.h"
#include "ui_timer.h"
#include<QTimer>
#include<QDebug>

timer::timer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::timer)
{
    ui->setupUi(this);
    setWindowTitle("Timer");
    mytimer=new QTimer(this);
    mytimer->setInterval(60);
    mytimer->setSingleShot(false);
    connect(mytimer,SIGNAL(timeout()),this,SLOT(timerslot()));
}

timer::~timer()
{
    delete ui;
}

void timer::timerslots(){
    qDebug()<<"timeslots";
}
void timer::on_pushButton_clicked()
{
    if(this->mytimer->isActive()==true){
        this->mytimer->stop();
        ui->pushButton->setText("Start");
    }
    else{
        this->mytimer->start(60);
        ui->pushButton->setText("Stop");
    }
}

