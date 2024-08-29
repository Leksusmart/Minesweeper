#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QDateTime>
#include <QFile>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class WelcomeWindow;
}
QT_END_NAMESPACE

class WelcomeWindow : public QMainWindow
{
public:
   WelcomeWindow(QMainWindow *parent = nullptr);
   ~WelcomeWindow();
   QFile *logFile = new QFile("session.log");
   QDateTime startTime = QDateTime::currentDateTime();
   QFile *data = new QFile("data.json");
   int GamesCounter = 0;
   int Defeats = 0;
   int Wins = 0;
   int maxRows = 0;
   int maxCols = 0;

private:
   Q_OBJECT
   Ui::WelcomeWindow *ui;
   QLabel *markerX;
   QLabel *markerY;
   qint64 hours = 0;
   qint64 minutes = 0;
   qint64 seconds = 0;
   QTimer *timerSec = new QTimer(this);
   double MusicVolume = 0.25;
   double UiVolume = 0.25;

public slots:
   void log(const QString &message);
   void saveData();
   void loadData();
   void endGame(bool win);
private slots:
   void updateMarkerXPosition(int value);
   void updateMarkerYPosition(int value);
   void showWidget(int index);
   QString setTime(int h, int m, int s);
   void closeEvent(QCloseEvent *event) override;
   void startGame();
};
#endif // WELCO;MEWINDOW_H
