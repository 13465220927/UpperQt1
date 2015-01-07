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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QTcpServer *tcpServer;
    QSerialPort *serialport;
    void InitUI();
    void senddata(QString buf);
    QString GetCommName(int index, QString keyorvalue);
    ~MainWindow();
private slots:
    void openPort();
    void readdata();
    void btn_send_clicked();
    void btn_led1_clicked();
    void btn_led2_clicked();
    void btn_led3_clicked();
    void btn_led4_clicked();
    void sendMessage();

    void on_btnRelay_clicked();
    void on_btnInfrared_clicked();
    void on_btnSmoke_clicked();
    void on_btnTemp_clicked();
    void on_btnLight_clicked();

    void startOrStopThreadSmoke();
    void startOrStopThreadTemp();

private:
    QString sbuf;
    QString portName;
    QStringList m_listcomboName;
    HKEY hKey;

    Thread threadSmoke;

    static bool flagLED = false;
    static bool flagRelay = false;
    static bool flagInfrared = false;
    static bool flagSmoke = false;
    static bool flagTemp = false;
    static bool flagLight = false;

    wchar_t keyname[256]; //键名数组
    char keyvalue[256];  //键值数组
    DWORD keysize, type, valuesize;
    int indexnum;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
