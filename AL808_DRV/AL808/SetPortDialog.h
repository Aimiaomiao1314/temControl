#ifndef SETPORTDIALOG_H
#define SETPORTDIALOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class SetPortDialog;
}

class SetPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPortDialog(QWidget *parent = 0);
    ~SetPortDialog();
    struct BaudRateBit
    {
        QSerialPort::BaudRate Baudbits;
        QString NameBaud;
        int IndexBaudRate;
    };
    QString com=NULL;
    QSerialPort::BaudRate baudrate;
    QList<struct BaudRateBit> BaudRateList;

private:
    Ui::SetPortDialog *ui;
private slots:

    void RefreshCombox();
    void RefreshBaudratebox();
    void on_ps_cancel_clicked();
    void on_ps_ok_clicked();
    void ReadConfig();
};

#endif // SETPORTDIALOG_H
