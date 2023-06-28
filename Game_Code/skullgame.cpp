#include "skullgame.h"
#include "ui_skullgame.h"

SkullGame::SkullGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SkullGame)
{
    ui->setupUi(this);
}

SkullGame::~SkullGame()
{
    delete ui;
}

