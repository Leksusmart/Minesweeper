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
   if (message == "Training") {
      isTraining = true;
      srand(0);
      initializeTutorial();
      nextTutorialStep();
   }
   ui->lcdNumberBombs->display(mines);
   ui->labelDifficult->setText(message);
   if (createButtonField()) log("Game starts: " + message);

   connect(timerSec, &QTimer::timeout, this, &GameWindow::secTimer);
   timerSec->start(1000);
   connect(minetimer, &QTimer::timeout, this, &GameWindow::updateMineTimer);
}
void GameWindow::initializeTutorial()
{
   log("initializeTutorial1");
   tutorialArrow = new QLabel(this);
   tutorialArrow2 = new QLabel(this);
   QTransform transform;
   transform.rotate(90);
   arrow.load(":/images/tutorial_arrow.png");
   rightArrow = arrow.transformed(transform);
   transform.rotate(180);
   leftArrow = arrow.transformed(transform);

   tutorialArrow->setPixmap(QPixmap::fromImage(arrow));
   tutorialArrow->setFixedSize(30, 31);
   tutorialArrow->hide();
   tutorialArrow2->hide();
   borderl = new QLabel(this);
   borderu = new QLabel(this);
   borderr = new QLabel(this);
   borderd = new QLabel(this);
   borderl->setStyleSheet("background-color: orange;");
   borderu->setStyleSheet("background-color: orange;");
   borderr->setStyleSheet("background-color: orange;");
   borderd->setStyleSheet("background-color: orange;");
   borderl->setFixedSize(6, 87);
   borderu->setFixedSize(87, 6);
   borderr->setFixedSize(6, 87);
   borderd->setFixedSize(87, 6);
   borderl->hide();
   borderu->hide();
   borderr->hide();
   borderd->hide();
   log("initializeTutorial2");
   tutorialText = new QLabel(this);
   tutorialText->setStyleSheet("color:black;background-color: white; border: 1px solid black;");
   tutorialText->setWordWrap(true);
   tutorialText->hide();
   log("initializeTutorial3");
   tutorialStep = -1;

   hightLight = new QLabel(this);
   hightLight->setStyleSheet("QLabel { background-color: transparent; border: 6px solid orange; }");
   hightLight->hide();
}
void GameWindow::nextTutorialStep()
{
   tutorialStep++;
   log(QString("current tutorial step is %1").arg(tutorialStep));
   QVector<QPixmap> buttonPixmaps = {button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8};
   short int foundx = NULL;
   short int foundy = NULL;
   switch (tutorialStep) {
   case 0:
      tutorialText->show();
      tutorialText->setFixedSize(160, 70);
      tutorialText->setText("Добро пожаловать в обучение игре 'Сапер'! Давайте начнем с основ.");
      tutorialText->move(this->rect().center() - tutorialText->rect().center());
      tutorialText->show();
      break;
   case 1:
      // Показать lcdNumberBombs
      tutorialArrow->show();
      tutorialArrow->move(ui->lcdNumberBombs->mapTo(this, QPoint(40, 35)));
      tutorialText->setFixedSize(140, 50);
      tutorialText->setText("Это счетчик бомб. Он показывает, сколько бомб предстоит найти.");
      tutorialText->move(tutorialArrow->pos() + QPoint(-1 * tutorialText->width() / 2 + 15, 31));
      break;
   case 2:
      // Показать lcdNumberMarked
      tutorialArrow->move(ui->lcdNumberMarked->mapTo(this, QPoint(40, 35)));
      tutorialText->setFixedSize(160, 70);
      tutorialText->setText("Это счетчик отмеченных клеток. Он показывает, сколько клеток вы отметили флажками.");
      tutorialText->move(tutorialArrow->pos() + QPoint(-1 * tutorialText->width() / 2, 31));
      break;
   case 3:
      // Показать labelTime
      tutorialArrow->move(ui->labelTime->mapTo(this, QPoint(10, 15)));
      tutorialText->setText("Здесь отображается время с начала игры.");
      tutorialText->setFixedSize(120, 50);
      tutorialText->move(tutorialArrow->pos() + QPoint(-1 * tutorialText->width() / 2, 31));
      break;
   case 4:
      // Показать поле (В общем плане, что это игровое поле)
      tutorialArrow->setPixmap(QPixmap::fromImage(rightArrow));
      tutorialArrow->setFixedSize(31, 30);
      tutorialArrow->move(buttons[1][0]->mapTo(this, QPoint(-40, 13)));
      tutorialText->setText("Это игровое поле. Здесь скрыты мины, которые вам нужно найти.");
      tutorialText->setFixedSize(140, 50);
      tutorialText->move(tutorialArrow->pos() + QPoint(-1 * tutorialText->width(), -1 * tutorialText->height() / 2 + 15));
      hightLight->show();
      hightLight->setFixedSize(162, 112);
      hightLight->move(buttons[0][0]->mapTo(this, QPoint(-6, -6)));
      break;
   case 5:
      // Рассказать цель игры
      hightLight->hide();
      tutorialArrow->hide();
      tutorialText->setText(
         "Ваша цель - открыть все клетки, не содержащие мины. Первое открытие всегда безопасноe. Нажмите на клетку, чтобы начать игру.");
      tutorialText->setFixedSize(300, 60);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 80));

      borderl->move(buttons[1][4]->mapTo(this, QPoint(-31, -31)));
      borderu->move(borderl->mapTo(this, QPoint(0, 0)));
      borderr->move(borderl->mapTo(this, QPoint(81, 0)));
      borderd->move(borderl->mapTo(this, QPoint(0, 81)));

      borderl->show();
      borderu->show();
      borderr->show();
      borderd->show();
      break;
   case 6:
      // Этот шаг будет вызван после первого клика пользователя
      // Показать ячейки с цифрами, рассказать о них
      borderl->hide();
      borderu->hide();
      borderr->hide();
      borderd->hide();
      tutorialText->setText("Отлично! Теперь вы видите числа. Они показывают, сколько мин находится рядом с этой клеткой. Используйте эту "
                            "информацию, чтобы определить, где могут быть мины. (Кликните, чтобы посмотреть пример)");
      tutorialText->setFixedSize(320, 70);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 80));
      break;
   case 7:
      for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++) {
            if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() != unpressed.toImage()) {
               QPixmap currentPixmap = buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize());
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
                  log("Training found number");
                  int unpressedCounter = 0;
                  short int all = 0;
                  for (int dx = -1; dx <= 1; dx++) {
                     for (int dy = -1; dy <= 1; dy++) {
                        int nx = i + dx;
                        int ny = j + dy;
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                           all++;
                           if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()) {
                              unpressedCounter++;
                           }
                        }
                     }
                  }
                  QString BoolMessage = "false";
                  if (number == unpressedCounter) BoolMessage = "true";
                  log(QString("number(%1) == unpressedCounter(%3) == %4").arg(number).arg(unpressedCounter).arg(BoolMessage));
                  if (number == unpressedCounter && all == 9) {
                     foundx = i;
                     foundy = j;
                     num = number;
                     goto found;
                  } else if (number == unpressedCounter) {
                     foundx = i;
                     foundy = j;
                     num = number;
                  }
               }
            }
         }
      }
   found:
      if (foundx != NULL) {
         if (num == 1)
            tutorialText->setText(
               QString(
                  "Например, в этой клетке написано %1 - это значит что рядом с ней в радиусе 3x3 есть %1 мина. Отметьте эту мину флажком, чтобы "
                  "знать что она тут есть и случайно не нажать на неё.\nДля этого щёлкните правым щелчком мыши по клетке 1 раз или можете "
                  "кликнуть (правым щелчком) по цифре.")
                  .arg(num));
         else if (num < 5)
            tutorialText->setText(
               QString(
                  "Например, в этой клетке написано %1 - это значит что рядом с ней в радиусе 3x3 есть %1 мины. Отметьте эти мины флажком, чтобы "
                  "знать что они тут есть и случайно не нажать на них.\nДля этого щёлкните правым щелчком мыши по 1 разу на клетку или можете "
                  "кликнуть (правым щелчком) по цифре.")
                  .arg(num));
         else
            tutorialText->setText(
               QString("Например, в этой клетке написано %1 - это значит что рядом с ней в радиусе 3x3 есть %1 мин. Отметьте эти мины флажком, чтобы "
                       "знать что они тут есть и случайно не нажать на них.\nДля этого щёлкните правым щелчком мыши по 1 разу на клетку или можете "
                       "кликнуть (правым щелчком) по цифре.")
                  .arg(num));
         tutorialText->setFixedSize(430, 80);
         tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 86));

         borderl->move(buttons[foundx][foundy]->mapTo(this, QPoint(-31, -31)));
         borderu->move(borderl->mapTo(this, QPoint(0, 0)));
         borderr->move(borderl->mapTo(this, QPoint(81, 0)));
         borderd->move(borderl->mapTo(this, QPoint(0, 81)));

         borderl->show();
         borderu->show();
         borderr->show();
         borderd->show();
      } else {
         for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
               if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() != unpressed.toImage()) {
                  QPixmap currentPixmap = buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize());
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
                     if (number == 1) {
                        log("Training found number secondTry");
                        int unpressedCounter = 0;
                        for (int dx = -1; dx <= 1; dx++) {
                           for (int dy = -1; dy <= 1; dy++) {
                              int nx = i + dx;
                              int ny = j + dy;
                              if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                                 if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()) {
                                    unpressedCounter++;
                                 }
                              }
                           }
                        }
                        QString BoolMessage = "false";
                        if (number + 1 == unpressedCounter) BoolMessage = "true";
                        log(QString("number(1) + 1 == unpressedCounter(%3) == %4").arg(number).arg(unpressedCounter).arg(BoolMessage));
                        if (number + 1 == unpressedCounter) {
                           foundx = i;
                           foundy = j;
                           num = number;
                        }
                     }
                  }
               }
            }
         }
         tutorialText->setText("Например, у этой единички рядом две клетки. Мы не можем знать наверняка в какой клетке бомба, но она точно в одной "
                               "из них. Пометьте их знаком вопроса, щёлкнув по клеткам 2 раза правой кнопрой мыши.");
         tutorialText->setFixedSize(330, 70);
         tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 86));

         borderl->setStyleSheet("background-color: orange;");
         borderu->setStyleSheet("background-color: orange;");
         borderr->setStyleSheet("background-color: orange;");
         borderd->setStyleSheet("background-color: orange;");
         borderl->setFixedSize(6, 87);
         borderu->setFixedSize(87, 6);
         borderr->setFixedSize(6, 87);
         borderd->setFixedSize(87, 6);

         borderl->move(buttons[foundx][foundy]->mapTo(this, QPoint(-31, -31)));
         borderu->move(borderl->mapTo(this, QPoint(0, 0)));
         borderr->move(borderl->mapTo(this, QPoint(81, 0)));
         borderd->move(borderl->mapTo(this, QPoint(0, 81)));

         borderl->show();
         borderu->show();
         borderr->show();
         borderd->show();
         secondTry = true;
      }

      break;
   case 8:
      // Этот шаг будет вызван после того, как пользователь поставит флажок
      if (num == 1)
         tutorialText->setText("Отлично! Вы отметили предполагаемую клетку с миной. Следуя такому правилу продолжайте помечать мины.");
      else
         tutorialText->setText("Отлично! Вы отметили предполагаемые клетки с минами. Следуя такому правилу продолжайте помечать мины.");
      tutorialText->setFixedSize(220, 70);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 76));
      borderl->hide();
      borderu->hide();
      borderr->hide();
      borderd->hide();
      break;
   case 9:
      tutorialText->show();
      tutorialText->setText("У этой мины уже отмечено рядом то количество мин, которое на ней написано. Значит неотмеченные клетки можно открыть.");
      tutorialText->setFixedSize(220, 70);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 76));
      borderl->move(buttons[found2x][found2y]->mapTo(this, QPoint(-31, -31)));
      borderu->move(borderl->mapTo(this, QPoint(0, 0)));
      borderr->move(borderl->mapTo(this, QPoint(81, 0)));
      borderd->move(borderl->mapTo(this, QPoint(0, 81)));

      borderl->show();
      borderu->show();
      borderr->show();
      borderd->show();
      break;
   case 10:
      tutorialArrow->show();
      tutorialArrow->move(ui->lcdNumberBombs->mapTo(this, QPoint(67, 2)));
      tutorialArrow->setPixmap(QPixmap::fromImage(leftArrow));
      tutorialArrow->setFixedSize(30, 31);
      tutorialArrow2->setPixmap(QPixmap::fromImage(arrow));
      tutorialArrow2->setFixedSize(30, 31);
      tutorialArrow2->show();
      tutorialArrow2->move(ui->lcdNumberMarked->mapTo(this, QPoint(40, 35)));

      tutorialText->show();
      tutorialText->setText("Бывают такие ситуации когда количество мин совпадает с количеством флажков на поле. Если вы верно расставляли "
                            "флажки, то можете спокойно открыть все неоткрытые клетки. Иначе вы проиграете.");
      tutorialText->setFixedSize(330, 70);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 86));
      break;
   case 11:
      for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++) {
            if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() != unpressed.toImage()) {
               QPixmap currentPixmap = buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize());
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
                  if (number == 1) {
                     log("Training found number secondTry");
                     int questionCounter = 0;
                     int unpressedCounter = 0;
                     for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                           int nx = i + dx;
                           int ny = j + dy;
                           if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                              if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == question.toImage()) {
                                 questionCounter++;
                              } else if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()) {
                                 unpressedCounter++;
                              }
                           }
                        }
                     }
                     if (number + unpressedCounter == questionCounter) {
                        foundx = i;
                        foundy = j;
                     }
                  }
               }
            }
         }
      }
      tutorialText->setText("А для этой единички мина находится там же где и для первой, значит можно открыть непомеченную клетку.");
      tutorialText->setFixedSize(200, 70);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 86));

      borderl->move(buttons[foundx][foundy]->mapTo(this, QPoint(-31, -31)));
      borderu->move(borderl->mapTo(this, QPoint(0, 0)));
      borderr->move(borderl->mapTo(this, QPoint(81, 0)));
      borderd->move(borderl->mapTo(this, QPoint(0, 81)));
      break;
   case 12:
      tutorialText->setText("Теперь у двойки можно пометить две мины и убрать сомнения по расположению бомб у единичек.\nПродолжайте игру, используя "
                            "все изученные приемы. Удачи!");
      tutorialText->setFixedSize(300, 70);
      tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 86));

      borderl->move(buttons[1][2]->mapTo(this, QPoint(-31, -31)));
      borderu->move(borderl->mapTo(this, QPoint(0, 0)));
      borderr->move(borderl->mapTo(this, QPoint(81, 0)));
      borderd->move(borderl->mapTo(this, QPoint(0, 81)));
      break;
   }
}
void GameWindow::leftClick(int x, int y)
{
   // Реализация левого клика
   if (GameEnd == true) return;
   QPixmap currentPixmap = buttons[x][y]->icon().pixmap(buttons[x][y]->iconSize());
   if (currentPixmap.toImage() == flag.toImage()) return;

   if (once && message == "Training" && tutorialStep == 5
       && ((x == 1 && y == 0) || (x == 2 && y == 0) || (x == 3 && y == 0) || (x == 2 && y == 1) || (x == 3 && y == 1) || (x == 3 && y == 2)
           || (x == 3 && y == 5)))
      return;
   if (message == "Training" && tutorialStep == 7) return;
   if (message == "Training" && (tutorialStep < 5 || tutorialStep == 6)) {
      nextTutorialStep();
      return;
   }
   if (message == "Training" && (tutorialStep == 8 || tutorialStep == 9)) {
      tutorialText->hide();
      borderl->hide();
      borderu->hide();
      borderr->hide();
      borderd->hide();
   }
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
   if (message == "Training" && tutorialStep == 5) {
      if (onceTraining) {
         onceTraining = false;
         QTimer::singleShot(300, this, &GameWindow::nextTutorialStep);
      }
   }
   if (ui->lcdNumberBombs->value() == ui->lcdNumberMarked->value()) {
      if (tutorialStep != 9) tutorialStep = 9;
      nextTutorialStep();
      return;
   }
   if (message == "Training" && tutorialStep == 11) {
      nextTutorialStep();
      return;
   }
   //проверка на победу
   if (message == "Training" && (tutorialStep == 8 || tutorialStep == 12)) {
      QVector<QPixmap> buttonPixmaps = {button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8};
      for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++) {
            if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() != unpressed.toImage()) {
               QPixmap currentPixmap = buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize());
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
                  int flagCounter = 0;
                  int unpressedCounter = 0;
                  for (int dx = -1; dx <= 1; dx++) {
                     for (int dy = -1; dy <= 1; dy++) {
                        int nx = i + dx;
                        int ny = j + dy;
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                           if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()) {
                              unpressedCounter++;
                           } else if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == flag.toImage()) {
                              flagCounter++;
                           }
                        }
                     }
                  }
                  if (number == flagCounter && unpressedCounter > 0) {
                     found2x = i;
                     found2y = j;
                     if (tutorialStep != 8) tutorialStep = 8;
                     nextTutorialStep();
                     return;
                  }
               }
            }
         }
      }
   }
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

   if (message == "Training" && tutorialStep < 7) {
      return;
   }

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

   if (message == "Training" && tutorialStep == 7 && secondTry == false) {
      short int flaged = 0;
      for (int i = 0; i < rows; i++)
         for (int j = 0; j < cols; j++) {
            if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() == flag.toImage()) flaged++;
         }
      if (num == flaged) {
         nextTutorialStep();
      }
   } else if (message == "Training" && tutorialStep == 7 && secondTry == true) {
      short int questions = 0;
      for (int i = 0; i < rows; i++)
         for (int j = 0; j < cols; j++) {
            if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() == question.toImage()) questions++;
         }
      if (num + 1 == questions) {
         tutorialStep = 10;
         nextTutorialStep();
      }
   }
   if (message == "Training" && ui->lcdNumberBombs->value() == ui->lcdNumberMarked->value()) {
      if (tutorialStep != 9) tutorialStep = 9;
      nextTutorialStep();
   }
}
void GameWindow::mousePressEvent(QMouseEvent *event)
{
   if (message == "Training" && event->button() == Qt::LeftButton && (tutorialStep < 5 || tutorialStep == 6)) {
      nextTutorialStep();
   }
   if (message == "Training" && tutorialStep == 12) {
      tutorialText->hide();
      borderl->hide();
      borderu->hide();
      borderr->hide();
      borderd->hide();
   }
   if (message == "Training" && (tutorialStep == 8 || tutorialStep == 12)) {
      QVector<QPixmap> buttonPixmaps = {button_1, button_2, button_3, button_4, button_5, button_6, button_7, button_8};
      for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++) {
            if (buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize()).toImage() != unpressed.toImage()) {
               QPixmap currentPixmap = buttons[i][j]->icon().pixmap(buttons[i][j]->iconSize());
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
                  int flagCounter = 0;
                  int unpressedCounter = 0;
                  for (int dx = -1; dx <= 1; dx++) {
                     for (int dy = -1; dy <= 1; dy++) {
                        int nx = i + dx;
                        int ny = j + dy;
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                           if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == unpressed.toImage()) {
                              unpressedCounter++;
                           } else if (buttons[nx][ny]->icon().pixmap(buttons[nx][ny]->iconSize()).toImage() == flag.toImage()) {
                              flagCounter++;
                           }
                        }
                     }
                  }
                  if (number == flagCounter && unpressedCounter > 0) {
                     found2x = i;
                     found2y = j;
                     if (tutorialStep != 8) tutorialStep = 8;
                     nextTutorialStep();
                     return;
                  }
               }
            }
         }
      }
   }
   QMainWindow::mousePressEvent(event);
}
void GameWindow::endGame(bool win)
{
   log("EndGame");
   if (tutorialArrow != nullptr) tutorialArrow->hide();
   if (tutorialArrow2 != nullptr) tutorialArrow2->hide();
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
   GameEnd = true;
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
      for (int x = 0; x < rows; x++)
         for (int y = 0; y < cols; y++) {
            QPixmap currentPixmap = buttons[x][y]->icon().pixmap(QSize(25, 25));
            if (Field[x][y] == 9 && currentPixmap.toImage() != defusedbomb.toImage()) {
               buttons[x][y]->setIcon(defusedbomb);
               parent->defusedCounter++;
               parent->ui->labelDefusedCouner->setText(QString::number(parent->defusedCounter));
            }
         }
      if (message == "Training") {
         tutorialText->show();
         tutorialText->setText(
            "Поздравляем! Вы успешно завершили обучение. Теперь вы готовы играть в 'Сапер' самостоятельно! Нажмите кнопку закрыть, чтобы выйти.");
         tutorialText->setFixedSize(300, 60);
         tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 76));
      }

   } else {
      minetimer->start(interval);
      if (message == "Training") {
         tutorialText->show();
         tutorialText->setText("Проигрыш! Надеюсь вы поняли причину своего поражения. В игре 'Сапер' важно быть внимательным и логичным. "
                               "В следующий раз получится! Нажмите кнопку закрыть, чтобы выйти.");
         tutorialText->setFixedSize(300, 68);
         tutorialText->move(this->rect().center() - tutorialText->rect().center() - QPoint(0, 80));
      }
   }

   delete borderl;
   delete borderu;
   delete borderr;
   delete borderd;
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
   if (tutorialText && tutorialText->isVisible()) {
      tutorialText->move(this->rect().center() - tutorialText->rect().center());
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
