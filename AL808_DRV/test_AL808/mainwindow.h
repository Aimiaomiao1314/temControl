#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../AL808/AL808.h"
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_getPV_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_DisConnect_clicked();

    void on_pushButton_ShowSetup_clicked();

    void on_pushButton_SetSL_clicked();

private:
    AL808 *al808;
    Ui::MainWindow *ui;
    QThread *thread;
signals:
   void TryConnect();
};

#endif // MAINWINDOW_H
