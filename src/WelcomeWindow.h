#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeWindow; }
QT_END_NAMESPACE

class WelcomeWindow : public QMainWindow {   Q_OBJECT
public:
    WelcomeWindow();
    ~WelcomeWindow();
    QFile *logFile= new QFile("session.log");
    QDateTime startTime  = QDateTime::currentDateTime();
    QFile *data = new QFile("data.json");
private:
    Ui::WelcomeWindow *ui;
public slots:
    void log(const QString &message);
    void saveData();
    void loadData();
private slots:

};
#endif // WELCOMEWINDOW_H
