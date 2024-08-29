#include "GameWindow.h"
#include "ui_Game.h"

#include <QApplication>
#include <QCloseEvent>
#include <QPushButton>
#include <QScreen>
#include <QTimer>
#include <QToolButton>

GameWindow::GameWindow(WelcomeWindow *parent, int rows, int cols, int mines, QString message)
    : parent(parent)
    , ui(new Ui::GameWindow)
    , rows(rows)
    , cols(cols)
    , mines(mines)
    , message(message)
{
   ui->setupUi(this);
   ui->lcdNumberBombs->display(mines);
   ui->labelDifficult->setText(message);
   if (createButtonField()) log("Game starts: " + message);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
   qDebug() << "Resize";
   QWidget::resizeEvent(event);
   if (onceResize) {
      onceResize = false;
      this->setMinimumWidth(ui->groupBoxGameField->width() + 18);
   }

   const int width = ui->groupBoxGameField->width();
   const int height = ui->groupBoxGameField->height();
   const int centerX = width / 2;
   const int centerY = height / 2;
   const int startX = centerX - (25 * cols / 2);
   const int startY = centerY - (25 * rows / 2);

   for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
         buttons[i][j]->setGeometry(startX + j * 25, startY + i * 25, 25, 25);
      }
   }
}
void GameWindow::closeEvent(QCloseEvent *event)
{
   log("Game closing...");
   parent->saveData();
   event->accept();
}

bool GameWindow::createButtonField()
{
   Field = new short int *[rows];
   for (int i = 0; i < rows; i++) {
      Field[i] = new short int[cols];
      for (int j = 0; j < cols; j++) {
         Field[i][j] = 0;
      }
   }
   int counter = 0;
   buttons.resize(rows);
   for (int i = 0; i < rows; i++) {
      buttons[i].resize(cols);
      for (int j = 0; j < cols; j++) {
         counter++;
         buttons[i][j] = new QToolButton(ui->groupBoxGameField);
         buttons[i][j]->setCursor(Qt::PointingHandCursor);
         buttons[i][j]->setStyleSheet("QToolButton { background-color:#ffffff; border: none; }");
         buttons[i][j]->setIconSize(QSize(25, 25));
         buttons[i][j]->setFixedSize(25, 25);
         buttons[i][j]->setIcon(unpressed);
      }
   }
   ui->groupBoxGameField->setGeometry(ui->groupBoxGameField->x(), ui->groupBoxGameField->y(), 514, 314 - 63);
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
