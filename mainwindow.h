#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QFile>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void receive_hosts_thread(QString);
    void receive_files_thread(QString);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_listWidget_itemSelectionChanged();
    void on_readHostButton_clicked(bool checked);
};



#endif // MAINWINDOW_H


