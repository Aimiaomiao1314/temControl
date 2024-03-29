#include "form.h"
#include "ui_form.h"
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_GetData_clicked()
{
    emit GetValue();
}

void Form::SetValue()
{
    this->ui->label_PV_Value->setText(QString::number(PV));
    this->ui->label_SP_Value->setText(QString::number(SP));
    this->ui->label_SL_Value->setText(QString::number(SL));
    this->ui->label_XP_Value->setText(QString::number(XP));
    this->ui->label_TI_Value->setText(QString::number(TI));
    this->ui->label_CH_Value->setText(QString::number(CH));
    this->ui->label_CC_Value->setText(QString::number(CC));
    this->ui->label_RG_Value->setText(QString::number(RG));
    this->ui->label_HS_Value->setText(QString::number(HS));
    this->ui->label_LS_Value->setText(QString::number(LS));
    this->ui->label_BP_Value->setText(QString::number(BP));
    this->ui->label_HO_Value->setText(QString::number(HO));
}

void Form::on_doubleSpinBox_SL_editingFinished()
{
    Commend CSL;
    CSL.id="SL";
    CSL.value=ui->doubleSpinBox_SL->value();
    emit  SendChange(CSL);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_XP_editingFinished()
{
    Commend CXP;
    CXP.id="XP";
    CXP.value=ui->doubleSpinBox_XP->value();
    emit   SendChange( CXP);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_TI_editingFinished()
{
    Commend CTI;
    CTI.id="TI";
    CTI.value=ui->doubleSpinBox_TI->value();
    emit   SendChange(CTI);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_TD_editingFinished()
{
    Commend CTD;
    CTD.id="TD";
    CTD.value=ui->doubleSpinBox_TD->value();
    emit    SendChange(CTD);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_CH_editingFinished()
{
    Commend CCH;
    CCH.id="CH";
    CCH.value=ui->doubleSpinBox_CH->value();
    emit    SendChange(CCH);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_CC_editingFinished()
{
    Commend CCC;
    CCC.id="SL";
    CCC.value=ui->doubleSpinBox_SL->value();
    emit   SendChange(CCC);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_RG_editingFinished()
{
    Commend CRG;
    CRG.id="RG";
    CRG.value=ui->doubleSpinBox_RG->value();
    emit  SendChange(CRG);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_HS_editingFinished()
{
    Commend CHS;
    CHS.id="HS";
    CHS.value=ui->doubleSpinBox_HS->value();
    emit   SendChange(CHS);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_LS_editingFinished()
{
    Commend CLS;
    CLS.id="LS";
    CLS.value=ui->doubleSpinBox_LS->value();
    emit    SendChange(CLS);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_BP_editingFinished()
{
    Commend CBP;
    CBP.id="BP";
    CBP.value=ui->doubleSpinBox_BP->value();
    emit   SendChange(CBP);
    qDebug()<<"Finish";
}

void Form::on_doubleSpinBox_HO_editingFinished()
{
    Commend CHO;
    CHO.id="HO";
    CHO.value=ui->doubleSpinBox_HO->value();
    emit   SendChange(CHO);
    qDebug()<<"Finish";
}
