#ifndef SINGUP_H
#define SINGUP_H

#include <QWidget>
#include"login.h"
#include<QJsonObject>
#include<QFile>
#include<QByteArray>
#include<QDebug>
#include<QJsonDocument>
#include <QPixmap>
#include <QBitmap>
#include <QWidget>
#include<QPushButton>
#include <QMessageBox>
#include"maindatabase.h"

namespace Ui {
class singup;
}

class singup : public QWidget
{
    Q_OBJECT

public:
    explicit singup(QWidget *parent = nullptr);
    ~singup();

private:
    Ui::singup *ui;

private:
    maindatabase *database;

private slots:
    /*void on_returnKey_clicked();
    void on_nextKey_clicked();
    void on_acceptKey_clicked();
    void on_eye1_pressed();
    void on_eye1_released();
    void on_eye2_pressed();
    void on_eye2_released();
    void on_inputPassword_textEdited(const QString &arg1);*/
    void on_completeRegButton_clicked();
    void on_showpassforsignup_stateChanged(int arg1);
    void on_backButton_clicked();
};

#endif // SINGUP_H
