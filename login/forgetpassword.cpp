#include "forgetpassword.h"
#include "ui_forgetpassword.h"

forgetpassword::forgetpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
    setWindowTitle("Forget password");
}

forgetpassword::~forgetpassword()
{
    delete ui;
}

/*void forgetpassword::show_password(){
    user forgetpass;
        QString pass, pass1, email, username;
        username = ui->usernameforforgetpass->text();
        email = ui->phoneforforgetpass->text();
        forgetpass.set_UserName(username);
        forgetpass.set_EmailAddress(email);
        if(database->userpasswordForforgot(forgetpass, pass))
        {

            pass1 = "Your password is : " + pass;
            ui->statusforforgetpass_4->setText(pass1);

            ui->usernameforforgetpass->setText("");
            ui->phoneforforgetpass->setText("");
            ui->statusforforgetpass_4->setText("");

        }
        else
        {
            ui->statusforforgetpass_4->setText("Sorry, User not found");
        }
        ui->usernameforforgetpass->setText("");
        ui->phoneforforgetpass->setText("");
        ui->statusforforgetpass_4->setText("");
}*/

void forgetpassword::on_showpassforforgetpass_clicked()
{
        user forgetpass;
        QString pass, pass1, phone, username;
        username = ui->usernameforforgetpass->text();
        phone = ui->phoneforforgetpass->text();
        forgetpass.set_UserName(username);
        forgetpass.set_PhoneNumber(phone);
        if(database->userpasswordForforgot(forgetpass, pass))
        {

            pass1 = "Your password is : " + pass;
            ui->lineEdit->setText(pass1);

            ui->usernameforforgetpass->setText("");
            ui->phoneforforgetpass->setText("");
            ui->statusforforgetpass_4->setText("");

        }
        else
        {
            ui->statusforforgetpass_4->setText("Sorry, User not found");
        }
        ui->usernameforforgetpass->setText("");
        ui->phoneforforgetpass->setText("");
        ui->statusforforgetpass_4->setText("");
}

void forgetpassword::on_backtologinforgetpass_clicked()
{
    this->hide();
    login*log=new login();
    log->show();
}
