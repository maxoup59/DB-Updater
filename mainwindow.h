#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "threadintegration.h"

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
    ThreadIntegration* queryExecutor;
};

#endif // MAINWINDOW_H
