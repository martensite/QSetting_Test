#include "AccessListThread.h"
#include "mainwindow.h"
#include "CheckHostThread.h"
AccessListThread::AccessListThread()
{
    //QSettings *read_ini = new QSettings("host.ini", QSettings::IniFormat);
    selected=false;
    stopped=false;
}

AccessListThread::~AccessListThread()
{
        //must define..or it is errorful....
}

void AccessListThread::run()
{
    while(!stopped){
        // have selected a host  (on the listwidget) and want to read its shared list
        if (selected)
        {
            int row=list1->currentRow();
            QString host=list1->item(row)->text();
            //QString dir="Shared_List/";
            QSettings *hostini=new QSettings("host.ini",QSettings::IniFormat);
            hostini->beginGroup(host);
             QString filename=hostini->value("filename").toString();
             hostini->endGroup();

            //const QStringList childGroups=read_ini->childGroups();

            QSettings *read_sharedini=NULL;
            //QString dir="./Shared_List/";
            //filename=dir+filename;
            read_sharedini=new QSettings(filename, QSettings::IniFormat);
            read_shared(read_sharedini);
            if(this->isFinished())
                stop();
            return;
        }
        //read host list when pressing read hosts button
        QSettings *read_hostini=new QSettings("host.ini", QSettings::IniFormat);
        QStringList hosts=read_host(read_hostini);
        if(this->isFinished())
            stop();
    }
}

void AccessListThread::stop()
{
    stopped=true;
}

QStringList AccessListThread::read_host(QSettings*  read_ini)
{
    const QStringList childGroups=read_ini->childGroups();
    int i=0;
    //return a QStringList hosts
    QStringList hosts;

    foreach (const QString &childGroup, childGroups){
        //show host list
        //check hosts whether have shared files

        list1->addItem(childGroup);
        hosts.append(childGroup);
        i++;
    }
    return hosts;
}

QStringList AccessListThread::read_shared(QSettings*  read_ini)
{
    QStringList sharedfiles;
    const QStringList childGroups=read_ini->childGroups();
    int i=0;
    foreach (const QString &childGroup, childGroups){
        read_ini->beginGroup(childGroup);
        const QStringList childKeys=read_ini->childKeys();
        int j=0;
        //return a QStringList
        QStringList sharedfiles;
        foreach (const QString &childKey, childKeys){
            this->list2->addItem(read_ini->value(childKey).toString());
            j++;
        }
        read_ini->endGroup();
        i++;
    }
    return sharedfiles;
}
