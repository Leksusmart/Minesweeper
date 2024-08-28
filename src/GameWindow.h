#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "WelcomeWindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow {
public:
    explicit GameWindow(WelcomeWindow *parent = nullptr);
    ~GameWindow();

private:
    Q_OBJECT
    Ui::GameWindow *ui;

public slots:

private slots:

};

#endif // GAMEWINDOW_H
