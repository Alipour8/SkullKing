#ifndef MASSAGEWIN_H
#define MASSAGEWIN_H

#include <QMainWindow>

namespace Ui {
class massagewin;
}

class massagewin : public QMainWindow
{
    Q_OBJECT

public:
    explicit massagewin(QWidget *parent = nullptr);
    ~massagewin();

private:
    Ui::massagewin *ui;
};

#endif // MASSAGEWIN_H
