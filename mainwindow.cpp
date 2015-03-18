#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->button_deleteTable->setEnabled(false);
    ui->button_initTable->setEnabled(false);
    ui->button_connect->setEnabled(true);
    statusLabel = new QLabel();
    ui->statusBar->addWidget(statusLabel);
    dataBase = new DB();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_connect_clicked()
{
    if(dataBase->connectBDD())
    {
        changeStatusMessage("Connected to BDD");
    }
    ui->button_deleteTable->setEnabled(true);
    ui->button_initTable->setEnabled(true);
    ui->button_connect->setEnabled(false);
}

void MainWindow::changeStatusMessage(QString message)
{
    statusLabel->setText(message);
}

void MainWindow::on_button_deleteTable_clicked()
{
    if(dataBase->deleteBDD())
    {
        changeStatusMessage("BDD deleted");
    }
    else
    {
        changeStatusMessage("Error can't delete BDD");
    }

}

void MainWindow::on_button_initTable_clicked()
{
    if(dataBase->initBDD())
    {
        changeStatusMessage("BDD initialized");
    }
    else {
        changeStatusMessage("Error can't init BDD");
    }
}

void MainWindow::on_button_updateData_clicked()
{
    dataBase->updateData();
}
