#include <QCloseEvent>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QRegularExpression>
#include <QScrollBar>
#include <QSlider>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include "./ui_Welcome.h"
#include "GameWindow.h"
#include "WelcomeWindow.h"
#include "ui_Game.h"

WelcomeWindow::WelcomeWindow(QMainWindow *parent)
    : ui(new Ui::WelcomeWindow)
{
   logFile->open(QIODevice::WriteOnly | QIODevice::Text);
   ui->setupUi(this);
   timerSec->start(1000);
   ui->btn_records->setIcon(QIcon(":/images/cup.png"));
   ui->btn_records->setIconSize(QSize(25, 25));
   ui->btn_settings->setIconSize(QSize(25, 25));
   ui->btn_records->setFixedSize(QSize(25, 25));
   ui->btn_settings->setFixedSize(QSize(25, 25));
   ui->stackedWidget->hide();
   loadData();
   ui->gridLayoutCustom->addWidget(ui->frame, 1, 2, Qt::AlignTop | Qt::AlignLeft);
   int width = ui->progressBarX->width() * ui->progressBarX->value() / ui->progressBarX->maximum();
   int height = ui->progressBarY->height() * ui->progressBarY->value() / ui->progressBarY->maximum();
   ui->frame->setFixedSize(width, height);
   ui->frame->setGeometry(28, 20, ui->frame->width(), ui->frame->height());

   markerX = new QLabel(ui->scrollAreaCustom->widget());
   markerY = new QLabel(ui->scrollAreaCustom->widget());
   markerX->setFixedSize(2, 19);
   markerX->setStyleSheet("background-color: black;");
   markerY->setFixedSize(23, 2);
   markerY->setStyleSheet("background-color: black;");
   ui->labelAllGames->setText(QString::number(GamesCounter));
   ui->labelDefeats->setText(QString::number(Defeats));
   ui->labelWins->setText(QString::number(Wins));
   double g = GamesCounter;
   double w = Wins;
   if (GamesCounter > 0)
      ui->labelWinsProcents->setText(QString::number((w / g) * 100.0) + "%");
   else if (GamesCounter == 0)
      ui->labelWinsProcents->setText("0%");
   QRect availableGeometry = QApplication::primaryScreen()->availableGeometry();
   int screenwidth = availableGeometry.width();
   int screenheight = availableGeometry.height();
   maxCols = (screenwidth - 18) / 25;
   maxRows = (screenheight - 85) / 25;
   log(QString("maxRows %1").arg(maxRows));
   log(QString("maxCols %1").arg(maxCols));
   ui->progressBarX->setMaximum(maxCols);
   ui->progressBarY->setMaximum(maxRows);
   ui->SliderX->setMaximum(maxCols);
   ui->SliderY->setMaximum(maxRows);

   connect(ui->btn_records, &QPushButton::clicked, this, [=] { showWidget(0); });
   connect(ui->btn_settings, &QPushButton::clicked, this, [=] { showWidget(1); });
   connect(ui->comboBox, &QComboBox::currentIndexChanged, this, [=] {
      if (ui->comboBox->currentIndex() == 6) {
         showWidget(2);
         int posX = ui->progressBarX->width() * 4 / ui->progressBarX->maximum() + ui->progressBarX->x();
         int posY = ui->progressBarX->y();
         markerX->move(posX - markerX->width() / 2, posY);
         posY = (ui->progressBarY->height() * 4 / ui->progressBarY->maximum()) + ui->progressBarY->y();
         posX = ui->progressBarY->x();
         markerY->move(posX, posY - markerY->height() / 2);
      } else if (ui->comboBox->currentIndex() != 6 && ui->stackedWidget->currentIndex() == 2 && !ui->stackedWidget->isHidden()) {
         ui->stackedWidget->hide();
      }
   });
   connect(ui->SliderX, &QSlider::valueChanged, this, [=](int value) {
      if (value <= 4) value = 4;
      ui->progressBarX->setValue(value);
      updateMarkerXPosition(value);
   });
   connect(ui->SliderY, &QSlider::valueChanged, this, [=](int value) {
      if (value <= 4) value = 4;
      ui->progressBarY->setValue(value);
      updateMarkerYPosition(value);
   });
   connect(ui->btn_start, &QPushButton::clicked, this, &WelcomeWindow::startGame);
   connect(ui->SliderMusicVolume, &QSlider::valueChanged, this, [=] { MusicVolume = ui->SliderMusicVolume->value() / 100.0; });
   connect(ui->SliderUiVolume, &QSlider::valueChanged, this, [=] { UiVolume = ui->SliderUiVolume->value() / 100.0; });
   connect(timerSec, &QTimer::timeout, this, [=] {
      seconds++;
      if (seconds >= 60) {
         minutes++;
         seconds = 0;
      }
      if (minutes >= 60) {
         hours++;
         minutes = 0;
      }
      ui->labelPlayedTime->setText(setTime(hours, minutes, seconds));
   });
}
void WelcomeWindow::startGame()
{
   GameWindow *Game;
   int rows = 0, cols = 0, mines = 0;
   QString message = "Error";
   switch (ui->comboBox->currentIndex()) {
   case 0: //Обучение
      rows = 4;
      cols = rows * 1.55;
      mines = rows * cols * 0.2;
      message = "Training";
      break;
   case 1: //Лёгкая
      rows = 4;
      cols = rows * 1.55;
      mines = rows * cols * 0.2;
      message = "Easy";
      break;
   case 2: //Средняя
      rows = 7;
      cols = rows * 1.55;
      mines = rows * cols * 0.2;
      message = "Medium";
      break;
   case 3: //Сложная
      rows = 10;
      cols = rows * 1.55;
      mines = rows * cols * 0.2;
      message = "Hard";
      break;
   case 4: //Экстрим
      rows = 14;
      cols = rows * 1.55;
      mines = rows * cols * 0.2;
      message = "Extreme";
      break;
   case 5: //Безумие
      rows = 20;
      cols = rows * 1.55;
      mines = rows * cols * 0.2;
      message = "Insane";
      break;
   case 6: //Своя игра
      rows = ui->progressBarY->value();
      cols = ui->progressBarX->value();
      mines = rows * cols * (ui->spinBoxMinesFill->value() / 100.0);
      message = "Custom";
      break;
   default:
      log("ComboBox switch Error");
      break;
   }
   Game = new GameWindow(this, rows, cols, mines, message);
   Game->ui->groupBoxGameField->setMinimumSize(cols * 25, rows * 25);
   Game->setMinimumSize(cols * 25 + 18, rows * 25 + 83);
   Game->show();
}
void WelcomeWindow::showWidget(int index)
{
   if (ui->stackedWidget->currentIndex() == index && !ui->stackedWidget->isHidden()) {
      if (ui->stackedWidget->currentIndex() == 2) {
      } else if (ui->comboBox->currentIndex() == 6) {
         ui->stackedWidget->setCurrentIndex(2);
      } else {
         ui->stackedWidget->hide();
      }
   } else {
      ui->stackedWidget->setCurrentIndex(index);
      ui->stackedWidget->show();
   }
   if (!ui->stackedWidget->isHidden()) {
      switch (ui->stackedWidget->currentIndex()) {
      case 0: //Records
         log("Current open page is \"Records\"");
      case 1: //Settings
         log("Current open page is \"Settings\"");
      case 2: //Custom_game
         log("Current open page is \"Custom game\"");
      }
   }
}
void WelcomeWindow::updateMarkerXPosition(int value)
{
   int posX = ui->progressBarX->width() * value / ui->progressBarX->maximum() + ui->progressBarX->x();
   int posY = ui->progressBarX->y();
   markerX->move(posX - markerX->width() / 2, posY);

   int width = ui->progressBarX->width() * ui->progressBarX->value() / ui->progressBarX->maximum();
   ui->frame->setFixedSize(width, ui->frame->height());
}
void WelcomeWindow::updateMarkerYPosition(int value)
{
   int posY = (ui->progressBarY->height() * value / ui->progressBarY->maximum()) + ui->progressBarY->y();
   int posX = ui->progressBarY->x();
   markerY->move(posX, posY - markerY->height() / 2);

   int height = ui->progressBarY->height() * ui->progressBarY->value() / ui->progressBarY->maximum();
   ui->frame->setFixedSize(ui->frame->width(), height);
}
void WelcomeWindow::saveData()
{
   QJsonDocument document;
   QJsonObject list;
   bool needLoad = false;
   if (!data->exists()) {
      log("Data file is empty.");
      needLoad = true;
   }

   //Records
   list["Easy"] = ui->labelEasyRecord->text().remove("лучшее время: ");
   list["Medium"] = ui->labelMediumRecord->text().remove("лучшее время: ");
   list["Hard"] = ui->labelHardRecord->text().remove("лучшее время: ");
   list["Extreme"] = ui->labelExtremeRecord->text().remove("лучшее время: ");
   list["Insane"] = ui->labelInsaneRecord->text().remove("лучшее время: ");
   list["GamesCounter"] = GamesCounter;
   list["Defeats"] = Defeats;
   list["Wins"] = Wins;
   qint64 lastseconds = ((hours * 60) + minutes) * 60 + seconds;
   list["PlayedTime"] = lastseconds;

   //Settings
   list["WatchAllField"] = ui->checkBoxWatchAllField->isChecked();
   list["MusicVolume"] = MusicVolume;
   list["UiVolume"] = UiVolume;
   list["UncorrectFlags"] = uncorrectFlags;
   list["DefusedBombs"] = defusedCounter;

   document = QJsonDocument(list);
   data->open(QIODevice::WriteOnly);
   data->write(document.toJson());
   data->close();
   log("Data saved to data.json");
   if (needLoad) loadData();
}
void WelcomeWindow::loadData()
{
   if (data->exists()) {
      data->open(QIODevice::ReadOnly);
      QJsonDocument document = QJsonDocument::fromJson(data->readAll());
      QJsonObject list = document.object();
      data->close();

      //Records
      auto loadRecordLabel = [&](QLabel *label, const QString &key) {
         if (list.contains(key) && list[key].toString().size() > 0) {
            label->setText("лучшее время: " + list[key].toString());
         } else {
            log("Info about \"" + key + "\" is not found.");
            label->setText("лучшее время: ?");
         }
      };
      loadRecordLabel(ui->labelEasyRecord, "Easy");
      loadRecordLabel(ui->labelMediumRecord, "Medium");
      loadRecordLabel(ui->labelHardRecord, "Hard");
      loadRecordLabel(ui->labelExtremeRecord, "Extreme");
      loadRecordLabel(ui->labelInsaneRecord, "Insane");
      if (list.contains("GamesCounter")) {
         GamesCounter = list["GamesCounter"].toInt();
      } else {
         log("Info about \"GamesCounter\" is not found.");
      }
      if (list.contains("Defeats")) {
         Defeats = list["Defeats"].toInt();
      } else {
         log("Info about \"Defeats\" is not found.");
      }
      if (list.contains("Wins")) {
         Wins = list["Wins"].toInt();
      } else {
         log("Info about \"Wins\" is not found.");
      }
      if (list.contains("PlayedTime")) {
         qint64 elapsedseconds = list["PlayedTime"].toInteger();
         seconds = elapsedseconds;
         hours = seconds / 3600;
         minutes = (seconds % 3600) / 60;
         seconds = seconds % 60;
         ui->labelPlayedTime->setText(setTime(hours, minutes, seconds));
      } else {
         log("Info about \"PlayedTime\" is not found.");
      }

      //Settings
      if (list.contains("WatchAllField")) {
         ui->checkBoxWatchAllField->setChecked(list["WatchAllField"].toBool());
      } else {
         log("Info about \"WatchAllField\" is not found.");
      }
      if (list.contains("MusicVolume")) {
         MusicVolume = list["MusicVolume"].toDouble();
      } else {
         log("Info about \"MusicVolume\" is not found.");
      }
      if (list.contains("UiVolume")) {
         UiVolume = list["UiVolume"].toDouble();
      } else {
         log("Info about \"UiVolume\" is not found.");
      }
      if (list.contains("UncorrectFlags")) {
         uncorrectFlags = list["UncorrectFlags"].toInt();
      } else {
         log("Info about \"UncorrectFlags\" is not found.");
      }
      if (list.contains("DefusedBombs")) {
         defusedCounter = list["DefusedBombs"].toInt();
      } else {
         log("Info about \"DefusedBombs\" is not found.");
      }

      ui->SliderMusicVolume->setSliderPosition(MusicVolume * 100);
      ui->SliderUiVolume->setSliderPosition(UiVolume * 100);
      ui->labelDefusedCouner->setText(QString::number(defusedCounter));
      ui->labelUncorrectFlagsCounter->setText(QString::number(uncorrectFlags));
   } else {
      log("Try to load. Data file is gone. Creating new...");
   }

   saveData();
}
QString WelcomeWindow::setTime(int h, int m, int s)
{
   QStringList timeParts;
   const char *units[][3] = {{"час", "часа", "часов"}, {"минута", "минуты", "минут"}, {"секунда", "секунды", "секунд"}};

   int times[] = {h, m, s};

   for (int i = 0; i < 3; ++i) {
      if (times[i] != 0) {
         int form = 2;
         if (times[i] % 10 == 1 && times[i] % 100 != 11) {
            form = 0;
         } else if (times[i] % 10 >= 2 && times[i] % 10 <= 4 && (times[i] % 100 < 12 || times[i] % 100 > 14)) {
            form = 1;
         }
         timeParts << QString("%1 %2").arg(times[i]).arg(units[i][form]);
      }
   }

   QString time = timeParts.join(" ");
   if (time.isEmpty()) {
      time = "0 секунд";
   }

   ui->labelPlayedTime->setText(time);
   return time;
}
void WelcomeWindow::log(const QString &message)
{
   qDebug() << message;
   QDateTime currentTime = QDateTime::currentDateTime();
   qint64 elapsedMilliseconds = startTime.msecsTo(currentTime);
   qint64 seconds = elapsedMilliseconds / 1000;
   qint64 hours = seconds / 3600;
   qint64 minutes = (seconds % 3600) / 60;
   seconds = seconds % 60;
   qint64 milliseconds = elapsedMilliseconds % 1000;

   QTextStream out(logFile);
   out << "[" << QString::number(hours).rightJustified(2, '0') << "h-" << QString::number(minutes).rightJustified(2, '0') << "m-"
       << QString::number(seconds).rightJustified(2, '0') << "s-" << QString::number(milliseconds).rightJustified(3, '0') << "ms] --> " << message
       << "\n";

   out.flush();
}
void WelcomeWindow::closeEvent(QCloseEvent *event)
{
   saveData();
   log("Application closing...");
   timerSec->stop();
   event->accept();
}
void WelcomeWindow::endGame(bool win)
{
   if (win) {
      Wins++;
   } else
      Defeats++;
   GamesCounter++;
   ui->labelAllGames->setText(QString::number(GamesCounter));
   ui->labelDefeats->setText(QString::number(Defeats));
   ui->labelWins->setText(QString::number(Wins));
   if (win)
      log("Game End result - Win");
   else
      log("Game End result - Defeat");
   saveData();
   double g = GamesCounter;
   double w = Wins;
   if (GamesCounter > 0) ui->labelWinsProcents->setText(QString::number((w / g) * 100.0) + "%");
}
WelcomeWindow::~WelcomeWindow()
{
   timerSec->stop();
   delete timerSec;
   delete markerX;
   delete markerY;
   logFile->close();
   delete logFile;
   delete data;
   delete ui;
}
