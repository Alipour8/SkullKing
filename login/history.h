#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include"user.h"
#include <QDialog>
#include "maindatabase.h"

namespace Ui {
class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    history(user me,QWidget *parent = nullptr);
    history(QString name,QWidget *parent = nullptr);
    ~history();

private slots:
    void on_show_clicked();

    void on_backbtn_clicked();

private:
    Ui::history *ui;
    user howAmI;
    QString name;
    maindatabase *database;
};

#endif // HISTORY_H
