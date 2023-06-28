#ifndef SKULLGAME_H
#define SKULLGAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SkullGame; }
QT_END_NAMESPACE

class SkullGame : public QMainWindow
{
    Q_OBJECT

public:
    SkullGame(QWidget *parent = nullptr);
    ~SkullGame();

private:
    Ui::SkullGame *ui;
};
#endif // SKULLGAME_H
