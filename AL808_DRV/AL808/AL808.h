#ifndef AL808_H
#define AL808_H

#include "al808_global.h"
#include <QtSerialPort/QSerialPort>
#include "../../BaseDrv/TemBase.h"
#include "SetPortDialog.h"
#include <QDebug>
#include <QObject>
#include <QQueue>
#include <QThread>

#define TESTDLLSHARED_EXPORT __declspec(dllexport)
#ifdef TESTDLLSHARED_EXPORT
#else
#define TESTDLLSHARED_EXPORT __declspec(dllimport)
#endif
enum TagofCmdID{
    cmdBP=0,
    cmdCC,
    cmdCH,
    cmdHO,
    cmdHS,
    cmdLS,
    cmdOP,
    cmdPV,
    cmdRG,
    cmdSL,
    cmdSP,
    cmdTD,
    cmdTI,
    cmdXP,
    cmdAL1,
    cmdAL2,
    cmdHA,
    cmdLA,
    cmdHB,
    cmdLB,
    cmdDA
};
struct StrofCmdID
{
    int id;
    QByteArray name;
    double value;
    QString memo;
};
class AL808SHARED_EXPORT AL808 : public TemBase
{
    Q_OBJECT

public:
    AL808();

    double getPV() override;
    double getOP() override;
    double getSP() override;
    double getSL() override;

    double getXP();
    double getTI();
    double getTD();
    double getHO();
    double getCH();
    double getCC();
    double getRG();
    double getHS();
    double getLS();
    double getBP();
    double getA1();
    double getA2();
    double getHA();
    double getLA();
    double getHB();
    double getLB();
    double getDA();

    double setPV() override;
    double setOP() override;
    double setSP() override;
    double setSL(QString) override;


    int getDrvVersion() override;

    void Set_Al808Setup();
    int writeData(char *data, int size);

    QSerialPort *Sp;
    SetPortDialog *Sp_Setup;

private:
    QByteArray ReceiveData=NULL;
    QByteArray Buffer=NULL;
    QString FinValue=NULL;

    double ValPV=0;
    double ValOP=0;
    double ValSP=0;
    double ValSL=0;
    double ValXP=0;
    double ValTI=0;
    double ValTD=0;
    double ValHO=0;
    double ValCH=0;
    double ValCC=0;
    double ValRG=0;
    double ValHS=0;
    double ValLS=0;
    double ValBP=0;
    double ValA1=0;
    double ValA2=0;
    double ValHA=0;
    double ValLA=0;
    double ValHB=0;
    double ValLB=0;
    double ValDA=0;
    QString Adress=NULL;
    int Readstate=0;

    QVector <struct StrofCmdID> ParameterList;
    QQueue<QString> queue;

    void SendAllLists(QString);//发送队列
    void ReadMatch(QByteArray , double);//赋值
    void Successjudge();


private slots:

    void ReadData();//读取数据
    void InsertLists();//插入队列等待发送
    void CommandDistinction();//等待完整数据

    bool SeekStart();//寻找起始位
    bool SeekEnd();//寻找终止位
    double XORTest();//数据处理
    char BCC(QByteArray);//异或校验

public slots:
    void Temconnect() override;
    void Temdisconnect() override;
    void ConnectTest();
protected:
    void run();
signals:
    void StartSearch();
};

#endif // AL808_H
