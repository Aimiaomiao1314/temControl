#ifndef TEMBASE_H
#define TEMBASE_H

#include <QObject>

class TemBase : public QObject
{
    Q_OBJECT
public:
    explicit TemBase(QObject *parent = nullptr);

signals:

public slots:

public:
    virtual double getPV() = 0;
    virtual double getOP() = 0;
    virtual double getSP() = 0;
    virtual double getSR() = 0;

    virtual double setPV() = 0;
    virtual double setOP() = 0;
    virtual double setSP() = 0;
    virtual double setSR() = 0;

    virtual void Temconnect() = 0;
    virtual void Temdisconnect() = 0;

    virtual int getDrvVersion() = 0;
};

#endif // TEMBASE_H