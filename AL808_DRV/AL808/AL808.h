#ifndef AL808_H
#define AL808_H

#include "al808_global.h"
#include <QtSerialPort/QSerialPort>
#include "../../BaseDrv/TemBase.h"
#include "SetPortDialog.h"
#include <QDebug>

#define TESTDLLSHARED_EXPORT __declspec(dllexport)
#ifdef TESTDLLSHARED_EXPORT
#else
#define TESTDLLSHARED_EXPORT __declspec(dllimport)
#endif
class AL808SHARED_EXPORT AL808 : public TemBase
{

public:
    AL808();

    double getPV() override;
    double getOP() override;
    double getSP() override;
    double getSR() override;

    double setPV() override;
    double setOP() override;
    double setSP() override;
    double setSR() override;

    void Temconnect() override;
    void Temdisconnect() override;
    int getDrvVersion() override;
    void Set_Al808Setup();
    void SetupWindows();
    int writeData(char *data, int size);

    QSerialPort *Sp;
    SetPortDialog *Sp_Setup;

private:
    QByteArray ReceiveData;
    QByteArray Buffer=NULL;

private slots:
    void ReadData();
    void CommandDistinction();
    bool SeekStart();
    bool SeekEnd();
    double XORTest();
    char BCC(QByteArray);
};

#endif // AL808_H
