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
#include <cstdlib> // Для srand и rand
#include <ctime>

GameWindow::GameWindow(WelcomeWindow *parent, int rows, int cols, int mines, QString message)
    : parent(parent)
    , ui(new Ui::GameWindow)
    , rows(rows)
    , cols(cols)
    , mines(mines)
    , message(message)
{
   ui->setupUi(this);
   srand(std::time(NULL));

   ui->lcdNumberBombs->display(mines);
   ui->labelDifficult->setText(message);

   if (createButtonField()) log("Game starts: " + message);

   connect(timerSec, &QTimer::timeout, this, &GameWindow::secTimer);
   timerSec->start(1000);
   connect(minetimer, &QTimer::timeout, this, &GameWindow::updateMineTimer);
}
void GameWindow::leftClick(int x, int y)
{
   // Реализация левого клика
   if (GameEnd == true) return;
   QPixmap currentPixmap = buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize());
   if (currentPixmap.toImage() == flag.toImage()) return;

   if (once) {
      once = false;
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
               if (bombCounter == 0)
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
               if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == unpressed.toImage()) {
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
                  if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == unpressed.toImage()) {
                     if (Field[nx][ny] != 9) {
                        buttons[nx][ny]->setIcon(QIcon(QString(":/images/button_%1.png").arg(Field[nx][ny])));
                        openFieldCounter++;
                        if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == button_0.toImage()) {
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
                        buttons[nx][ny]->setIcon(QIcon(":/images/button_armedbomb.png"));
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
         buttons[x][y]->setIcon(QIcon(QString(":/images/button_%1.png").arg(Field[x][y])));
         if (buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == button_0.toImage()) {
            // Открываем соседние пустые клетки
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
         endGame(false);
      }
   }
   //проверка на победу
   if (rows * cols - mines == openFieldCounter) {
      endGame(true);
      return;
   }
}
void GameWindow::rightClick(int x, int y)
{
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
               if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == unpressed.toImage()) {
                  unpressedCounter++;
               } else if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == flag.toImage()) {
                  flagCounter++;
               }
            }
         }
      }
      int number = 0;
      for (int i = 1; i <= 8; ++i) {
         QPixmap buttonPixmap = QIcon(QString(":/images/button_%1.png").arg(i)).pixmap(QSize(25, 25));
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
                  if (buttons[nx][ny]->icon().pixmap(buttons[x][y]->iconSize()).toImage() == unpressed.toImage()) {
                     ui->lcdNumberMarked->display(ui->lcdNumberMarked->value() + 1);
                     buttons[nx][ny]->setIcon(flag);
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
   qint64 lastseconds = ((parent->hours * 60) + parent->minutes) * 60 + parent->seconds;
   int h = time / 3600;
   int m = (time % 3600) / 60;
   int s = time % 60;
   if (win) {
      if (ui->labelDifficult->text() == "Easy") {
         if (lastseconds > time) {
            parent->ui->labelEasyRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Medium") {
         if (lastseconds > time) {
            parent->ui->labelMediumRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Hard") {
         if (lastseconds > time) {
            parent->ui->labelHardRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Extreme") {
         if (lastseconds > time) {
            parent->ui->labelExtremeRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      } else if (ui->labelDifficult->text() == "Insane") {
         if (lastseconds > time) {
            parent->ui->labelInsaneRecord->setText(QString("лучшее время: " + parent->setTime(h, m, s)));
         }
      }
   }

   for (int x = 0; x < rows; x++)
      for (int y = 0; y < cols; y++) {
         QPixmap currentPixmap = buttons[x][y]->icon().pixmap(QSize(25, 25));
         if (Field[x][y] == 9 && currentPixmap.toImage() != flag.toImage()) {
            arrsize++;
            arr.push_back(buttons[x][y]);
         } else if (currentPixmap.toImage() == flag.toImage() && Field[x][y] == 9) {
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
      minetimer->start(interval);
   }
   ui->btn_exit->setText("Закрыть");
   parent->endGame(win);
}
void GameWindow::updateMineTimer()
{
   if (arrsize <= 0) {
      if (parent->ui->checkBoxWatchAllField->isChecked()) {
         for (int x = 0; x < rows; x++)
            for (int y = 0; y < cols; y++) {
               if (Field[x][y] >= 0 && Field[x][y] <= 8) buttons[x][y]->setIcon(QIcon(QString(":/images/button_%1.png").arg(Field[x][y])));
            }
      }
      minetimer->stop();
      return;
   }
   int u = rand() % arrsize;

   //bombsound->stop();
   //bombsound->play();

   arr[u]->setIcon(armedbomb);

   if (u >= 0 && u < arr.size()) {
      arr.erase(arr.begin() + u);
   }
   arrsize--;
   int decrement;
   if (arrsize > 0) {
      int decreaseFactor = 10; // Можете настроить этот коэффициент
      int newInterval = interval - (decreaseFactor * (1000 - arrsize) / 100);
      if (intervalCounter == 40) minInterval = 10;
      interval = qMax(minInterval, newInterval);
      minetimer->setInterval(interval);
      if (interval == minInterval && intervalCounter < 50) intervalCounter++;
      // Логирование нового интервала
      log(QString("newInterval = %1").arg(interval));
   }
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
   timerSec->stop();
   minetimer->stop();
   log("Game closing...");
   parent->saveData();
   event->accept();
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
   delete[] Field;
   delete ui;
}
