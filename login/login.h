#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMainWindow>
#include<QLabel>
#include"singup.h"
#include"rules.h"
#include"forgetpassword.h"
#include"maindatabase.h"
#include"user.h"
#include"menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);

    ~login();

    bool Login(QString u, QString p);

    bool loggedIn;

public :
     //void startGame();
     //void showrule();
     //void on_ExitKey_clicked();
     //void opennewwindow();
    //void sing_up();
     /* void on_ExitKey_clicked();
    void on_signupKey_clicked();
    void on_enterKey_clicked();
    void on_eye_pressed();
    void on_eye_released();
    void on_inputPassword_textEdited(const QString &arg1);*/


private slots:
    void on_rule_clicked();

    void on_forgetpassbtn_clicked();

    void on_regButton_clicked();

    void on_checkBox_showpass_stateChanged(int arg1);

    void on_loginButton_clicked();

private:
    Ui::login *ui;
    //singup *Sing;
    rules*rules;
    user inneruser;
    maindatabase *database;
    QString username;
    QString password;
    menu*Menu;
};
#endif // LOGIN_H
