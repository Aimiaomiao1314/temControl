#ifndef TEMBASE_H
#define TEMBASE_H

#include <QObject>

class TemBase : public QObject
{

public:
    explicit TemBase(QObject *parent = nullptr);

signals:

public slots:
public:
    virtual double getPV() = 0;
    virtual double getOP() = 0;
    virtual double getSP() = 0;
    virtual double getSL() = 0;

    virtual void setPV(QString) = 0;
    virtual void setOP(QString) = 0;
    virtual void setSP(QString) = 0;
    virtual void setSL(QString) = 0;

    virtual void Temconnect() = 0;
    virtual void Temdisconnect() = 0;

    virtual int getDrvVersion() = 0;
};

#endif // TEMBASE_H
