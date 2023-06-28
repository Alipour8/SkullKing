#include "server.h"
#include "ui_server.h"

server::server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::server)
{
    ui->setupUi(this);

    QFile file("skull-Database.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        file.open(QIODevice::WriteOnly);
        QJsonObject main;
        main.insert("Users", QJsonArray());
        file.write(QJsonDocument(main).toJson());
        file.close();
    }

    Server = new QTcpServer(this);
    Server->listen(QHostAddress::Any, 2020);

    if (!Server->isListening())
        ui->textEdit->setText("not listening. There is a problem");

    connect(Server, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
    ui->textEdit->setText((time.currentTime()).toString() + "       Listening...\t\n");
}

server::~server()
{
    delete ui;
}

void server::newConnectionSlot()
{
    socket = Server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void server::readyRead()
{
    QByteArray data = socket->readAll();

    if(data == "I WANT DATA") //get
    {
        QFile file("skull-Database.json");
        file.open(QIODevice::ReadOnly);

        socket->write(file.readAll());
        socket->waitForBytesWritten();
        ui->textEdit->append((time.currentTime()).toString() + "       Transferring data       " + QString::number(socket->socketDescriptor()) + "\t");
        file.close();
    }
    else //set
    {
        QFile file("skull-Database.json");
        file.open(QIODevice::ReadWrite | QIODevice::Truncate);
        file.write(data);
        file.close();
    }
}

void server::on_pushButton_clicked()  //save logs
{
    QString dir;
    dir = QFileDialog::getSaveFileName(this, "Save");
    dir += ".txt";
    QFile file(dir);
    file.open(QFile::WriteOnly | QFile::Truncate);
    file.write(ui->textEdit->toPlainText().toUtf8());
    file.close();
}


void server::on_pushButton_2_clicked()  //get user
{
    QString text = QInputDialog::getText(this, tr("skull king"), tr("Username:"), QLineEdit::Normal);
    if (!text.isEmpty())
    {
        QFile file("skull-Database.json");
        file.open(QIODevice::ReadOnly);

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray arr = (doc.object())["Users"].toArray();

        for (int i = 0; i < arr.size(); i++)
            if ((arr[i].toObject())["Username"].toString() == text)
            {
                doc.setObject(arr[i].toObject());
                user *u = new user(doc.toJson(), this);
                u->exec();
                return;
            }

        user *u = new user("This user does not exist !!!");
        u->exec();
    }
}
