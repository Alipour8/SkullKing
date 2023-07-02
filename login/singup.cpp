#include "singup.h"
#include "ui_singup.h"

singup::singup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singup)
{
    ui->setupUi(this);

    //QPixmap image("C:/Users/ASUS/Downloads/sign up.jpg");
    //ui->label->setPixmap(image);
    //ui->label->setMask(image.mask());


    setWindowTitle("Sign up/Skull king");
    //setFixedSize(1431, 1091);
}

singup::~singup()
{
    delete ui;
}

/*void singup::addUser(QString _name,QString _username, QString _phone_number,QString _Address,QString _password){
    //_name=ui->name->text();
    QJsonObject person;
    person.insert("name",_name);
    person.insert("username",_username);
    person.insert("phonenumber",_phone_number);
    person.insert("Address",_Address);
    person.insert("password",_password);
}*/

void singup::on_completeRegButton_clicked()
{
    bool halt = false;


        if(ui->usernameRegister->text() == "")
        {
            ui->usernameRegister->setPlaceholderText("Username EMPTY!");
            halt = true;
        }

        if(ui->passwordRegister->text() == "")
        {
            ui->passwordRegister->setPlaceholderText("Password EMPTY!");
            halt = true;
        }
        if(ui->passwordRegister_2->text() == "")
        {
            ui->passwordRegister_2->setPlaceholderText("Second Password EMPTY!");
            halt = true;
        }

        if(ui->emailRegister->text() == "")
        {
            ui->emailRegister->setPlaceholderText("E-mail EMPTY!");
            halt = true;
        }

        if(ui->firstnameRegister->text() == "")
        {
            ui->firstnameRegister->setPlaceholderText("Name EMPTY!");
            halt = true;
        }

        if(ui->phoneRegister->text() == "")
        {
            ui->phoneRegister->setPlaceholderText("Phone is EMPTY!");
            halt = true;
        }


        if(!ui->emailRegister->text().contains("@"))
        {
            ui->emailRegister->setText("");
            ui->emailRegister->setPlaceholderText("Enter a valid E-mail!");
            halt = true;
        }


        if(halt)
        {
            ui->regLabel->setText("<b color:#33>Please correct your mistakes.</b>");
        }
        else
        {
            QString username, password, namee, lastname, phone, email;
            username = ui->usernameRegister->text();
            password = ui->passwordRegister->text();
            namee = ui->firstnameRegister->text();
            phone = ui->phoneRegister->text();
            email = ui->emailRegister->text();

            if(password.size() < 4)
            {
                ui->passwordRegister->clear();
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
                //ui->passwordBox->clear();
            }
            if(ui->passwordRegister_2->text()!= password)
            {
                QMessageBox::warning(this, "Not same", "Passwords are not the same!");
                ui->passwordRegister->clear();
                ui->passwordRegister_2->clear();
            }
            if(!maindatabase::Check_username(username))
            {
                QMessageBox::warning(this,"Duplicate username", "Oh no! We have your username in our database choose another one please!");
                ui->usernameRegister->clear();
            }
            if(!maindatabase::Check_EmailAddress(email))
            {
                QMessageBox::warning(this,"Duplicate email", "Oh no! We have your email in our database choose another one please!");
                ui->emailRegister->clear();
            }
            if(!maindatabase::Check_PhoneNumber(phone))
            {
                QMessageBox::warning(this,"Duplicate phone", "Oh no! We have your phone in our database choose another one please!");
                ui->phoneRegister->clear();
            }

            bool username1, password1, phone1, email1;
            username1 = ui->usernameRegister->text().size();
            password1 = ui->passwordRegister->text().size();
            phone1 = ui->phoneRegister->text().size();
            email1 = ui->emailRegister->text().size();

            if(username1 && password1 && phone1 && email1)
            {
                user userRegister;
                userRegister.set_UserName(username);
                userRegister.set_Password(password);
                userRegister.set_EmailAddress(email);
                userRegister.set_Firstname(namee);
                userRegister.set_PhoneNumber(phone);


                database->Add_user(userRegister);

                ui->regLabel->setText("");
                ui->usernameRegister->setText("");
                ui->passwordRegister->setText("");
                ui->passwordRegister_2->setText("");
                ui->emailRegister->setText("");
                ui->firstnameRegister->setText("");
                ui->phoneRegister->setText("");
                ui->showpassforsignup->setChecked(false);
                ui->regLabel->setText("Registration Successful! You can now login.");
            }
        }
}

void singup::on_showpassforsignup_stateChanged(int arg1)
{
    if(arg1)
       {
           ui->passwordRegister->setEchoMode(QLineEdit::Normal);
           ui->passwordRegister_2->setEchoMode(QLineEdit::Normal);
       }
       else
       {
           ui->passwordRegister_2->setEchoMode(QLineEdit::Password);
           ui->passwordRegister->setEchoMode(QLineEdit::Password);
       }
}

void singup::on_backButton_clicked()
{
    close();
    login*log=new login();
    log->show();
}
