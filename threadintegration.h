#ifndef THREADINTEGRATION_H
#define THREADINTEGRATION_H

#include <QThread>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

class ThreadIntegration : public QThread
{
public:
    ThreadIntegration();
    ~ThreadIntegration();
    void run();
    void update();
    void setChoice(int pChoice);
private :
    QSqlDatabase db;
    int choice;
    void init();
    void remove();
};

#endif // THREADINTEGRATION_H
