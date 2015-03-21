#ifndef THREADINTEGRATION_H
#define THREADINTEGRATION_H

#include <QThread>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QFile>

class ThreadIntegration : public QThread
{
    Q_OBJECT

public:
    ThreadIntegration();
    ~ThreadIntegration();
    void run();
    void update();
    void setChoice(int pChoice);
    void setDate(int pStartyear,int pEndyear);
    void setFinDemandee(bool pFinDemande);
signals:
    void lineInserted(int value);
    void yearStarted(int value);
    void threadStoped();
private :
    QSqlDatabase db;
    int choice;
    void init();
    void remove();
    int startYear,endYear;
    bool finDemandee;
};

#endif // THREADINTEGRATION_H
