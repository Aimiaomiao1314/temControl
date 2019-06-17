#include "AL808.h"
#include <QDebug>
#include "SetPortDialog.h"
#include <QMessageBox>

AL808::AL808()
{
    Sp_Setup=new SetPortDialog();
//    Set_Al808Setup();
//    SetupWindows();

}

void AL808::Temconnect()
{

    Sp =new QSerialPort();
    Sp->setPortName(Sp_Setup->com);
    Sp->setBaudRate(Sp_Setup->baudrate);
    Sp->setDataBits(QSerialPort::Data5);
    Sp->setStopBits(QSerialPort::OneStop);
    Sp->setParity(QSerialPort::NoParity);
    Sp->open(QSerialPort::ReadWrite);
    qDebug()<<"端口号:"<<Sp->portName();
    qDebug()<<"波特率:"<<Sp->baudRate();
    qDebug()<<"奇偶性:"<<Sp->parity();
    qDebug()<<"数据位:"<<Sp->dataBits();
    qDebug()<<"停止位:"<<Sp->stopBits();
}

void AL808::Temdisconnect()
{
    return void();
}



double AL808::getPV()
{
    qDebug()<<"getPV";
    return 1;
}

double AL808::getOP()
{
    return 0;
}

double AL808::getSP()
{
    return 0;
}

double AL808::getSR()
{
    return 0;
}

double AL808::setPV()
{
    return 0;
}

double AL808::setOP()
{
    return 0;
}

double AL808::setSP()
{
    return 0;
}

double AL808::setSR()
{
    return 0;
}



int AL808::getDrvVersion()
{

    return 0;
}

void AL808::Set_Al808Setup()
{
    Sp_Setup->show();
}

void AL808::SetupWindows()
{
//    QMessageBox box;
//    box.setText(Sp->portName());
//    box.setText(Sp->baudRate());
//    box.exec();
}
