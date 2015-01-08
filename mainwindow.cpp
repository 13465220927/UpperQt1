#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    countSerialSend = 0;
    bit3 = 0;
    flagLED = false;
    flagRelay = false;
    flagInfrared = false;
    flagSmoke = false;
    flagTemp = false;
    flagLight = false;
    tcpServer=new QTcpServer(this);
    sbuf = "SerialPortOpen";
    if(!tcpServer->listen(QHostAddress::Any,8812))
    {//监听本机6666端口。若出错，则输出错误信息，并关闭
      qDebug()<<tcpServer->errorString();
      close();
    }
    else{
        ui->lbConnStatus->setText("ListenSucc");
    }
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnect())); //连接信号和相应槽函数

    serialport = new QSerialPort(this);
    connect(ui->btnOpenSerial, SIGNAL(clicked()), this, SLOT(openPort()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(btn_send_clicked()));

    connect(ui->btnLED1, SIGNAL(clicked()), this, SLOT(btn_led1_clicked()));
    connect(ui->btnLED2, SIGNAL(clicked()), this, SLOT(btn_led2_clicked()));
    connect(ui->btnLED3, SIGNAL(clicked()), this, SLOT(btn_led3_clicked()));
    connect(ui->btnLED4, SIGNAL(clicked()), this, SLOT(btn_led4_clicked()));
}

/*Send Message to Android ,
 * use by TCP socket.
 * and this is the TCPServer
*/

void MainWindow::newConnect(){
    clientConnect = tcpServer->nextPendingConnection();
    connect(clientConnect, SIGNAL(readyRead()), this, SLOT(sendMessage()));
}
void MainWindow::sendMessage(){
    qDebug()<<"Before Sent";
    QByteArray block;
    QByteArray readData;
    QDataStream out(&block, QIODevice::WriteOnly);
    QString ss;
    QByteArray strDataNoHandle;
    out.setVersion(QDataStream::Qt_4_8);
    out<<(quint16)0;
    //out<<tr("HOST Connect!");
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));

    connect(clientConnect, &QTcpSocket::disconnected, clientConnect,&QTcpSocket::deleteLater);
    qDebug()<<clientConnect->peerAddress();
    readData = clientConnect->readAll();
    if (readData == "HTC 802d"){
        qDebug()<<"李沛然的手机发了个数据过来！";
        ss = "000000000000";
        clientConnect->write(ss.toStdString().c_str(),strlen(ss.toStdString().c_str()));
        //clientConnect->disconnectFromHost();

        qDebug()<<ss;
        qDebug()<<readData;
    }
    if (readData == "Read"){
//        QString str = sbuf;
//        QByteArray ba = str.toLatin1();
//        ch = ba.data();
        strDataNoHandle[0] = str[3];
        strDataNoHandle[1] = (flagLED+48);
        strDataNoHandle[2] = (flagRelay+48);
        strDataNoHandle[3] = (flagInfrared+48);
        //char* ch;
        //QString str = ui->lblSmoke->text();
        //QByteArray ba = str.toLatin1();
        //ch = ba.data();
        strDataNoHandle[4] = dataSmoke[0];
        strDataNoHandle[5] = dataSmoke[1];
        strDataNoHandle[6] = dataSmoke[2];

        strDataNoHandle[7] = dataTemp[0];
        strDataNoHandle[8] = dataTemp[1];
        strDataNoHandle[9] = dataTemp[2];
        strDataNoHandle[10] = dataTemp[3];

        strDataNoHandle[11] = dataLight[0];
        strDataNoHandle[12] = dataLight[1];


        qDebug()<<strDataNoHandle;


    }
    if (readData == "10"){

    }

    if (readData == "11"){

    }

    if (readData == "20"){

    }

    if (readData == "21"){

    }


    //if (readData == "")

    ui->lbConnStatus->setText("Client Connect Success");
}

void MainWindow::InitUI(){//Read the COM from regedit
    //串口
    QString path = "HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
    QSettings *settings = new QSettings( path, QSettings::NativeFormat);
    QStringList key = settings->allKeys();
    for(int i=0; i < (int)key.size(); i++)
    {
        m_listcomboName.append(GetCommName(i, "value"));
    }
    ui->cbSerial->addItems(m_listcomboName);

    //
}

void MainWindow::openPort(){//Open the Port and Ready to read from COM
    portName = ui->cbSerial->currentText();
    serialport->setPort(QSerialPortInfo(portName));
    qDebug()<<portName;
    if (serialport->open(QIODevice::ReadWrite)){
        QMessageBox box;
        box.setText("串口打开成功！");
        box.exec();
        serialport->setBaudRate(QSerialPort::Baud115200);
        serialport->setDataBits(QSerialPort::Data8);
        serialport->setParity(QSerialPort::NoParity);
        serialport->setStopBits(QSerialPort::OneStop);
        serialport->setFlowControl(QSerialPort::NoFlowControl);
        //senddata(sbuf);
        connect(serialport,SIGNAL(readyRead()), this, SLOT(readdata()));
    }else{
        QMessageBox box;
        box.setText("串口打开失败！");
        box.exec();
    }
}

QString MainWindow::GetCommName(int index, QString keyorvalue)//This method is search from the Internet
{
    QString commresult;
    if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),0,KEY_READ,&hKey)!=0)
    {
        QString error="Cannot open regedit!";//无法打开注册表时返回error
        return error;
    }
    QString keymessage;//键名
    QString message;
    QString valuemessage;//键值
    indexnum = index;//要读取键值的索引号
    keysize = sizeof(keyname);
    valuesize = sizeof(keyvalue);
    if (::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)//列举键名和值
    {
        for (DWORD i = 0; i < keysize; i++)
        {
            message=keyname[i];
            keymessage.append(message);
        }// for(int i=0;i<=keysize;i++)    读取键名
        for (DWORD j = 0; j < valuesize; j++)
        {
            if(keyvalue[j] != 0x00)
            {
                valuemessage.append(keyvalue[j]);
            }
        }//for(int j=0;j<valuesize;j++) 读取键值
        if(keyorvalue == "key")
        {
            commresult = keymessage;
        }
        if(keyorvalue == "value")
        {
            commresult = valuemessage;
        }
    }
    else
    {
        commresult = "nokey";
    } //if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0) 列举键名和值
    ::RegCloseKey(hKey);//关闭注册表
    return commresult;
}
/*Method of Button while we Clicked it*/
void MainWindow::btn_send_clicked(){
    sbuf = ui->teSendData->text();
    senddata(sbuf);
}

void MainWindow::btn_led2_clicked(){
    QMessageBox box;
    box.setText("麻蛋别点了,这个灯不能用！IO口被占了傻吊！");
    box.exec();
    sbuf ="L2";
    //senddata(sbuf);
}

void MainWindow::btn_led3_clicked(){
    QMessageBox box;
    box.setText("麻蛋别点了,这个灯不能用！IO口被占了傻吊！");
    box.exec();
    sbuf ="L3";
   // senddata(sbuf);
}

void MainWindow::btn_led4_clicked(){
    QMessageBox box;
    box.setText("麻蛋别点了,这个灯不能用！IO口被占了傻吊！");
    box.exec();
    sbuf ="L4";
   // senddata(sbuf);
}

void MainWindow::senddata(QString buf){
    qDebug()<<buf;
    serCount = serialport->write(buf.toLatin1());

    //qDebug()<<serCount;

}

void MainWindow::readdata(){    //Read data from SerialPort and According it on UI
    str = serialport->readAll();
    qDebug()<<str;
    qint8 num = (qint8)(str[1]-48);

    switch (num) {
    case 3:
        data[0]=str[3];
        ui->lblInfrared->setText(data);
        break;
    case 4:
        dataSmoke[0]=str[3];
        dataSmoke[1]=str[4];
        dataSmoke[2]=str[5];
        ui->lblSmoke->setText(dataSmoke);
        break;
    case 5:
        dataTemp[0]=str[3];
        dataTemp[1]=str[4];
        dataTemp[2]=str[5];
        dataTemp[4]=str[6];
        ui->lblTemp->setText(dataTemp);
        break;
    case 6:
        dataLight[0]=str[3];
        dataLight[1]=str[4];
        ui->lblLight->setText(dataLight);
        break;
    default:
        break;
    }
    ui->teRecData->insertPlainText(str);
    ui->teRecData->insertPlainText("\n");
}

void MainWindow::dataCalcAndSend(){//Calc and Deal the Data,and turn it into a QString:sbuf

    bit3+=32;
    char str = (char)bit3;
    sbuf += str;
    sbuf += "0000#";

    threadSend.setMessage(sbuf, serialport);//a thread,to send String use SerialPort
    threadSend.start();

    bit3-=32;
    qDebug()<<"bit3="<<bit3;

}

void MainWindow::sendToSerial(){

}
MainWindow::~MainWindow()
{
    threadSend.stop();//Stop the Thread before destroy UI
    threadSend.wait();

    if(serialport->isOpen())//Close the SerialPort before destroy UI
    {
        serialport->close();
    }
    delete ui;
}

void MainWindow::btn_led1_clicked(){//LED
    flagLED = !flagLED;
    if (flagLED){countSerialSend++; bit3+=1; ui->btnLED1->setText(tr("关闭"));}
       else{countSerialSend--; bit3-=1;ui->btnLED1->setText(tr("开启"));}
    sbuf = "*1";
    dataCalcAndSend();


}

void MainWindow::on_btnRelay_clicked(){//继电器
    flagRelay = !flagRelay;
    if (flagRelay){countSerialSend++; bit3+=2; ui->btnRelay->setText(tr("关闭"));}
    else{countSerialSend--; bit3-=2; ui->btnRelay->setText(tr("开启"));}
    sbuf = "*2";
    dataCalcAndSend();

}

void MainWindow::on_btnInfrared_clicked(){//红外
    flagInfrared = !flagInfrared;
    if (flagInfrared){countSerialSend++; bit3+=4; ui->btnInfrared->setText(tr("关闭"));}
    else{countSerialSend--;bit3-=4;ui->btnInfrared->setText(tr("开启"));}
    sbuf = "*3";
    dataCalcAndSend();

}

void MainWindow::on_btnSmoke_clicked(){//烟雾
    flagSmoke = !flagSmoke;
    if (flagSmoke){countSerialSend++; bit3+=8; ui->btnSmoke->setText(tr("关闭"));}
    else{countSerialSend--;bit3-=8;ui->btnSmoke->setText(tr("开启"));}
    sbuf = "*4";
    dataCalcAndSend();

}

void MainWindow::on_btnTemp_clicked(){//温度
    flagTemp = !flagTemp;
    if (flagTemp){countSerialSend++; bit3+=16; ui->btnTemp->setText(tr("关闭"));}
    else{countSerialSend--;bit3-=16;ui->btnTemp->setText(tr("开启"));}
    sbuf = "*5";
    dataCalcAndSend();

}

void MainWindow::on_btnLight_clicked(){//光敏
    flagLight = !flagLight;
    if (flagLight){countSerialSend++; bit3+=32; ui->btnLight->setText(tr("关闭"));}
    else{countSerialSend--;bit3-=32;ui->btnLight->setText(tr("开启"));}
    sbuf = "*6";
    dataCalcAndSend();

}
