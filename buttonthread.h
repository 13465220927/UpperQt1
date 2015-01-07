#ifndef BUTTONTHREAD_H
#define BUTTONTHREAD_H

#include <QThread>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
//#include "mainwindow.h"
class ButtonThread : public QThread
{
    Q_OBJECT
public:
    explicit ButtonThread(QObject *parent = 0);

    void setMessage(QString message, QSerialPort *serialport);
    void stop();
    void senddata(QString buf);
protected:
    void run();
    void printMessage();

private:
    QSerialPort *serial;
    QString messageStr;
    volatile bool stopped;
signals:

public slots:

};

#endif // BUTTONTHREAD_H
