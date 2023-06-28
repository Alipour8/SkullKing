#ifndef RULES5_H
#define RULES5_H

#include <QWidget>

namespace Ui {
class rules5;
}

class rules5 : public QWidget
{
    Q_OBJECT

public:
    explicit rules5(QWidget *parent = nullptr);
    ~rules5();

private slots:
    void on_pushButton_clicked();

private:
    Ui::rules5 *ui;
};

#endif // RULES5_H
