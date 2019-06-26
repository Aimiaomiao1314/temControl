#include "AL808.h"
#include <QDebug>
#include "SetPortDialog.h"
#include <QMessageBox>

AL808::AL808()
{
    Sp=new QSerialPort();
    Sp_Setup=new SetPortDialog();
    connect(Sp,SIGNAL(readyRead()),this,SLOT(ReadData())); //接收到数据处理;
}

void AL808::Temconnect()
{
    Sp_Setup->ReadConfig();
    if(Sp->isOpen())
    {
        qDebug()<<"AL808已连接";
        QMessageBox::information(NULL, "提示", "已连接,请勿重复操作", QMessageBox::Ok);
        return void();
    }
    Sp =new QSerialPort();
    Sp->setPortName(Sp_Setup->com);
    Sp->setBaudRate(Sp_Setup->baudrate);
    Sp->setDataBits(QSerialPort::Data5);
    Sp->setStopBits(QSerialPort::OneStop);
    Sp->setParity(QSerialPort::NoParity);
    Sp->setFlowControl(QSerialPort::NoFlowControl);//流控制
    Sp->setReadBufferSize(0);//设置缓冲区大小
    Sp->open(QSerialPort::ReadWrite);
    qDebug()<<"端口号:"<<Sp->portName();
    qDebug()<<"波特率:"<<Sp->baudRate();
    qDebug()<<"奇偶性:"<<Sp->parity();
    qDebug()<<"数据位:"<<Sp->dataBits();
    qDebug()<<"停止位:"<<Sp->stopBits();
}

void AL808::Temdisconnect()
{
    if(Sp->isOpen())
    {
        Sp->close();
        qDebug()<<"关闭串口成功";
    }
    else
    {
        QMessageBox::information(NULL, "提示", "已处于关闭状态,请勿重复操作", QMessageBox::Ok);
    }

}

double AL808::getPV()
{
    char ChStartbit=4;     //起始位
    char ChEndbit=5;       //终止位
    QString Adress="0011"; //地址
    QString SealedText=QString("%1").arg(ChStartbit)+Adress+"PV"+ QString("%1").arg(ChEndbit);  //命令字符串
    QByteArray byte = SealedText.toLatin1();
    char *ch=byte.data();
    writeData(ch,strlen(ch));
    return 0;
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
int AL808::writeData(char *data, int size)               //用于发送数据
{

    int error =-1;
    int len = 0;
    forever
    {
        qint64 n =Sp->write(&data[len], size-len);
        if (n == -1)
        {
            qDebug()<<"发生错误";
            return error; //返回-1代表发生错误;
        }
        else
        {
            len += n;
            if (size == len)
                break;
        }
    }
    qDebug()<<"发送成功";
    return len;
}
void AL808::ReadData()
{
    ReceiveData=Sp->readAll();           //读取所有数据
    CommandDistinction();
}
void AL808::CommandDistinction()
{
    qDebug()<<"接收到了信息:"<<ReceiveData;

    if(!SeekStart()) return;

    if(!SeekEnd())   return;

    XORTest();
}
bool AL808::SeekStart() //寻找起始位的位置并截取从起始位开始到末尾
{
    char ChSTX=2;   //正文开始
    //    char ChACK=6;   //收到通知
    //    char ChNAK=15;  //拒绝接受
    for(int i=0;i<ReceiveData.length();i++)
    {
        Buffer.append(ReceiveData.at(i));

    }
    if(Buffer.contains(ChSTX))
    {
        int StartBitLocation =Buffer.indexOf(ChSTX);
        Buffer = Buffer.mid(StartBitLocation);
        return true;
    }
    return false;
}
double AL808::XORTest()  //异或效验
{
    char Chtemp;
    char ChETX=3;   //正文结束
    Chtemp=BCC(Buffer);
    if(Buffer.endsWith(Chtemp))
    {
        QString FinValue;
        for(int i=3;i<Buffer.length();i++)
        {
            if(Buffer.at(i)!=ChETX)
                FinValue.append(Buffer.at(i));
            else
                return FinValue.toDouble();
        }
    }
    else
    {
        qDebug()<<"数据有丢失,请重新获取";
        Buffer=NULL;
    }
    return 0;
}
char AL808::BCC(QByteArray ba) //异或校验过程
{
    char result = ba.at(1);
    for(int i=2;i<ba.size()-1; ++i)
    {
        result ^=ba.at(i);
    }
    return result;
}
bool AL808::SeekEnd()    //找终止位
{
    char ChETX=3;   //正文结束
    if(Buffer.contains(ChETX))
    {
        int EndBitLocation =Buffer.indexOf(ChETX);
        if(Buffer.length()>EndBitLocation+1)
        {
            Buffer = Buffer.mid(0,EndBitLocation+2);
            return true;
        }
    }
    return false;
}

int AL808::getDrvVersion()
{

    return 0;
}

void AL808::Set_Al808Setup()
{
    Sp_Setup->ReadConfig();
    Sp_Setup->show();
}

void AL808::SetupWindows()
{
  // QMessageBox box;
}
