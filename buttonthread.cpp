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

void ButtonThread::setMessage(QString message){
    messageStr = message;
}

void ButtonThread::printMessage(){
    qDebug()<<messageStr;
    sleep(1);
}
