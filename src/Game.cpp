#include "GameWindow.h"
#include "ui_Game.h"
#include "ui_Welcome.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDateTime>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QScreen>
#include <QTimer>
#include <QToolButton>
#include <QTransform>
#include <QUrl>
#include <cstdlib>
#include <ctime>
#include <queue>

GameWindow::GameWindow(WelcomeWindow *parent, int rows, int cols, int mines, QString message)
    : parent(parent)
    , ui(new Ui::GameWindow)
    , rows(rows)
    , cols(cols)
    , mines(mines)
    , message(message)
{
   parent->volumeDown();
   ui->setupUi(this);
   srand(std::time(NULL));

   ui->lcdNumberBombs->display(mines);
   ui->labelDifficult->setText(message);

   if (createButtonField()) log("Game starts: " + message);

   connect(timerSec, &QTimer::timeout, this, &GameWindow::secTimer);
   timerSec->start(1000);

   //Звук
   // Фоновая музыка
   audioOutput->setVolume(parent->MusicVolume);
   background->setAudioOutput(audioOutput);
   int i = rand() % 48;
   background->setSource(sources[i]);
   connect(background, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
      if (status == QMediaPlayer::EndOfMedia) {
         // Получаем текущий источник
         QUrl currentSource = background->source();
         // Находим индекс текущего источника
         auto it = std::find(sources.begin(), sources.end(), currentSource);
         // Если текущий источник найден и не последний в списке
         if (it != sources.end() && (it + 1) != sources.end()) {
            background->setSource(*(it + 1)); // Устанавливаем следующий источник
         } else {
            background->setSource(sources[0]); // Переключаем на первый источник, если достигнут конец
         }
         log(QString("Music auto-changed from %1 to %2").arg(currentSource.toString(), background->source().toString())); // Преобразуем QUrl в QString
         background->play(); // Запускаем воспроизведение
      }
   });
   background->play(); // Запускаем воспроизведение

   // Звуки интерфейса
   soundUi->setAudioOutput(audioOutputUi);
   audioOutputUi->setVolume(parent->UiVolume);
   connect(ui->btn_exit, &QToolButton::clicked, this, [=] {
      soundUi->setSource(soundClicked);
      soundUi->play();
   });
}
void GameWindow::leftClick(int x, int y)
{
   if (GameEnd == true) return;

   // Звуки интерфейса
   if (buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize()).toImage() != button_0.toImage()) {
      soundUi->setSource(soundClicked);
      soundUi->play();
   } else
      return;

   // Реализация левого клика
   QPixmap currentPixmap = buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize());
   if (currentPixmap.toImage() == flag.toImage()) return;

   if (onceField) {
      onceField = false;
      int startx = x;
      int starty = y;
      short int counter = 0;
      // Генерация мин
      while (counter < mines) {
         short int x = rand() % rows;
         short int y = rand() % cols;
         // Проверяем, что клетка не является миной, не является точкой старта
         // и не находится рядом с точкой старта
         if (Field[x][y] != 9 && (startx != x || starty != y)) {
            bool isAdjacentToStart = false;

            // Массив смещений для проверки соседних клеток
            const int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

            // Проверяем соседние клетки
            for (const auto &offset : offsets) {
               int ni = startx + offset[0];
               int nj = starty + offset[1];
               if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && ni == x && nj == y) {
                  isAdjacentToStart = true;
                  break;
               }
            }

            // Если клетка не соседняя, то ставим мину
            if (!isAdjacentToStart) {
               Field[x][y] = 9;
               counter++;
            }
         }
      }

      // Дальше генерим цифры
      for (int i = 0; i < rows; i++) {
         QString row;
         for (int j = 0; j < cols; j++) {
            if (Field[i][j] != 9) { // Если это не мина
               short int bombCounter = 0;

               // Массив смещений для проверки соседей
               const int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

               // Проверяем соседние ячейки
               for (const auto &offset : offsets) {
                  int ni = i + offset[0];
                  int nj = j + offset[1];
                  if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && Field[ni][nj] == 9) {
                     bombCounter++;
                  }
               }
               Field[i][j] = bombCounter; // Устанавливаем количество бомб вокруг
               row += QString("[%1]").arg(Field[i][j]);
            } else {
               row += "[*]";
            }
         }
         log(row);
      }
   }

   QVector<QPixmap> buttonPixmaps = {button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8};
   bool matchFound = false;
   int number = 1;
   for (const auto &pixmap : buttonPixmaps) {
      if (currentPixmap.toImage() == pixmap.toImage()) {
         matchFound = true;
         break;
      } else
         number++;
   }

   if (matchFound) {
      log("Left click on number");
      int flagCounter = 0;
      int unpressedCounter = 0;
      for (int dx = -1; dx <= 1; dx++) {
         for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
               if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == unpressed.toImage()
                   || buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == question.toImage()) {
                  unpressedCounter++;
               } else if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == flag.toImage()) {
                  flagCounter++;
               }
            }
         }
      }
      QString BoolMessage = "false";
      if (number == flagCounter) BoolMessage = "true";
      log(QString("number(%1) == flags(%3) == %4").arg(number).arg(flagCounter).arg(BoolMessage));
      if (number == flagCounter) {
         for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
               int nx = x + dx;
               int ny = y + dy;
               if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                  if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == unpressed.toImage()
                      || buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == question.toImage()) {
                     if (Field[nx][ny] != 9) {
                        buttons[nx][ny]->setIcon(QIcon(QString(":/images/Pictures/button_%1.png").arg(Field[nx][ny])));
                        openFieldCounter++;
                        if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == button_0.toImage()) {
                           //Отключение видимости нажатия на кнопку
                           buttons[nx][ny]->setStyleSheet(R"(
                              QToolButton {
                                 background-color: #808080;
                                 border: none;
                              }
                              QToolButton:pressed {
                                 border: none;
                                 padding: 0px;
                                 margin: 0px;
                              }
                           )");
                           // Открываем соседние клетки
                           for (int d2x = -1; d2x <= 1; d2x++) {
                              for (int d2y = -1; d2y <= 1; d2y++) {
                                 int n2x = nx + d2x;
                                 int n2y = ny + d2y;
                                 if (n2x >= 0 && n2x < rows && n2y >= 0 && n2y < cols) {
                                    leftClick(n2x, n2y);
                                 }
                              }
                           }
                        }
                     } else {
                        buttons[nx][ny]->setIcon(QIcon(":/images/Pictures/button_armedbomb.png"));
                        deadCellx = x;
                        deadCelly = y;
                        endGame(false);
                     }
                  }
               }
            }
         }
      }
   } else if (currentPixmap.toImage() == unpressed.toImage()) {
      log(QString("Open cell x%1y%2 value = %3").arg(x).arg(y).arg(Field[x][y]));
      if (Field[x][y] != 9) {
         openFieldCounter++;
         buttons[x][y]->setIcon(QIcon(QString(":/images/Pictures/button_%1.png").arg(Field[x][y])));
         if (buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == button_0.toImage()) {
            //Отключение видимости нажатия на кнопку
            buttons[x][y]->setStyleSheet(R"(
            QToolButton {
               background-color: #808080;
               border: none;
               }
               QToolButton:pressed {
                  border: none;
                  padding: 0px;
                  margin: 0px;
               }
            )");
            // Открываем соседние клетки
            for (int dx = -1; dx <= 1; dx++) {
               for (int dy = -1; dy <= 1; dy++) {
                  int nx = x + dx;
                  int ny = y + dy;
                  if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                     QPixmap cellPixmap = buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize());
                     if (cellPixmap.toImage() == unpressed.toImage()) {
                        leftClick(nx, ny);
                     }
                  }
               }
            }
         }
      } else {
         buttons[x][y]->setIcon(armedbomb);
         deadCellx = x;
         deadCelly = y;
         endGame(false);
      }
   }
   //проверка на победу
   if (rows * cols - mines == openFieldCounter) {
      endGame(true);
   }
}
void GameWindow::rightClick(int x, int y)
{
   if (GameEnd == true) return;

   // Звуки интерфейса
   if (buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize()).toImage() != button_0.toImage()) {
      soundUi->setSource(soundClicked);
      soundUi->play();
   } else
      return;

   // Реализация правого клика
   QPixmap currentPixmap = buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize());
   QVector<QPixmap> buttonPixmaps = {button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8};
   bool matchFound = false;

   for (const auto &pixmap : buttonPixmaps) {
      if (currentPixmap.toImage() == pixmap.toImage()) {
         matchFound = true;
         break;
      }
   }

   if (matchFound) {
      log("Right click on number");
      int flagCounter = 0;
      int unpressedCounter = 0;
      for (int dx = -1; dx <= 1; dx++) {
         for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
               if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()
                   || buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == question.toImage()) {
                  unpressedCounter++;
               } else if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == flag.toImage()) {
                  flagCounter++;
               }
            }
         }
      }
      int number = 0;
      for (int i = 1; i <= 8; ++i) {
         QPixmap buttonPixmap = QIcon(QString(":/images/Pictures/button_%1.png").arg(i)).pixmap(QSize(25, 25));
         if (currentPixmap.toImage() == buttonPixmap.toImage()) {
            number = i;
            break;
         }
      }
      QString BoolMessage = "false";
      if (number == unpressedCounter + flagCounter) BoolMessage = "true";
      log(QString("number(%1) == unpressed(%2) + flags(%3) == %4").arg(number).arg(unpressedCounter).arg(flagCounter).arg(BoolMessage));
      if (number == unpressedCounter + flagCounter) {
         for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
               int nx = x + dx;
               int ny = y + dy;
               if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                  if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()
                      || buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == question.toImage()) {
                     ui->lcdNumberMarked->display(ui->lcdNumberMarked->value() + 1);
                     buttons[nx][ny]->setIcon(flag);
                     buttons[nx][ny]->setStyleSheet(R"(
                        QToolButton {
                           background-color: #808080;
                           border: none;
                        }
                        QToolButton:pressed {
                           padding: 0px;
                           margin: 0px;
                        }
                     )");
                  }
               }
            }
         }
      }
   } else if (currentPixmap.toImage() == unpressed.toImage()) {
      ui->lcdNumberMarked->display(ui->lcdNumberMarked->value() + 1);
      buttons[x][y]->setIcon(flag);
      buttons[x][y]->setStyleSheet(R"(
         QToolButton {
            background-color: #808080;
            border: none;
         }
         QToolButton:pressed {
            padding: 0px;
            margin: 0px;
         }
         )");
      log(QString("set flag on x%1y%2").arg(x).arg(y));
   } else if (currentPixmap.toImage() == flag.toImage()) {
      ui->lcdNumberMarked->display(ui->lcdNumberMarked->value() - 1);
      buttons[x][y]->setIcon(question);
      log(QString("set question on x%1y%2").arg(x).arg(y));
   } else if (currentPixmap.toImage() == question.toImage()) {
      buttons[x][y]->setIcon(unpressed);
      buttons[x][y]->setStyleSheet(R"(
         QToolButton {
            background-color: #808080;
            border: none;
         }
         QToolButton:pressed {
            padding-top: 1px;
            padding-left: 1px;
            margin-bottom: -1px;
            margin-right: -1px;
         }
         )");
      log(QString("remove question on x%1y%2").arg(x).arg(y));
   }
}
void GameWindow::endGame(bool win)
{
   log("EndGame");
   GameEnd = true;
   timerSec->stop(); // Останавливаем таймер
   ui->labelStaticTime->setText("Итого:");
   int h = time / 3600;
   int m = (time % 3600) / 60;
   int s = time % 60;

   //Отключение видимости нажатия на кнопку
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
         buttons[i][j]->setStyleSheet(R"(
            QToolButton {
               background-color: #808080;
               border: none;
            }
            QToolButton:pressed {
               padding: 0px;
               margin: 0px;
            }
         )");
      }
   }
   //Обновление статистики
   parent->endGame(win);
   for (int x = 0; x < rows; x++)
      for (int y = 0; y < cols; y++) {
         QPixmap currentPixmap = buttons[x][y]->icon().pixmap(QSize(25, 25));
         if (currentPixmap.toImage() == flag.toImage() && Field[x][y] == 9) {
            buttons[x][y]->setIcon(defusedbomb);
            parent->defusedCounter++;
            parent->ui->labelDefusedCouner->setText(QString::number(parent->defusedCounter));
         } else if (currentPixmap.toImage() == flag.toImage()) {
            buttons[x][y]->setEnabled(false);
            parent->uncorrectFlags++;
            parent->ui->labelUncorrectFlagsCounter->setText(QString::number(parent->uncorrectFlags));
         }
      }
   if (win) {
      if (ui->labelDifficult->text() == "Easy") {
         if (parent->decryptTime(parent->ui->labelEasyRecord->text()) > time) {
            parent->ui->labelEasyRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Medium") {
         if (parent->decryptTime(parent->ui->labelMediumRecord->text()) > time) {
            parent->ui->labelMediumRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Hard") {
         if (parent->decryptTime(parent->ui->labelHardRecord->text()) > time) {
            parent->ui->labelHardRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Extreme") {
         if (parent->decryptTime(parent->ui->labelExtremeRecord->text()) > time) {
            parent->ui->labelExtremeRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Insane") {
         if (parent->decryptTime(parent->ui->labelInsaneRecord->text()) > time) {
            parent->ui->labelInsaneRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      }

      //Обновление интерфейса
      ui->btn_exit->setText("Закрыть");
      ui->btn_exit->setStyleSheet(R"(QPushButton {
         background-color: #4CAF50;
         border-radius:4px;
         color: white;
      }
      QPushButton:hover {
         background-color: #45a049; 
      }
      QPushButton:pressed {
         background-color: #388e3c;
      })");
      for (int x = 0; x < rows; x++) {
         for (int y = 0; y < cols; y++) {
            QPixmap currentPixmap = buttons[x][y]->icon().pixmap(QSize(25, 25));
            if (Field[x][y] == 9 && currentPixmap.toImage() != defusedbomb.toImage()) {
               buttons[x][y]->setIcon(defusedbomb);
               parent->defusedCounter++;
               parent->ui->labelDefusedCouner->setText(QString::number(parent->defusedCounter));
            }
         }
      }
   } else {
      minesExplosion();
   }
}
void GameWindow::minesExplosion()
{
   log("Explosion started");

   // Устанавливаем интервал и запускаем таймер
   explosionTimer->setInterval(interval);
   explosionTimer->start();

   // Начинаем с начальной точки
   queue.push(QPoint(deadCellx, deadCelly));
   visited.push_back(QPoint(deadCellx, deadCelly));

   connect(explosionTimer, &QTimer::timeout, this, [this]() {
      // Открываем клетки в круговом радиусе
      int cellsOpenedLocal = 0; // Счётчик открытых клеток

      for (int dx = -currentRadius; dx <= currentRadius; dx++) {
         for (int dy = -currentRadius; dy <= currentRadius; dy++) {
            // Проверяем, находится ли точка в круге
            if (dx * dx + dy * dy <= currentRadius * currentRadius) {
               int newX = deadCellx + dx; // Используем начальную точку
               int newY = deadCelly + dy;

               // Проверяем границы
               if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                  QPoint neighbor(newX, newY);
                  // Проверяем, была ли клетка уже открыта
                  if (std::find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                     visited.push_back(neighbor); // Добавляем в посещенные
                     queue.push(neighbor);        // Добавляем в очередь

                     // Открываем клетку
                     if (Field[newX][newY] != 9) {
                        if (parent->ui->checkBoxWatchAllField->isChecked()) {
                           if (buttons[newX][newY]->isEnabled())
                              buttons[newX][newY]->setIcon(QIcon(QString(":/images/Pictures/button_%1.png").arg(Field[newX][newY])));
                        }
                     } else {
                        if (buttons[newX][newY]->icon().pixmap(buttons[newX][newY]->iconSize()).toImage() != defusedbomb.toImage())
                           buttons[newX][newY]->setIcon(armedbomb);
                     }
                     cellsOpenedLocal++;
                     cellsOpenedGlobal++;
                  }
               }
            }
         }
      }

      // Увеличиваем радиус только если были открыты клетки
      if (cellsOpenedLocal > 0) {
         currentRadius++;
      }

      if (cellsOpenedGlobal == cols * rows) {
         log("Cells out. Stop exploding");
         // Останавливаем таймер
         explosionTimer->stop();
      }
   });
}
void GameWindow::secTimer()
{
   time++;
   int h = time / 3600;
   int m = (time % 3600) / 60;
   int s = time % 60;
   ui->labelTime->setText(parent->setTime(h, m, s));
}
void GameWindow::resizeEvent(QResizeEvent *event)
{
   QWidget::resizeEvent(event);
   if (onceResize) {
      onceResize = false;
      this->setMinimumWidth(ui->groupBoxGameField->width() + 18);
   }

   const QSize fieldSize = ui->groupBoxGameField->size();
   const int centerX = fieldSize.width() / 2;
   const int centerY = fieldSize.height() / 2;
   const int startX = centerX - (12.5 * cols);
   const int startY = centerY - (12.5 * rows);

   for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
         buttons[i][j]->setGeometry(startX + j * 25, startY + i * 25, 25, 25);
      }
   }
}
void GameWindow::closeEvent(QCloseEvent *event)
{
   background->stop();
   timerSec->stop();
   explosionTimer->stop();
   log("Game closing...");
   if (GameEnd == false) parent->endGame(false);
   parent->saveData();

   this->hide();   // Скрываем текущее окно
   parent->show(); // Показываем родительское окно
   parent->volumeUp();
   event->accept(); // Позволяет окну закрыться
}
bool GameWindow::createButtonField()
{
   Field = new short int *[rows];
   buttons.resize(rows);

   for (int i = 0; i < rows; i++) {
      Field[i] = new short int[cols]();
      buttons[i].resize(cols);
      for (int j = 0; j < cols; j++) {
         buttons[i][j] = new QToolButton(ui->groupBoxGameField);
         buttons[i][j]->setCursor(Qt::PointingHandCursor);
         buttons[i][j]->setContextMenuPolicy(Qt::CustomContextMenu);
         buttons[i][j]->setStyleSheet(R"(
         QToolButton {
            background-color: #808080;
            border: none;
         }
         QToolButton:pressed {
            border: none;
            padding-top: 1px;
            padding-left: 1px;
            margin-bottom: -1px;
            margin-right: -1px;
         }
         )");

         buttons[i][j]->setIconSize(QSize(25, 25));
         buttons[i][j]->setFixedSize(25, 25);
         buttons[i][j]->setIcon(unpressed);
         connect(buttons[i][j], &QToolButton::clicked, this, [this, i, j]() { leftClick(i, j); });
         connect(buttons[i][j], &QToolButton::customContextMenuRequested, this, [this, i, j]() { rightClick(i, j); });
      }
   }
   ui->groupBoxGameField->setGeometry(ui->groupBoxGameField->x(), ui->groupBoxGameField->y(), 623 - 16, 314 - 63);
   return true;
}

GameWindow::~GameWindow()
{
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
         delete buttons[i][j];
      }
      delete[] Field[i];
   }
   delete explosionTimer;
   delete timerSec;
   delete[] Field;
   delete ui;
}
