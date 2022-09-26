#include "serial.h"
#include <QDebug>

Serial::Serial()
{
    RecieveSbuff.clear();
    status = statusDisconnect;
    RecievByte_Count = 0;
    SendByte_Count = 0;
}

bool Serial::Connect()
{
    if(status == statusConnect)
        return false;

    QList<QSerialPortInfo>  List = QSerialPortInfo::availablePorts(); // 串口信息列表

    foreach (const QSerialPortInfo&info, List)
    {
        qDebug() << "portName: " << info.portName() << endl;

        port = new QSerialPort;
        port->setPort(info);
        port->setBaudRate(QSerialPort::BaudRate::Baud115200);
        port->setStopBits(QSerialPort::StopBits::OneStop );
        port->setDataBits(QSerialPort::DataBits::Data8);
        port->setParity(QSerialPort::Parity::NoParity);

        if(port->open(QIODevice::ReadWrite))
        {
            status = statusConnect;
            //emit Signal_StatusChange(statusConnect);
            connect(port, &QSerialPort::readyRead, this, &Serial::Slot_SerialRecieve);

            char res_data[3] = {FunctionCode::ConnectAIO, 1, ConnectionState::Connecting};
            Serial_Send(res_data, sizeof(res_data));

            return true;
        }else
        {
            delete port;
            port = NULL;
            status = statusDisconnect;
            //emit Signal_StatusChange(statusConnectErr);
            return false;
        }
    }
    //emit Signal_StatusChange(statusConnectErr);
    return false;
}

void Serial::Slot_SerialRecieve()
{
    RecieveSbuff = port->readAll();
    RecievByte_Count = RecieveSbuff.length();

    qDebug() << "Serial Slot_SerialRecieve: len = "  << RecievByte_Count << endl;

    for(int i = 0; i < RecievByte_Count; i++)
    {
        qDebug()  << (unsigned char)RecieveSbuff[i] << " ";
    }

    //emit Signal_RecieveData(RecieveSbuff);
}

void Serial::Serial_Send(QString &str, bool Hex, bool Utf8)
{
    if(status == statusConnect)
    {
        QByteArray dat;
        if(Utf8)
            dat = str.toUtf8();
        else
            dat = str.toLocal8Bit();
        if(Hex)
            dat = dat.toHex();
        Serial_Send(dat);
        SendByte_Count += dat.length();
    }
}

void Serial::Serial_Send(QByteArray &arr)
{
    if(status == statusConnect)
    {
        port->write(arr);
        SendByte_Count += arr.length();
    }
}

void Serial::Serial_Send(char *dat)
{
    if(status == statusConnect)
    {
        while(*dat!='\0')
        {
            port->putChar(*dat);
            dat++;
            SendByte_Count++;
        }
    }
}

void Serial::Serial_Send(char *dat, int len)
{
    qDebug() << "Serial Serial_Send: len = "  << len << endl;
    if(status == statusConnect)
    {
        port->write(dat, len);
    }
}

QByteArray& Serial::Read_RecieveSbuffer()
{
    return RecieveSbuff;
}

void Serial::Disconnect()
{
    if(status == statusConnect)
    {
        disconnect(port, &QSerialPort::readyRead, this, &Serial::Slot_SerialRecieve);
        port->close();
        delete port;
        port = nullptr;
        status = statusDisconnect;
        //emit Signal_StatusChange(status);
    }
}

void Serial::Serial_SbufferClear()
{
    RecieveSbuff.clear();
    SendByte_Count = 0;
    RecievByte_Count = 0;
}

Serial::~Serial()
{
    Disconnect();
}
