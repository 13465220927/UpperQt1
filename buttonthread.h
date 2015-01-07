#ifndef BUTTONTHREAD_H
#define BUTTONTHREAD_H

#include <QThread>
#include <QString>

class ButtonThread : public QThread
{
    Q_OBJECT
public:
    explicit ButtonThread(QObject *parent = 0);

    void setMessage(QString message);
    void stop();

protected:
    void run();
    void printMessage();

private:
    QString messageStr;
    volatile bool stopped;
signals:

public slots:

};

#endif // BUTTONTHREAD_H
