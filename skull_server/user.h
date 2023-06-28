#ifndef USER_H
#define USER_H

#include <QWidget>
#include<QDialog>

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QByteArray text, QWidget *parent = nullptr);
    ~user();

private:
    Ui::user *ui;
};

#endif // USER_H
