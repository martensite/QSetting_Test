#ifndef CHECKHOSTTHREAD_H
#define CHECKHOSTTHREAD_H

#include <QThread>
#include <QSettings>
#include <QListWidget>
#include <QMutex>

//Define the thread class used to handle list accessing (every host)
class CheckHostThread : public QThread
{
        Q_OBJECT
public:
    CheckHostThread(QString);
    ~CheckHostThread();
    void run();
    void check_host(QSettings* );
    QListWidget *list1;
    QListWidget *list2;
    //the hosts have shared files?
    bool have_shared;
    void stop();

signals:
    void send_to_list1(QString);
    void send_to_list2(QString);

private:
     QMutex mutex;
     QSettings *inifile;
     QString file;
     bool stopped;
};

#endif // CHECKHOSTTHREAD_H
