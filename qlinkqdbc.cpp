#include "qlinkqdbc.h"

QLinkQDBC::QLinkQDBC()
{
}


void QLinkQDBC::OpenQDBC()
{
    db=QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString("DRIVER={SQL SERVER};SERVER=%1;PORT=%2;DATABASE=%3;UID=%4;PWD=%5;").arg("127.0.0.1").arg("1433").arg("ZigBeeDb").arg("zigbee").arg("mcmdhr");
    db.setDatabaseName(dsn);
    if (!db.open())
    {
        //QMessageBox::critical(0, qApp->tr("数据连接异常！"), db.lastError().databaseText(), QMessageBox::Cancel);
    }
}

void QLinkQDBC::CloseQDBC()
{
    db.close();
    QSqlDatabase::removeDatabase("ZigBeeDb");
}

void QLinkQDBC::SelectQDBC(QString str1,QString str2)
{
    QSqlQuery query;
    QString name;{
        name = QSqlDatabase::database().connectionName();
    }
    sign=0;
    query.exec("SELECT * FROM tblUser");
    if(str1 == NULL)
    {
        sign == 2;
        return;
    }
    if(str2 == "")
    {
        sign == 3;
        return;
    }
    while(query.next())
    {
        if(str1 == query.value(0).toString()&&str2 == query.value(1).toString())
        {
            sign =1;
            break;
        }
        else if(str1 == query.value(0).toString()&&str2 != query.value(1).toString())
        {
            sign =4;
            break;

        }
    }
}
