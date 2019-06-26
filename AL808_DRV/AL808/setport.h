#ifndef SETPORT_H
#define SETPORT_H

#include <QObject>
#include <QSerialPort>

class SetPort : public QObject
{
    Q_OBJECT
public:
    explicit SetPort(QObject *parent = nullptr);
    struct BaudRateBit
    {
        QSerialPort::BaudRate Baudbits;
        QString NameBaud;
        int IndexBaudRate;
    };
    QString com=NULL;
    QSerialPort::BaudRate baudrate;
    QList<struct BaudRateBit> BaudRateList;
private slots:

    void RefreshCombox();
    void RefreshBaudratebox();
    void on_ps_cancel_clicked();
    void on_ps_ok_clicked();
    void ReadConfig();
};

#endif // SETPORT_H
