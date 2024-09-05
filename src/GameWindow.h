#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "WelcomeWindow.h"

#include <QApplication>
#include <QIcon>
#include <QImage>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QTimer>
#include <QUrl>
#include <QVector>
#include <QWidget>
#include <queue>
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
   bool onceField = true;
   bool onceResize = true;
   QString message = "Error";
   QTimer *timerSec = new QTimer;
   qint64 time = 0;
   short int interval = 100;
   bool GameEnd = false;
   short int deadCellx = NULL;
   short int deadCelly = NULL;
   QTimer *explosionTimer = new QTimer;
   short int openFieldCounter = 0;
   std::queue<QPoint> queue;    // Используем очередь для обработки клеток
   std::vector<QPoint> visited; // Для отслеживания уже открытых клеток
   int currentRadius = 1;       // Переменная для отслеживания радиуса
   int cellsOpenedGlobal = 1;
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
   void minesExplosion();
};

#endif // GAMEWINDOW_H
