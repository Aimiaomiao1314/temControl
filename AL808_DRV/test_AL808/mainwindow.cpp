#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../AL808/AL808.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    al808 = new AL808();
    connect(this,SIGNAL(groove()),al808,SLOT(ConnectTest()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_getPV_clicked()
{
    double PV=al808->getPV();
    qDebug()<<"获得PV值："<<PV;
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
    al808->Set_Al808Setup();
}

void MainWindow::on_Btn_SearchAdress_clicked()
{

    al808->SeachAdress(0);

}

void MainWindow::on_pushButton_SetSL_clicked()
{
    al808->setSL("40.2");
}

void MainWindow::on_pushButton_Groove_clicked()
{
    emit groove();
}
