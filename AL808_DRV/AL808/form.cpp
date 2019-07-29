#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    al808=new AL808();
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_PV_clicked()
{
  al808->setPV();
}

void Form::on_pushButton_GetData_clicked()
{

}
