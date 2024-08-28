#include "./ui_Welcome.h"
#include "WelcomeWindow.h"

#include <QRegularExpression>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QScrollBar>
#include <QTimer>
#include <QCloseEvent>
WelcomeWindow::WelcomeWindow(QMainWindow *parent) : ui(new Ui::WelcomeWindow)
{
    logFile->open(QIODevice::WriteOnly | QIODevice::Text);
    ui->setupUi(this);
    timerSec->start(1000);
    ui->btn_records->setIcon(QIcon(":/images/cup.png"));
    ui->btn_records->setIconSize(QSize(25, 25));
    ui->btn_settings->setIconSize(QSize(25, 25));
    ui->stackedWidget->hide();
    loadData();

    markerX->setFixedSize(2, 20);
    markerX->setStyleSheet("background-color: black;");
    markerY->setFixedSize(21, 2);
    markerY->setStyleSheet("background-color: black;");
    markerX->hide();
    markerY->hide();
    markerX->raise();
    markerY->raise();
    ui->labelAllGames->setText(QString::number(GamesCounter));
    ui->labelDefeats->setText(QString::number(Defeats));
    ui->labelWins->setText(QString::number(Wins));
    if(GamesCounter > 0) ui->labelWinsProcents->setText(QString::number((Wins/GamesCounter)*100)+"%");
    else if(GamesCounter == 0) ui->labelWinsProcents->setText("0%");

    connect(ui->btn_records, &QPushButton::clicked, this, [=]{showWidget(0);});
    connect(ui->btn_settings, &QPushButton::clicked, this, [=]{showWidget(1);});
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, [=]{if(ui->comboBox->currentIndex() == 6)showWidget(2);});
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index){if(index == 2){showWidget(2); markerX->show(); markerY->show();}});
    connect(ui->progressBarX, &QProgressBar::valueChanged, this, &WelcomeWindow::updateMarkerXPosition);
    connect(ui->progressBarY, &QProgressBar::valueChanged, this, &WelcomeWindow::updateMarkerYPosition);
    connect(ui->scrollAreaCustom->verticalScrollBar(), &QScrollBar::valueChanged, this, [=](int) {
        updateMarkerXPosition(ui->progressBarX->value());
        updateMarkerYPosition(ui->progressBarY->value());
    });
    connect(ui->SliderMusicVolume, &QSlider::valueChanged, this, [=]{MusicVolume = ui->SliderMusicVolume->value()/100.0;});
    connect(ui->SliderUiVolume, &QSlider::valueChanged, this, [=]{UiVolume = ui->SliderUiVolume->value()/100.0;});
    connect(timerSec, &QTimer::timeout, this, [=]{
        seconds++;
        if (seconds >= 60){
            minutes++;
            seconds = 0;
        } if (minutes >= 60){
            hours++;
            minutes = 0;
        }
        setLabelPlayedTime();
    });
}
void WelcomeWindow::showWidget(int index){
    if(ui->stackedWidget->currentIndex() == index && !ui->stackedWidget->isHidden()) {
        if(ui->stackedWidget->currentIndex() == 2){
            ui->stackedWidget->hide();
            //Добавить проверку на comboBox сложность своя
        } else {
            ui->stackedWidget->hide();
        }
    }else {
        ui->stackedWidget->setCurrentIndex(index);
        ui->stackedWidget->show();
    }
}
void WelcomeWindow::updateMarkerXPosition(int value)
{
    int scrollY = ui->scrollAreaCustom->verticalScrollBar()->value();
    int posX = ui->progressBarX->width() * value / ui->progressBarX->maximum() + ui->stackedWidget->x() + ui->progressBarX->x();
    int posY = ui->stackedWidget->y() + ui->scrollAreaCustom->y() + ui->progressBarX->y() + 1 - scrollY;
    markerX->move(posX - markerX->width() / 2, posY);
}
void WelcomeWindow::updateMarkerYPosition(int value)
{
    int scrollY = ui->scrollAreaCustom->verticalScrollBar()->value();
    int posY = (ui->progressBarY->height() * value / ui->progressBarY->maximum()) + ui->stackedWidget->y() + ui->scrollAreaCustom->y() + ui->progressBarY->y() - scrollY;
    int posX = ui->stackedWidget->x() + ui->progressBarY->x() + 2;
    markerY->move(posX, posY - markerY->height() / 2);
}
void WelcomeWindow::saveData() {
    QJsonDocument document;
    QJsonObject list;
    if (!data->exists()) {
        log("Data file is empty.");
    }
    else {
        data->open(QIODevice::ReadOnly);
        document = QJsonDocument::fromJson(data->readAll());
        list = document.object();
        GamesCounter += list["GamesCounter"].toInt();
        Defeats += list["Defeats"].toInt();
        Wins += list["Wins"].toInt();
        data->close();
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


    document = QJsonDocument(list);
    data->open(QIODevice::WriteOnly);
    data->write(document.toJson());
    data->close();
    log("Data saved to data.json");
}
void WelcomeWindow::loadData() {
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
        auto load = [&](int Value, const QString &key) {
            if (list.contains(key)) {
                Value = list[key].toInt();
            } else {
                log("Info about \"" + key + "\" is not found.");
            }
        };
        loadRecordLabel(ui->labelEasyRecord, "Easy");
        loadRecordLabel(ui->labelMediumRecord, "Medium");
        loadRecordLabel(ui->labelHardRecord, "Hard");
        loadRecordLabel(ui->labelExtremeRecord, "Extreme");
        loadRecordLabel(ui->labelInsaneRecord, "Insane");
        load(GamesCounter, "GamesCounter");
        load(Defeats, "Defeats");
        load(Wins, "Wins");
        if (list.contains("PlayedTime")) {
            qint64 elapsedseconds = list["PlayedTime"].toInteger();
            // Преобразуем миллисекунды в часы, минуты и секунды
            seconds = elapsedseconds;
            hours = seconds / 3600;
            minutes = (seconds % 3600) / 60;
            seconds = seconds % 60;
            setLabelPlayedTime();
        } else {
            log("Info about \"PlayedTime\" is not found.");
        }



        //Settings
        ui->checkBoxWatchAllField->setChecked(list["WatchAllField"].toBool());
        MusicVolume = list["MusicVolume"].toDouble();
        UiVolume = list["UiVolume"].toDouble();
        ui->SliderMusicVolume->setSliderPosition(MusicVolume*100);
        ui->SliderUiVolume->setSliderPosition(UiVolume*100);

    } else {
        log("Try to load. Data file is gone. Creating new...");
    }
    saveData();
}
void WelcomeWindow::setLabelPlayedTime(){
    QString time = "";
    if(hours != 0){
        if(hours % 10 == 1 && hours % 100 != 11)time+= QString::number(hours) + " час ";
        else if(hours % 10 >= 2 && hours % 10 <= 4 && (hours % 100 < 12 || hours % 100 > 14))time+= QString::number(hours) + " часа ";
        else time+= QString::number(hours) + " часов ";
    }
    if(minutes != 0){
        if(minutes % 10 == 1 && minutes % 100 != 11)time+= QString::number(minutes) + " минута ";
        else if(minutes % 10 >= 2 && minutes % 10 <= 4 && (minutes % 100 < 12 || minutes % 100 > 14))time+= QString::number(minutes) + " минуты ";
        else time+= QString::number(minutes) + " минут ";
    }
    if(seconds != 0){
        if(seconds % 10 == 1 && seconds % 100 != 11)time+= QString::number(seconds) + " секунда";
        else if(seconds % 10 >= 2 && seconds % 10 <= 4 && (seconds % 100 < 12 || seconds % 100 > 14))time+= QString::number(seconds) + " секунды";
        else time+= QString::number(seconds) + " секунд";
    }
    if(time == "")ui->labelPlayedTime->setText("0 секунд");
    ui->labelPlayedTime->setText(time);
}
void WelcomeWindow::log(const QString &message) {
    qDebug()<<message;
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 elapsedMilliseconds = startTime.msecsTo(currentTime);
    qint64 seconds = elapsedMilliseconds / 1000;
    qint64 hours = seconds / 3600;
    qint64 minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;
    qint64 milliseconds = elapsedMilliseconds % 1000;

    QTextStream out(logFile);
    out << "["
        << QString::number(hours).rightJustified(2, '0') << "h-"
        << QString::number(minutes).rightJustified(2, '0') << "m-"
        << QString::number(seconds).rightJustified(2, '0') << "s-"
        << QString::number(milliseconds).rightJustified(3, '0') << "ms] --> "
        << message << "\n";

    out.flush();
}
void WelcomeWindow::closeEvent(QCloseEvent *event){
    log("Application closing...");
    timerSec->stop();
    saveData();
    event->accept();
}
void WelcomeWindow::endGame(bool win){
    if (win){
        Wins++;
    } else Defeats++;
    GamesCounter++;
    ui->labelAllGames->setText(QString::number(GamesCounter));
    ui->labelDefeats->setText(QString::number(Defeats));
    ui->labelWins->setText(QString::number(Wins));
    if(GamesCounter > 0) ui->labelWinsProcents->setText(QString::number((Wins/GamesCounter)*100)+"%");
    if(win)log("Game End result - Win");
    else log("Game End result - Defeat");
    saveData();
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
