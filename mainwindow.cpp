#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QThread>
#include "AccessListThread.h"
#include "CheckHostThread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_readHostButton_clicked(bool checked)
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();

    QSettings *hostini=new QSettings("host.ini",QSettings::IniFormat);
    QStringList childGroups=hostini->childGroups();

    CheckHostThread  *hostthread=0;

    foreach (const QString &childGroup, childGroups){
        hostini->beginGroup(childGroup);
        QString host=hostini->value("filename").toString();
        hostini->endGroup();

        //produce threads for every host
        hostthread=new CheckHostThread(host);
        QObject::connect(hostthread,SIGNAL(send_to_list1(QString)),this,SLOT(receive_hosts_thread(QString)));
        QObject::connect(hostthread,SIGNAL(send_to_list2(QString)),this,SLOT(receive_files_thread(QString)));

        //hostthread->list1=ui->listWidget;
        //hostthread->list2=ui->listWidget_2;
        hostthread->start();
    }

    //Connect thread'signal and ui's slot
    //connect(readini, SIGNAL(read_host()),ui->listWidget, SLOT(clear()));
}

// Read host's shared files using on_listWidget_itemSelectionChanged function
void MainWindow::on_listWidget_itemSelectionChanged()
{
    //produce threads for every host
    /*
    foreach (const QString &childGroup, childGroups){
        QString checkhost="checkhost";
        //hostthread=checkhost+childGroup;
        CheckHostThread  *hostthread=new CheckHostThread();
        hostthread->start();
    }
    */
    AccessListThread *readshared=new AccessListThread();
    readshared->list1=ui->listWidget;
    readshared->list2=ui->listWidget_2;
    readshared->selected=true;
    ui->listWidget_2->clear();
    readshared->start();
}
//Processing the received data from threads
void MainWindow::receive_hosts_thread(QString host){
        ui->listWidget->addItem(host);
}
void MainWindow::receive_files_thread(QString file){
        ui->listWidget_2->addItem(file);
}
