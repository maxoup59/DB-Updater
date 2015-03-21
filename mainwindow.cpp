#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusLabel = new QLabel();
    ui->statusBar->addWidget(statusLabel);
    queryExecutor = new ThreadIntegration();
    connect(queryExecutor,SIGNAL(lineInserted(int)),this,SLOT(onLineInserted(int)));
    connect(queryExecutor,SIGNAL(yearStarted(int)),this,SLOT(onYearStarted(int)));
    connect(queryExecutor,SIGNAL(threadStoped()),this,SLOT(onThreadStoped()));
}

void MainWindow::onLineInserted(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::onYearStarted(int value)
{
    ui->label_year->setText(QString::number(value));
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_button_stopUpdate_clicked()
{
    queryExecutor->setFinDemandee(true);
}

void MainWindow::onThreadStoped()
{
    changeStatusMessage("Thread stoped");
    ui->progressBar->setValue(0);
    ui->label_year->setText("Year");
}
