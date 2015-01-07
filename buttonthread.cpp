#include "buttonthread.h"
#include <QDebug>

ButtonThread::ButtonThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
}

void ButtonThread::run(){
    while (!stopped){
        printMessage();
    }
    stopped = false;
}

void ButtonThread::stop(){
    stopped = true;
}

void ButtonThread::setMessage(QString message, QSerialPort *serialport){
    messageStr = message;
    serial = serialport;
}

void ButtonThread::senddata(QString buf){
    qDebug()<<buf;
    serial->write(buf.toLatin1());
}

void ButtonThread::printMessage(){
    senddata(messageStr);
   // qDebug()<<messageStr;
    sleep(2);
}


