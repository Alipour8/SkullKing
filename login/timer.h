#ifndef TIMER_H
#define TIMER_H

#include <QMainWindow>

namespace Ui {
class timer;
}

class timer : public QMainWindow
{
    Q_OBJECT

public:
    explicit timer(QWidget *parent = nullptr);
    ~timer();

private slots:
    void on_pushButton_clicked();
    void timerslots();
private:
    Ui::timer *ui;
    QTimer*mytimer;
};

#endif // TIMER_H
