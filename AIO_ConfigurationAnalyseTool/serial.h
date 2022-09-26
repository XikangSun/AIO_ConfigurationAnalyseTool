#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

enum FunctionCode
{
    ConnectAIO = 0,
};

enum ConnectionState
{
    Connecting,
    Connected
};

enum SerialStatus
{
    statusConnect,
    statusDisconnect,
    statusConnectErr
};

class Serial : public QObject
{
    Q_OBJECT
public:
    Serial();
    ~Serial();
    int RecievByte_Count;
    int SendByte_Count;
    //发送函数,port未连接直接返回
    void Serial_Send(char*dat);
    void Serial_Send(QString&str, bool Hex=false, bool Utf8 = true);
    void Serial_Send(QByteArray&arr);
    void Serial_Send(char *dat, int len);
    //读取串口接收
    QByteArray& Read_RecieveSbuffer();
    //清除缓存
    void Serial_SbufferClear();
    //连接和解除 串口
    bool Connect();                                      //连接 port的ReadyRead信号 和 Slot_SerialRecieve槽
    void Disconnect();                                  //解除 ReadyRead信号 和 Slot_SerialRecieve槽 的连接
public slots:
    void Slot_SerialRecieve();                          //串口接收

//signals:
    //void Signal_StatusChange(SerialStatus status);      //串口连接状态信号
    //void Signal_RecieveData(QByteArray&dat);            //串口接收信号

private:
    bool wait_reply = false;
    QByteArray  RecieveSbuff;             //串口接收缓存
    QSerialPort *port = nullptr;          //串口句柄
    SerialStatus status;                  //串口连接状态
};

#endif // SERIAL_H
