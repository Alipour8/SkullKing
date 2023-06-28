#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include"user.h"
#include <QDialog>
#include "maindatabase.h"
#include <QCoreApplication>

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    setting(user me,QWidget *parent = nullptr);
    ~setting();

private slots:
    void on_savebtn_clicked();

    void on_backbtn_clicked();

private:
    Ui::setting *ui;
    user howAmI;
    QString name;
};

#endif // SETTING_H
