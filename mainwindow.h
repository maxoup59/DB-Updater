#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "db.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void changeProgressBarValue(int value);
    ~MainWindow();

private slots:
    void on_button_connect_clicked();

    void on_button_deleteTable_clicked();

    void on_button_initTable_clicked();

    void on_button_updateData_clicked();


private:
    QLabel* statusLabel;
    Ui::MainWindow *ui;
    void changeStatusMessage(QString message);

    DB* dataBase;
};

#endif // MAINWINDOW_H
