#ifndef RULES_H
#define RULES_H

#include <QWidget>
#include"rules2.h"

namespace Ui {
class rules;
}


class rules : public QWidget
{
    Q_OBJECT

public:
    explicit rules(QWidget *parent = nullptr);
    ~rules();



private slots:
    void on_pushButton_clicked();

private:
    Ui::rules *ui;
    //rules2*rul;
    //login*log;
};

#endif // RULES_H
