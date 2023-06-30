#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::setting(user me,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    howAmI=me;
}

setting::~setting()
{
    delete ui;
}

void setting::on_savebtn_clicked()
{
    bool halt = false;


    if(ui->passwordeditprofile->text() == "")
    {
        ui->passwordeditprofile->setPlaceholderText("Password EMPTY!");
        halt = true;
    }

    if(ui->firstnameeditprofile->text() == "")
    {
        ui->firstnameeditprofile->setPlaceholderText("Name EMPTY!");
        halt = true;
    }


    if(halt)
    {
        ui->lineEdit_2->setText("<b color:#33>Please correct your mistakes.</b>");
    }
    else
    {
        QString password, firstname, lastname,phone,email;
        password = ui->passwordeditprofile->text();
        firstname = ui->firstnameeditprofile->text();
        phone=ui->phoneeditprofile->text();
        email=ui->emaileditprofile->text();

        if(password.size() < 4)
        {
            ui->passwordeditprofile->clear();
            QMessageBox::warning(this, "Warnning", "password must have at least 4 characters");
        }
        bool hasUppercase = false;
        bool hasNumber = false;
        for (int x = 0; x < password.length(); x++)
        {
            if (password[x] >= 'A' && password[x] < 'Z')
            {
                hasUppercase = true;
            }
            if (password[x] >= '0' && password[x] < '9')
            {
                hasNumber = true;
            }
        }
        // condition to check if password met the 2 requirements for including an uppercase letter and a number
        if (!hasNumber || !hasUppercase)
        {
            QMessageBox::warning(this,"Warning", "Password must include atleast 1 uppercase letter and atleast 1 number");
            ui->passwordeditprofile->clear();
        }

        bool password1;
        password1 = ui->passwordeditprofile->text().size();

        if(password1)
        {
            howAmI.set_Password(password);
            howAmI.set_Firstname(firstname);
            howAmI.set_PhoneNumber(phone);
            howAmI.set_EmailAddress(email);

            maindatabase::Modify_UserDetails(howAmI);


            ui->lineEdit_2->setText("Edited successfully");


            on_backbtn_clicked();

        }
    }
}

void setting::on_backbtn_clicked()
{
    this->hide();

}
