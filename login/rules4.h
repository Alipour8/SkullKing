#ifndef RULES4_H
#define RULES4_H

#include <QWidget>
#include"rules5.h"

namespace Ui {
class rules4;
}

class rules4 : public QWidget
{
    Q_OBJECT

public:
    explicit rules4(QWidget *parent = nullptr);
    ~rules4();

private slots:
    void on_pushButton_clicked();

private:
    Ui::rules4 *ui;
};

#endif // RULES4_H
