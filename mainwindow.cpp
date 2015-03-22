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
    connect(queryExecutor,SIGNAL(yearStarted(QString)),this,SLOT(onYearStarted(QString)));
    connect(queryExecutor,SIGNAL(threadStoped()),this,SLOT(onThreadStoped()));
    connect(queryExecutor,SIGNAL(haveSomethingToSay(QString)),this,SLOT(onHaveSomethingToSay(QString)));
    connect(queryExecutor,SIGNAL(checkTableFinished(QString)),this,SLOT(onCheckTableFinished(QString)));


    queryExecutor->setChoice(0);
    queryExecutor->start();
}

void MainWindow::onLineInserted(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::onYearStarted(QString value)
{
    QStringList test = value.split('+');
    ui->label_year->setText(test[0]);
    ui->progressBar->setMaximum(test[1].toInt());
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
    queryExecutor->setChoice(2);
    queryExecutor->start();
    ui->button_deleteTable->setEnabled(false);
    ui->button_initTable->setEnabled(true);
    ui->button_updateData->setEnabled(false);
}

void MainWindow::on_button_initTable_clicked()
{
    queryExecutor->setChoice(3);
    queryExecutor->start();
    ui->button_deleteTable->setEnabled(true);
    ui->button_initTable->setEnabled(false);
    ui->button_updateData->setEnabled(true);
}

void MainWindow::on_button_updateData_clicked()
{
    if(ui->button_updateData->text() == "Update Data")
    {
        queryExecutor->setChoice(1);
        queryExecutor->setDate(ui->spinBox->value(),ui->spinBox_2->value());
        queryExecutor->start();
        ui->button_updateData->setText("Stop");
    }
    else
    {
        queryExecutor->setFinDemandee(true);
    }

}

void MainWindow::onThreadStoped()
{
    changeStatusMessage("Intégration stoped");
    ui->progressBar->setValue(0);
    ui->label_year->setText("Year");
    ui->button_updateData->setText("Update Data");
}

void MainWindow::onCheckTableFinished(QString value)
{
    if(value == "1")
    {
        ui->button_deleteTable->setEnabled(true);
        ui->button_initTable->setEnabled(false);
    }
    else if(value == "0")
    {
        ui->button_deleteTable->setEnabled(false);
        ui->button_initTable->setEnabled(true);
            ui->button_updateData->setEnabled(false);
    }
}

void MainWindow::onHaveSomethingToSay(QString something)
{
    changeStatusMessage(something);
}
