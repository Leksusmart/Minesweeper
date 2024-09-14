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
#include <QToolButton>
#include <QUrl>
#include <QVector>
#include <QWidget>
#include <array>
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

   QMediaPlayer *background = new QMediaPlayer(this);

private:
   Q_OBJECT
   WelcomeWindow *parent;
   friend WelcomeWindow;
   QVector<QVector<QToolButton *>> buttons;
   QPixmap unpressed = QIcon(":/images/Pictures/button_unpresseed.png").pixmap(QSize(25, 25));
   QPixmap button_0 = QIcon(":/images/Pictures/button_0.png").pixmap(QSize(25, 25));
   QPixmap button_1 = QIcon(":/images/Pictures/button_1.png").pixmap(QSize(25, 25));
   QPixmap button_2 = QIcon(":/images/Pictures/button_2.png").pixmap(QSize(25, 25));
   QPixmap button_3 = QIcon(":/images/Pictures/button_3.png").pixmap(QSize(25, 25));
   QPixmap button_4 = QIcon(":/images/Pictures/button_4.png").pixmap(QSize(25, 25));
   QPixmap button_5 = QIcon(":/images/Pictures/button_5.png").pixmap(QSize(25, 25));
   QPixmap button_6 = QIcon(":/images/Pictures/button_6.png").pixmap(QSize(25, 25));
   QPixmap button_7 = QIcon(":/images/Pictures/button_7.png").pixmap(QSize(25, 25));
   QPixmap button_8 = QIcon(":/images/Pictures/button_8.png").pixmap(QSize(25, 25));
   QPixmap armedbomb = QIcon(":/images/Pictures/button_armedbomb.png").pixmap(QSize(25, 25));
   QPixmap defusedbomb = QIcon(":/images/Pictures/button_defusedbomb.png").pixmap(QSize(25, 25));
   QPixmap flag = QIcon(":/images/Pictures/button_flag.png").pixmap(QSize(25, 25));
   QPixmap question = QIcon(":/images/Pictures/button_question.png").pixmap(QSize(25, 25));
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
   std::array<QUrl, 48> sources = {QUrl("qrc:/sound/sound/background/2_Young_4_Love_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/All_I_Wanna_Do_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/All_Mine_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Another_Galaxy_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Bad_Girl_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Brand_New_Love_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Devotion_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Dont_Rock_The_Boat_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Dreaming_of_You_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Faith_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Fascination_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Figured_Out_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Fly_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Foolin_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Forever_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Freedom_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Frequency_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Friend_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Get_Away_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Go_All_Nite_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Heat_of_the_Moment_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/I_Need_That_Feeling_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/I_Want_You_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Just_Right_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Last_2_Know_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Love_2nite_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Love_in_Motion_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Midnight_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Moments_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Motion_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Neon_Heart_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Nightmare_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Party_Princess_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Physical_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Play_It_Cool_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Shadow_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Something_Good_Tonight_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Summer84_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Take_U_On_A_Ride_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Take_Ur_Hand_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/The_Dream_Machine_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Touch_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/U_Can_Have_It_All_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/U_Keep_Me_Up_All_Nite_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/UFO_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Undercover_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/Unforgettable_INSTRUMENTAL.mp3"),
                                   QUrl("qrc:/sound/sound/background/We_Got_Somethin_INSTRUMENTAL.mp3")};
   QAudioOutput *audioOutput = new QAudioOutput(this);
   QAudioOutput *audioOutputUi = new QAudioOutput(this);
   QMediaPlayer *soundUi = new QMediaPlayer(this);
   QUrl soundClicked = QUrl("qrc:/sound/sound/Button.mp3");
   QUrl soundCheckBox = QUrl("qrc:/sound/sound/CheckBox.mp3");
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
