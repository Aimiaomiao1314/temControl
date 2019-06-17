#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../AL808/AL808.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AL808 *al808 = new AL808();
     al808->SetupWindows();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_getPV_clicked()
{

}

void MainWindow::on_pushButton_Connect_clicked()
{

}

void MainWindow::on_pushButton_DisConnect_clicked()
{

}

void MainWindow::on_pushButton_ShowSetup_clicked()
{

}
