#ifndef RULES2_H
#define RULES2_H

#include <QWidget>
#include"rules3.h"

namespace Ui {
class rules2;
}

class rules2 : public QWidget
{
    Q_OBJECT

public:
    explicit rules2(QWidget *parent = nullptr);
    ~rules2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::rules2 *ui;
};

#endif // RULES2_H
