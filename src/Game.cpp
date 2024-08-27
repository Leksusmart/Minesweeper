#include "GameWindow.h"
#include "WelcomeWindow.h"
#include "ui_Game.h"

GameWindow::GameWindow(WelcomeWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}
