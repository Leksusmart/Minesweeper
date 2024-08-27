#include "./ui_Welcome.h"
#include "WelcomeWindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
WelcomeWindow::WelcomeWindow() : ui(new Ui::WelcomeWindow)
{
    logFile->open(QIODevice::WriteOnly | QIODevice::Text);
    ui->setupUi(this);
    loadData();



}
void WelcomeWindow::saveData() {
    QJsonObject list;
    list["username"] = "Player1";
    list["score"] = 100;

    QJsonDocument document(list);
    if (!data->open(QIODevice::ReadOnly)) {
        qDebug() << "Data file is empty.";
        log("Data file is empty.");
    }
    else data->close();
    data->open(QIODevice::WriteOnly);
    data->write(document.toJson());
    data->close();
    qDebug() << "Data saved to data.json";
    log("Data saved to data.json");
}
void WelcomeWindow::loadData() {
    if (data->open(QIODevice::ReadOnly)) {
        QJsonDocument document = QJsonDocument::fromJson(data->readAll());
        QJsonObject list = document.object();

        qDebug() << "Username:" << list["username"].toString();
        qDebug() << "Score:" << list["score"].toInt();

        data->close();
    } else {
        qDebug() << "Try to load. Data file is gone. Creating new...";
        log("Try to load. Data file is gone. Creating new...");
        saveData();
    }
}
void WelcomeWindow::log(const QString &message) {
    // Получаем текущее время
    QDateTime currentTime = QDateTime::currentDateTime();
    // Вычисляем разницу во времени
    qint64 elapsedMilliseconds = startTime.msecsTo(currentTime);
    // Преобразуем миллисекунды в часы, минуты и секунды
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

WelcomeWindow::~WelcomeWindow()
{
    logFile->close();
    delete logFile;
    delete data;
    delete ui;
}
