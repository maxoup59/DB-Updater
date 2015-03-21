#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->button_deleteTable->setEnabled(false);
    ui->button_initTable->setEnabled(false);
    ui->button_updateData->setEnabled(false);
    ui->progressBar->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->button_connect->setEnabled(true);
    statusLabel = new QLabel();
    ui->statusBar->addWidget(statusLabel);
    queryExecutor = new ThreadIntegration();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_connect_clicked()
{

    ui->button_deleteTable->setEnabled(true);
    ui->button_initTable->setEnabled(true);
    ui->button_connect->setEnabled(false);
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->button_updateData->setEnabled(true);
}

void MainWindow::changeStatusMessage(QString message)
{
    statusLabel->setText(message);
}

void MainWindow::on_button_deleteTable_clicked()
{
    queryExecutor->setChoice(1);
    queryExecutor->start();
    /*if(dataBase->deleteBDD())
    {
        changeStatusMessage("BDD deleted");
    }
    else
    {
        changeStatusMessage("Error can't delete BDD");
    }*/

}

void MainWindow::on_button_initTable_clicked()
{
    queryExecutor->setChoice(2);
    queryExecutor->start();
    /*if(dataBase->initBDD())
    {
        changeStatusMessage("BDD initialized");
    }
    else {
        changeStatusMessage("Error can't init BDD");
    }*/
}

void MainWindow::on_button_updateData_clicked()
{
    queryExecutor->setChoice(0);
    queryExecutor->setDate(ui->spinBox->value(),ui->spinBox_2->value());
    queryExecutor->start();
}
