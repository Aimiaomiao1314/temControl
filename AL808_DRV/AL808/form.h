#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

struct Commend
{
    QString id;
    double value;
};

class Form : public QWidget
{
    Q_OBJECT

public:
    Ui::Form *ui;
    explicit Form(QWidget *parent = 0);
    ~Form();
    double PV=0;
    double SP=0;
    double SL=0;
    double XP=0;
    double TI=0;
    double TD=0;
    double CH=0;
    double CC=0;
    double RG=0;
    double HS=0;
    double LS=0;
    double BP=0;
    double HO=0;
    void SetValue();


private slots:

    void on_pushButton_GetData_clicked();

    void on_doubleSpinBox_PV_editingFinished();

    void on_doubleSpinBox_OP_editingFinished();

    void on_doubleSpinBox_SP_editingFinished();

    void on_doubleSpinBox_SL_editingFinished();

    void on_doubleSpinBox_XP_editingFinished();

    void on_doubleSpinBox_TI_editingFinished();

    void on_doubleSpinBox_TD_editingFinished();

    void on_doubleSpinBox_CH_editingFinished();

    void on_doubleSpinBox_CC_editingFinished();

    void on_doubleSpinBox_RG_editingFinished();

    void on_doubleSpinBox_HS_editingFinished();

    void on_doubleSpinBox_LS_editingFinished();

    void on_doubleSpinBox_BP_editingFinished();

    void on_doubleSpinBox_HO_editingFinished();

private:



signals:

    void GetValue();
    void SendChange(Commend );

};

#endif // FORM_H
