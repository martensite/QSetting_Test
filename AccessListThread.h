#ifndef ACCESSLISTTHREAD_H
#define ACCESSLISTTHREAD_H


#include <QThread>
#include <QSettings>
#include <QListWidget>

//Define the thread class used to handle list accessing (every host)
class AccessListThread : public QThread
{
        Q_OBJECT
public:
    AccessListThread();
    ~AccessListThread();
    void run();
    QStringList read_host(QSettings* );
    QStringList read_shared(QSettings*  read_ini);
    QListWidget *list1;
    QListWidget *list2;
    //for selected host to show its shared files
    bool selected;
    void stop();
private:
    //QFile inifile;
    QSettings inifile;
    bool stopped;
};

#endif // ACCESSLISTTHREAD_H
