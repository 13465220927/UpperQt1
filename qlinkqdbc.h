#ifndef QLINKQDBC_H
#define QLINKQDBC_H
#include "logindia.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
class QLinkQDBC
{
public:
    QLinkQDBC();
    void OpenQDBC();
    void CloseQDBC();
    void SelectQDBC(QString str1,QString str2);
    int sign;
    QSqlDatabase db;
};

#endif // QLINKQDBC_H
