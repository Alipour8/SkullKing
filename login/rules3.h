#ifndef RULES3_H
#define RULES3_H

#include <QWidget>
#include"rules4.h"

namespace Ui {
class rules3;
}

class rules3 : public QWidget
{
    Q_OBJECT

public:
    explicit rules3(QWidget *parent = nullptr);
    ~rules3();

private slots:
    void on_pushButton_clicked();

private:
    Ui::rules3 *ui;
};

#endif // RULES3_H
