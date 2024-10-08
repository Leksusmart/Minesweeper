#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QAudioOutput>
#include <QDateTime>
#include <QFile>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include <QUrl>

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
   Ui::WelcomeWindow *ui;
   qint64 hours = 0;
   qint64 minutes = 0;
   qint64 seconds = 0;
   int uncorrectFlags = 0;
   int defusedCounter = 0;

   QMediaPlayer *background = new QMediaPlayer(this);
   double MusicVolume = 0.25;
   double UiVolume = 0.25;

private:
   Q_OBJECT
   QLabel *markerX;
   QLabel *markerY;
   QTimer *timerSec = new QTimer(this);

   QUrl source1 = QUrl("qrc:/sound/sound/background/Dancefloor_Lover_INSTRUMENTAL.mp3");
   QUrl source2 = QUrl("qrc:/sound/sound/background/Hard_2_Find_INSTRUMENTAL.mp3");
   QAudioOutput *audioOutput = new QAudioOutput(this);
   QAudioOutput *audioOutputUi = new QAudioOutput(this);
   QMediaPlayer *soundUi = new QMediaPlayer(this);
   QUrl soundClicked = QUrl("qrc:/sound/sound/Button.mp3");
   QUrl soundCheckBox = QUrl("qrc:/sound/sound/CheckBox.mp3");
public slots:
   void log(const QString &message);
   void saveData();
   void loadData();
   void endGame(bool win);
   QString setTime(int h, int m, int s);
   qint64 decryptTime(QString sTime);
   void volumeUp(double volume);
   void volumeDown(double volume);
   void volumeUp();
   void volumeDown();
private slots:
   void updateMarkerXPosition(int value);
   void updateMarkerYPosition(int value);
   void showWidget(int index);
   void closeEvent(QCloseEvent *event) override;
   void startGame();
};
#endif // WELCOMEWINDOW_H
