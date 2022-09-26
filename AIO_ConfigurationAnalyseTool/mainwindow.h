#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serial.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Slot_SerialConnected(SerialStatus status);     //连接操作后的槽函数
    void Slot_RecieveTextRefresh();                //接收文本框刷新

private slots:
    void on_pushButton_dev_clicked();
    void on_pushButton_config_clicked();
    void on_pushButton_debug_clicked();
    void on_pushButton_comm_clicked();

    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();
    void on_pushButton_Send_clicked();
    void on_pushButton_Recv_clicked();

private:
    Ui::MainWindow *ui;
    Serial     *serial;
};

#endif // MAINWINDOW_H
