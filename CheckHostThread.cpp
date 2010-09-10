#include "CheckHostThread.h"
#include "mainwindow.h"

//construnctor of CheckHostThread
CheckHostThread::CheckHostThread(QString file)
{
    have_shared=false;
    (this->file)=file;
    stopped=false;
}
//destructor of CheckHostThread
CheckHostThread::~CheckHostThread()
{
}

void CheckHostThread::run()
{
    while(!stopped){
        //this->mutex.lock();
        //QSettings *checkini=new QSettings(file,QSettings::IniFormat);
        inifile=new QSettings(this->file,QSettings::IniFormat);
        check_host(inifile);
        if(this->isFinished())
            stop();
    }
    //this->mutex.unlock();
}
//Stop function, set stopped to true
void CheckHostThread::stop()
{
    stopped=true;
}

void CheckHostThread::check_host(QSettings*  ini)
{
    QStringList childGroups=ini->childGroups();
    QStringList allKeys=ini->allKeys();
    //QMutexLocker locker(&mutex);
        //List hosts that have shared files
        foreach (const QString &childGroup, childGroups)
        {
            //Check whether that host has shared anything
            ini->beginGroup(childGroup);
            if(ini->childKeys().isEmpty())
                break;
            else
                //list1->addItem(childGroup);
                this->mutex.lock();
                emit send_to_list1(childGroup);
                this->mutex.unlock();
            ini->endGroup();
        }
        //list all shared files
        foreach (const QString &key, allKeys)
        {
            this->mutex.lock();
            //list2->addItem(ini->value(key).toString());
            emit send_to_list2(ini->value(key).toString());
            this->mutex.unlock();
         }

    }
