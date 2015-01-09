#include "logindia.h"
#include "ui_logindia.h"

Logindia::Logindia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logindia)
{
    ui->setupUi(this);
    InitLogin();
}

Logindia::~Logindia()
{
    delete ui;
}

void Logindia::InitLogin()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setMaxLength(13);
    ui->lineEdit_2->setMaxLength(9);
    ui->pushButton->setFlat(true);

    QFont font1,font2;
    font1.setFamily("宋体");
    font2.setFamily("楷体");
    font1.setPointSize(11);
    font2.setPointSize(9);
    font1.setBold(true);
    font2.setBold(true);
    ui->label_2->setFont(font2);
    ui->label_3->setFont(font2);
    ui->pushButton->setGeometry(80,250,110,34);
    ui->pushButton_2->setGeometry(420,30,17,18);
}

void Logindia::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dpos = mousePos - windowPos;
}

void Logindia::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dpos);
}

void Logindia::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch(e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:break;
    }
}


void Logindia::on_pushButton_clicked()
{
    QLinkQDBC linkStudent;
    linkStudent.OpenQDBC();
    linkStudent.SelectQDBC(ui->lineEdit->text(),ui->lineEdit_2->text());
    linkStudent.CloseQDBC();
    switch(linkStudent.sign){
    case 0:

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        break;
    case 1:
        accept();
        break;


    }
}

void Logindia::on_pushButton_2_clicked()
{
    exit(0);
}

