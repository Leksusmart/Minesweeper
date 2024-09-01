#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "WelcomeWindow.h"

#include <QApplication>
#include <QIcon>
#include <QImage>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QWidget>
namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
public:
   explicit GameWindow(WelcomeWindow *parent = nullptr, int rows = 0, int cols = 0, int mines = 0, QString message = "Error");
   ~GameWindow();
   Ui::GameWindow *ui;
   int rows;
   int cols;
   int mines;
   short int **Field;

private:
   Q_OBJECT
   WelcomeWindow *parent;
   friend WelcomeWindow;
   QVector<QVector<QToolButton *>> buttons;
   QPixmap unpressed = QIcon(":/images/button_unpresseed.png").pixmap(QSize(25, 25));
   QPixmap button_0 = QIcon(":/images/button_0.png").pixmap(QSize(25, 25));
   QPixmap button_1 = QIcon(":/images/button_1.png").pixmap(QSize(25, 25));
   QPixmap button_2 = QIcon(":/images/button_2.png").pixmap(QSize(25, 25));
   QPixmap button_3 = QIcon(":/images/button_3.png").pixmap(QSize(25, 25));
   QPixmap button_4 = QIcon(":/images/button_4.png").pixmap(QSize(25, 25));
   QPixmap button_5 = QIcon(":/images/button_5.png").pixmap(QSize(25, 25));
   QPixmap button_6 = QIcon(":/images/button_6.png").pixmap(QSize(25, 25));
   QPixmap button_7 = QIcon(":/images/button_7.png").pixmap(QSize(25, 25));
   QPixmap button_8 = QIcon(":/images/button_8.png").pixmap(QSize(25, 25));
   QPixmap armedbomb = QIcon(":/images/button_armedbomb.png").pixmap(QSize(25, 25));
   QPixmap defusedbomb = QIcon(":/images/button_defusedbomb.png").pixmap(QSize(25, 25));
   QPixmap flag = QIcon(":/images/button_flag.png").pixmap(QSize(25, 25));
   QPixmap question = QIcon(":/images/button_question.png").pixmap(QSize(25, 25));
   bool once = true;
   bool onceResize = true;
   QString message = "Error";
   QTimer *timerSec = new QTimer;
   qint64 time = 0;
   QTimer *minetimer = new QTimer;
   QVector<QToolButton *> arr;
   short int arrsize = 0;
   short int interval = 800;
   bool GameEnd = false;
   short int minInterval = 50;
   short int openFieldCounter = 0;
   short int intervalCounter = 0;
   bool isTraining = false;

   int tutorialStep = -1;
   QLabel *tutorialArrow = nullptr;
   QLabel *tutorialArrow2 = nullptr;
   QLabel *tutorialText;
   QLabel *hightLight;
   QImage rightArrow;
   QImage leftArrow;
   QImage arrow;
   bool onceTraining = true;
   short int num = NULL;
   QLabel *borderl;
   QLabel *borderu;
   QLabel *borderr;
   QLabel *borderd;
   short int found2x = NULL;
   short int found2y = NULL;
   bool secondTry = false;
public slots:
   void log(const QString &message)
   {
      parent->log(message);
   };
private slots:
   bool createButtonField();
   void resizeEvent(QResizeEvent *event) override;
   void closeEvent(QCloseEvent *event) override;
   void secTimer();
   void leftClick(int x, int y);
   void rightClick(int x, int y);
   void endGame(bool win);
   void updateMineTimer();

   void nextTutorialStep();
   void initializeTutorial();
   void mousePressEvent(QMouseEvent *event) override;
};

#endif // GAMEWINDOW_H
