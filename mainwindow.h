#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QString>
#include <QSettings>
#include <QStringList>
#include "QCloseEvent"
#include <windows.h>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QtCore>
#include "buttonthread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QTcpServer *tcpServer;
    QTcpSocket *clientConnect;
    QSerialPort *serialport;
    void InitUI();
    void senddata(QString buf);
    void dataCalcAndSend();
    QString GetCommName(int index, QString keyorvalue);
    ~MainWindow();
//signals:
//    void writeFinish();
private slots:
   // void timerSendData();
    void openPort();
    void readdata();
    void btn_send_clicked();
    void btn_led1_clicked();
    void btn_led2_clicked();
    void btn_led3_clicked();
    void btn_led4_clicked();
    void sendMessage();
    void sendToSerial();
    //void dataCalcAndSend();
    void showData();
    void newConnect();

    void on_btnRelay_clicked();
    void on_btnInfrared_clicked();
    void on_btnSmoke_clicked();
    void on_btnTemp_clicked();
    void on_btnLight_clicked();
    void btn_starttcp_clicked();

    void on_btnShowData_clicked();

signals:
    void isShow();
private:
    QString sbuf;
    QString portName;
    QStringList m_listcomboName;
    HKEY hKey;
    qint16 serCount;
    qint8 bit3;
    qint16 countSerialSend;
    ButtonThread threadSmoke;
    ButtonThread threadTemp;
    ButtonThread threadLight;

    ButtonThread threadSend;
    QThread xxx;
    bool flagLED;
    bool flagRelay;
    bool flagInfrared;
    bool flagSmoke;
    bool flagTemp;
    bool flagLight;
    bool flagShow;
    bool flagCon;

    QByteArray data;
    QByteArray dataTemp;
    QByteArray dataSmoke;
    QByteArray dataLight;
    QByteArray str;
    QByteArray strPeople;

    wchar_t keyname[256]; //键名数组
    char keyvalue[256];  //键值数组
    DWORD keysize, type, valuesize;
    int indexnum;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
