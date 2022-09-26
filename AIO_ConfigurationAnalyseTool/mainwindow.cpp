#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new Serial;
    //连接串口连接情况信号
    //connect(serial,Serial::Signal_StatusChange,this,Slot_SerialConnected);

    //连接串口接收信号   槽函数不接收变量,由槽函数再次通过Serial的接口获得缓存区的引用
    //connect(serial,Serial::Signal_RecieveData,this,Slot_RecieveTextRefresh);

    this->setWindowTitle("AllinOne配置调试工具");
    this->setWindowIcon(QIcon(":/new/prefix1/images/Portfolio.ico"));

    QPixmap currConnStateIcon(":/new/prefix1/images/disconnected.png");
    currConnStateIcon = currConnStateIcon.scaled(ui->label_currentConnState->width(), ui->label_currentConnState->height());
    ui->label_currentConnState->setPixmap(currConnStateIcon);
}

void MainWindow::Slot_RecieveTextRefresh()
{
    //QByteArray RecieveSbuffer = serial->Read_RecieveSbuffer();  //获取接收缓存
    QString RecieveText;                            //接收框将要显示的字符串
    RecieveText.clear();
}

void MainWindow::Slot_SerialConnected(SerialStatus status)
{
    bool enable;
    QString temp;
}

void MainWindow::on_pushButton_dev_clicked()
{
    qDebug() << "MainWindow on_pushButton_dev_clicked" << endl;
    ui->stackedWidget->setCurrentWidget(ui->page_dev);
}

void MainWindow::on_pushButton_config_clicked()
{
    qDebug() << "MainWindow on_pushButton_config_clicked" << endl;
    ui->stackedWidget->setCurrentWidget(ui->page_config);
}

void MainWindow::on_pushButton_debug_clicked()
{
    qDebug() << "MainWindow on_pushButton_debug_clicked" << endl;
    ui->stackedWidget->setCurrentWidget(ui->page_debug);
}

void MainWindow::on_pushButton_comm_clicked()
{
    qDebug() << "MainWindow on_pushButton_comm_clicked" << endl;
    ui->stackedWidget->setCurrentWidget(ui->page_comm);
}

void MainWindow::on_pushButton_Connect_clicked()
{
    qDebug() << "MainWindow on_pushButton_Send_clicked" << endl;

    serial->Connect();

    QPixmap currConnStateIcon(":/new/prefix1/images/connected.png");
    currConnStateIcon = currConnStateIcon.scaled(ui->label_currentConnState->width(), ui->label_currentConnState->height());
    ui->label_currentConnState->setPixmap(currConnStateIcon);
}

void MainWindow::on_pushButton_Disconnect_clicked()
{
    qDebug() << "MainWindow on_pushButton_Disonnect_clicked" << endl;

    serial->Disconnect();

    QPixmap currConnStateIcon(":/new/prefix1/images/disconnected.png");
    currConnStateIcon = currConnStateIcon.scaled(ui->label_currentConnState->width(), ui->label_currentConnState->height());
    ui->label_currentConnState->setPixmap(currConnStateIcon);
}

void MainWindow::on_pushButton_Send_clicked()
{
    qDebug() << "MainWindow on_pushButton_Send_clicked" << endl;

    char res_data[256] = {0};

    for(int i = 0; i < 256; i++)
    {
        res_data[i] = i;
    }

    //char res_data[3] = {'0', '1', '2'};
    serial->Serial_Send(res_data, sizeof(res_data));

    //QByteArray res_arr(res_data, sizeof(res_data));

    //serial->Serial_Send(res_arr);
    //serial->Serial_Send("Hello QT!");
}

void MainWindow::on_pushButton_Recv_clicked()
{
    qDebug() << "MainWindow on_pushButton_Recv_clicked" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

