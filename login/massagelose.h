#ifndef MASSAGELOSE_H
#define MASSAGELOSE_H

#include <QMainWindow>

namespace Ui {
class massagelose;
}

class massagelose : public QMainWindow
{
    Q_OBJECT

public:
    explicit massagelose(QWidget *parent = nullptr);
    ~massagelose();

private:
    Ui::massagelose *ui;
};

#endif // MASSAGELOSE_H
