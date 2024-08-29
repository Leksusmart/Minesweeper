#include <QApplication>
#include "GameWindow.h"
#include "WelcomeWindow.h"

int main(int argc, char *argv[])
{
   QApplication App(argc, argv);
   WelcomeWindow Window;
   Window.show();
   return App.exec();
}
