#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../AL808/AL808.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    al808 = new AL808();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_getPV_clicked()
{
    al808->getPV();
}

void MainWindow::on_pushButton_Connect_clicked()
{
    al808->Temconnect();
}

void MainWindow::on_pushButton_DisConnect_clicked()
{
    al808->Temdisconnect();
}

void MainWindow::on_pushButton_ShowSetup_clicked()
{
    qDebug()<<"点击Setup";
    al808->Set_Al808Setup();
}
