#include "SetPortDialog.h"
#include "ui_SetPortDialog.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QSettings>

SetPortDialog::SetPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPortDialog)
{
    ui->setupUi(this);
}

SetPortDialog::~SetPortDialog()
{
    delete ui;
}

void SetPortDialog::RefreshCombox()   //添加COM列表
{
    QList<QSerialPortInfo> m_list = QSerialPortInfo::availablePorts();  //查询可用COM端口号并添加
    ui->cbox_com->clear();
    for(int i = 0;i<m_list.count();i++)
    {
        if(!m_list.at(i).isBusy())
        {
            ui->cbox_com->addItem(m_list.at(i).portName());
        }
    }
}

void SetPortDialog::RefreshBaudratebox() //添加波特率列表
{
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud1200,"1200",0});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud2400,"2400",1});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud4800,"4800",2});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud9600,"9600",3});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud19200,"19200",4});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud38400,"38400",5});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud57600,"57600",6});
    BaudRateList.append(BaudRateBit{QSerialPort::BaudRate::Baud115200,"115200",7});
    for(int i=0;i<BaudRateList.size();i++)
    {
        ui->cbox_baudrate->insertItem(BaudRateList.at(i).IndexBaudRate,BaudRateList.at(i).NameBaud);
        ui->cbox_baudrate->setCurrentIndex(0);
    }
}

void SetPortDialog::on_ps_ok_clicked() //点击OK , 写配置文件
{
    QString ini_path;
    QSettings* app_config;
    com = ui->cbox_com->currentText();
    ini_path = "configuration.ini";
    app_config= new QSettings (ini_path, QSettings::IniFormat);//生成配置文件
    app_config->beginGroup("Serilport");       //端口号内容写入
    app_config->setValue("ComPort",ui->cbox_com->currentText());
    app_config->setValue("BaudRate",ui->cbox_baudrate->currentText());
    app_config->setValue("Address",ui->cbox_sp_communication->currentText());
    app_config->endGroup();
    this->close();
}

void SetPortDialog::on_ps_cancel_clicked() //点击Cancel
{
    this->close();
}

void SetPortDialog::ReadConfig()  //读配置文件
{
    RefreshCombox();
    RefreshBaudratebox();
    QString ini_path;
    QSettings* app_config;
    ini_path = "configuration.ini";
    app_config= new QSettings (ini_path, QSettings::IniFormat);//生成配置文件
    app_config->beginGroup("Serilport");
    com = app_config->value("ComPort").toString(); //读端口号
    addr = app_config->value("Address").toInt();       //读通讯地址
    for(int i=0;i<BaudRateList.size();i++)                      //读波特率
    {
        if(app_config->value("BaudRate").toString()==BaudRateList.at(i).NameBaud)
        {
            baudrate=BaudRateList.at(i).Baudbits;
            ui->cbox_baudrate->setCurrentText(BaudRateList.at(i).NameBaud);
        }
    }
    app_config->endGroup();
}

QString SetPortDialog::ErgodicAdress(int i)
{

  QString temp=QString("%1").arg(i, 2, 10, QChar('0'));
  QString Adress1=temp.at(0);
  QString Adress2=temp.at(1);
  QString Adress=Adress1+Adress1+Adress2+Adress2;
  return Adress;

}
