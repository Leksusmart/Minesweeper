#include "WelcomeWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    WelcomeWindow Window;
    Window.show();
    return App.exec();
}
