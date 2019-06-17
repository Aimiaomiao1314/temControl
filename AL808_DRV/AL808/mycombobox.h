#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H
#include<QComboBox>


class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComboBox(QWidget *parent);
    ~MyComboBox();
protected:

    virtual void mousePressEvent(QMouseEvent *e);  //添加鼠标点击事件

signals:

    void clicked();
};

#endif // MYCOMBOBOX_H
