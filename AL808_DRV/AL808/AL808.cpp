#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include <QSettings>
#include "AL808.h"
#include "SetPortDialog.h"

AL808::AL808()
{
    struct StrofCmdID pl;
    pl={TagofCmdID::cmdBP, "BP",ValBP,"故障功率"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdCC, "CC",ValCC,"冷却周期"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdCH, "CH",ValCH,"加热周期"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdHO, "HO",ValHO,"最大功率"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdHS, "HS",ValHS,"最大值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdLS, "LS",ValLS,"最小值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdOP, "OP",ValOP,"输出功率"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdPV, "PV",ValPV,"测量值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdRG, "RG",ValRG,"相关系数"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdSL, "SL",ValSL,"设定值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdSP, "SP",ValSP,"目标值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdTD, "TD",ValTD,"微分时间"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdTI, "TI",ValTI,"积分时间"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdXP, "XP",ValXP,"加热比例带"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdAL1, "A1",ValA1,"AL1报警值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdAL2, "A2",ValA2,"AL2报警值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdHA, "HA",ValHA,"上限报警值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdLA, "LA",ValLA,"下限报警值"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdHB, "HB",ValHB,"PID上分离带"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdLB, "LB",ValLB,"PID下分离带"}; ParameterList.push_back(pl);
    pl={TagofCmdID::cmdDA, "DA",ValDA,"偏差报警"}; ParameterList.push_back(pl);

    Sp=new QSerialPort();
    Sp_Setup=new SetPortDialog();
    connect(Sp,SIGNAL(readyRead()),this,SLOT(ReadData())); //接收到数据处理;
    connect(this,SIGNAL(StartSearch()),this,SLOT(InsertLists()));//开始搜索

    timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutAddr()));

//    QThread *newthread = new  QThread;
//    this->moveToThread(newthread);
//    newthread->start();
//    qDebug()<<"123123123当前线程："<<newthread->currentThread();

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
    else
    {
        Sp->setPortName(Sp_Setup->com);
        Sp->setBaudRate(Sp_Setup->baudrate);
        Sp->setDataBits(QSerialPort::Data7);
        Sp->setStopBits(QSerialPort::OneStop);
        Sp->setParity(QSerialPort::EvenParity);
        Sp->setFlowControl(QSerialPort::NoFlowControl);//流控制
        Sp->setReadBufferSize(0);//设置缓冲区大小
        Sp->open(QSerialPort::ReadWrite);
        if(Sp->isOpen())
        {
            qDebug()<<"端口号:"<<Sp->portName();
            qDebug()<<"波特率:"<<Sp->baudRate();
            qDebug()<<"奇偶性:"<<Sp->parity();
            qDebug()<<"数据位:"<<Sp->dataBits();
            qDebug()<<"停止位:"<<Sp->stopBits();
            emit StartSearch();
        }
    }
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

int AL808::writeData(char *data, int size)//用于发送数据
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
void AL808::SeachAdress(int i)
{
    if(Sp->isOpen())
    {
        Sp_Setup->addr=i;
        Readstate=3;
        StartAdress(i);
        timer->start(500);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("请先连接端口");
        msgBox.exec();
    }
}

void AL808::ConnectTest()
{
    qDebug()<<"DLL槽连接成功";
}

QString AL808::StartAdress(int i)
{
    char ChSTX=4;   //正文开始
    char ChETX=5;   //正文结束
    QString Adresstemp=Sp_Setup->ErgodicAdress(i);
    QString PVSealedText=QString("%1").arg(ChSTX)+Adresstemp+"PV"+ QString("%1").arg(ChETX);  //命令字符串
    qDebug()<<"发送的消息为："<<PVSealedText;
    QByteArray byte = PVSealedText.toLatin1();
    char *ch=byte.data();

    writeData(ch,strlen(ch));
    return Adresstemp;
}
void AL808::ReadData()
{
    if(Readstate==0)
        ReceiveData=Sp->readAll();           //读取所有数据
    CommandDistinction();

    if(Readstate==1)
        ReceiveData=Sp->readAll();
    Successjudge();

    if(Readstate==3)
        ConfirmAdress();


}
void AL808::Successjudge()
{
    char ChACK=6;   //收到通知
    char ChNAK=15;  //拒绝接受
    if(ReceiveData.contains(ChACK)){
        qDebug()<<"修改成功";
        ReceiveData.clear();
        Readstate=0;
    }
    if(ReceiveData.contains(ChNAK)){
        qDebug()<<"修改失败";
        ReceiveData.clear();
        Readstate=0;
    }
}
void AL808::CommandDistinction()
{

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
    QString Value=NULL;
    Chtemp=BCC(Buffer);
    if(Buffer.endsWith(Chtemp))
    {
        for(int i=3;i<Buffer.length();i++)
        {
            if(Buffer.at(i)!=ChETX)
            {
                Value.append(Buffer.at(i));
            }
            else
            {
                qDebug()<<"最终获得的完整值："<<Buffer;
                qDebug()<<"最终数值："<<Value;
                ReadMatch(Buffer,Value.toDouble());
                Buffer=NULL;
                emit StartSearch();
            }
        }
    }
    else
    {
        qDebug()<<"数据有丢失,请重新获取";
        Buffer=NULL;
        emit StartSearch();
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

void AL808::timeoutAddr()
{
    timer->stop();
    if(Sp_Setup->addr>20)
    {
        qDebug()<<"未找到地址";
        Sp_Setup->addr=0;
        return;
    }
    SeachAdress(++Sp_Setup->addr);
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
void AL808::ConfirmAdress()
{
    Readstate=0;
    qDebug()<<"确认地址:"<<Sp_Setup->addr;
    timer->stop();

    QString ini_path= "configuration.ini";
    QSettings* app_config;
    app_config= new QSettings (ini_path, QSettings::IniFormat);//生成配置文件
    app_config->beginGroup("Serilport");       //端口号内容写入
    app_config->setValue("Address",Sp_Setup->addr);
    app_config->endGroup();
}


void AL808::InsertLists()//插入队列
{
    if(queue.empty())
    {
        char ChSTX=4;     //正文开始
        char ChETX=5;     //正文结束

        QString Address=Sp_Setup->ErgodicAdress(Sp_Setup->addr);
        QString PVSealedText=QString("%1").arg(ChSTX)+Address+"PV"+ QString("%1").arg(ChETX);  //命令字符串
        QString OPSealedText=QString("%1").arg(ChSTX)+Address+"OP"+ QString("%1").arg(ChETX);  //命令字符串
        QString SPSealedText=QString("%1").arg(ChSTX)+Address+"SP"+ QString("%1").arg(ChETX);  //命令字符串
        QString SLSealedText=QString("%1").arg(ChSTX)+Address+"SL"+ QString("%1").arg(ChETX);  //命令字符串
        QString XPSealedText=QString("%1").arg(ChSTX)+Address+"XP"+ QString("%1").arg(ChETX);  //命令字符串
        QString TISealedText=QString("%1").arg(ChSTX)+Address+"TI"+ QString("%1").arg(ChETX);  //命令字符串
        QString TDSealedText=QString("%1").arg(ChSTX)+Address+"TD"+ QString("%1").arg(ChETX);  //命令字符串
        QString CHSealedText=QString("%1").arg(ChSTX)+Address+"CH"+ QString("%1").arg(ChETX);  //命令字符串
        QString CCSealedText=QString("%1").arg(ChSTX)+Address+"CC"+ QString("%1").arg(ChETX);  //命令字符串
        QString RGSealedText=QString("%1").arg(ChSTX)+Address+"RG"+ QString("%1").arg(ChETX);  //命令字符串
        QString HSSealedText=QString("%1").arg(ChSTX)+Address+"HS"+ QString("%1").arg(ChETX);  //命令字符串
        QString LSSealedText=QString("%1").arg(ChSTX)+Address+"LS"+ QString("%1").arg(ChETX);  //命令字符串
        QString BPSealedText=QString("%1").arg(ChSTX)+Address+"BP"+ QString("%1").arg(ChETX);  //命令字符串
        QString HOSealedText=QString("%1").arg(ChSTX)+Address+"HO"+ QString("%1").arg(ChETX);  //命令字符串

        queue.enqueue(PVSealedText);
        queue.enqueue(OPSealedText);
        queue.enqueue(SPSealedText);
        queue.enqueue(SLSealedText);
        queue.enqueue(XPSealedText);
        queue.enqueue(TISealedText);
        queue.enqueue(TDSealedText);
        queue.enqueue(CHSealedText);
        queue.enqueue(CCSealedText);
        queue.enqueue(RGSealedText);
        queue.enqueue(HSSealedText);
        queue.enqueue(LSSealedText);
        queue.enqueue(BPSealedText);
        queue.enqueue(HOSealedText);

        QTimer::singleShot(3000,this,SLOT(InsertLists()));
        return;
    }
    if(Readstate==0)
        SendAllLists(queue.dequeue());

}
void AL808::SendAllLists(QString queue)
{
    qDebug()<<"发送的消息为："<<queue;
    QByteArray byte = queue.toLatin1();
    char *ch=byte.data();
    writeData(ch,strlen(ch));
}

void AL808::ReadMatch(QByteArray data , double Value)
{
    if(data.contains("PV"))
        ValPV=Value;return;
    if(data.contains("OP"))
        ValOP=Value;return;
    if(data.contains("SP"))
        ValSP=Value;return;
    if(data.contains("SL"))
        ValPV=Value;return;
    if(data.contains("XP"))
        ValPV=Value;return;
    if(data.contains("TI"))
        ValPV=Value;return;
    if(data.contains("TD"))
        ValPV=Value;return;
    if(data.contains("HO"))
        ValPV=Value;return;
    if(data.contains("CH"))
        ValPV=Value;return;
    if(data.contains("CC"))
        ValPV=Value;return;
    if(data.contains("RG"))
        ValPV=Value;return;
    if(data.contains("HS"))
        ValPV=Value;return;
    if(data.contains("LS"))
        ValLS=Value;return;
    if(data.contains("BP"))
        ValBP=Value;return;
    if(data.contains("A1"))
        ValA1=Value;return;
    if(data.contains("A2"))
        ValA2=Value;return;
    if(data.contains("HA"))
        ValHA=Value;return;
    if(data.contains("LA"))
        ValLA=Value;return;
    if(data.contains("HB"))
        ValHB=Value;return;
    if(data.contains("LB"))
        ValLB=Value;return;
    if(data.contains("DA"))
        ValDA=Value;return;

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
double AL808::getPV()
{
    return ValPV;
}

double AL808::getOP()
{
    return ValOP;
}

double AL808::getSP()
{
    return ValSP;
}

double AL808::getSL()
{
    return ValSL;
}

double AL808::getXP()
{
    return ValXP;
}
double AL808::getTI()
{
    return ValTI;
}
double AL808::getTD()
{
    return ValTD;
}
double AL808::getHO()
{
    return ValHO;
}
double AL808::getCH()
{
    return ValCH;
}
double AL808::getCC()
{
    return ValCC;
}
double AL808::getRG()
{
    return ValRG;
}
double AL808::getHS()
{
    return ValHS;
}
double AL808::getLS()
{
    return ValLS;
}
double AL808::getBP()
{
    return ValBP;
}
double AL808::getA1()
{
    return ValA1;
}
double AL808::getA2()
{
    return ValA2;
}
double AL808::getHA()
{
    return ValHA;
}
double AL808::getLA()
{
    return ValLA;
}
double AL808::getHB()
{
    return ValHB;
}
double AL808::getLB()
{
    return ValLB;
}
double AL808::getDA()
{
    return ValDA;
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

double AL808::setSL(QString data)
{
    QString EditText="SL"+data;
    QString Addr=Sp_Setup->ErgodicAdress(Sp_Setup->addr);
    char ChEOT=4;     //传输结束
    char ChSTX=2;     //正文开始
    char ChETX=3;     //正文结束
    char ChXOR;       //异或校验
    char Chtemp;
    Readstate=1;

    QString Start=QString("%1").arg(ChEOT)+Addr+QString("%1").arg(ChSTX);
    QString SealedText =Start +EditText+QString("%1").arg(ChETX);
    ChXOR=SealedText.at(6).toLatin1();
    for(int i=7;i<SealedText.length();i++)
    {
        Chtemp=SealedText.at(i).toLatin1();
        ChXOR=ChXOR^Chtemp;
    }
    SealedText.append(ChXOR);
    qDebug()<<"发送的数据为："<<SealedText;
    QByteArray byte = SealedText.toLatin1();
    char *ch=byte.data();
    writeData(ch,byte.size());
    return 0;
}
