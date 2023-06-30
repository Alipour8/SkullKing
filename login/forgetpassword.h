#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>

#include"maindatabase.h"
#include"user.h"
#include"maindatabase.h"
#include"login.h"

namespace Ui {
class forgetpassword;
}

class forgetpassword : public QWidget
{
    Q_OBJECT

public:
    explicit forgetpassword(QWidget *parent = nullptr);
    ~forgetpassword();
    //void show_password();

private slots:
    void on_showpassforforgetpass_clicked();

    void on_backtologinforgetpass_clicked();

private:
    Ui::forgetpassword *ui;
    maindatabase *database;
};

#endif // FORGETPASSWORD_H
