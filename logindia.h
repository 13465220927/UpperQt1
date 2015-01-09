#ifndef LOGINDIA_H
#define LOGINDIA_H

#include <QDialog>
#include <QtGui>
#include "qlinkqdbc.h"
//#include "qdbcformenu.h"
namespace Ui {
class Logindia;
}

class Logindia : public QDialog
{
    Q_OBJECT

public:
    explicit Logindia(QWidget *parent = 0);
    ~Logindia();

private:
    Ui::Logindia *ui;

public:
    void InitLogin();
    QPoint windowPos;
    QPoint mousePos;
    QPoint dpos;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void changeEvent(QEvent *e);
    void update_config();
    int  login_state;
    int user_state;
public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // LOGINDIA_H
