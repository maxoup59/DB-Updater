#ifndef DB_H
#define DB_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlQuery>
#include <QTextStream>
#include <QDebug>
#include <QSqlError>
#include <QCoreApplication>
#include <QSqlQueryModel>
#include <QLabel>
#include <QDir>


class DB
{
public:
    DB();
    ~DB();
        QSqlDatabase db;
    bool initBDD();
    bool deleteBDD();
    bool connectBDD();
    bool updateData();
    void setYear(int start,int end);
private :
    int startYear,endYear;
private slots:
    void hey();
};

#endif // DB_H
