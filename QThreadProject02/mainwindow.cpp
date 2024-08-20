#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randomnum.h"
#include <BubbleSort.h>
#include <Quick.h>
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QThread *t1 = new QThread;
    QThread *t2 = new QThread;
    QThread *t3 = new QThread;

    RandomNum *randNum = new RandomNum;
    Quick *quick = new Quick;
    BubbleSort *bubble = new BubbleSort;

    randNum->moveToThread(t1);
    quick->moveToThread(t2);
    bubble->moveToThread(t3);

    connect(this,&MainWindow::starting,randNum,&RandomNum::working);

    connect(ui->btnStart,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        t1->start();
    });

    connect(randNum,&RandomNum::sendRandomArray,quick,&Quick::working);
    connect(randNum,&RandomNum::sendRandomArray,bubble,&BubbleSort::working);

    connect(randNum,&RandomNum::sendRandomArray,this,[=](QVector<int> list){
        t2->start();
        t3->start();
        for (int i = 0; i < list.size()-1; ++i) {

            ui->listWidget_random->addItem(QString::number(list.at(i)));
        }
        emit sendArrList(list);

    });

    connect(quick,&Quick::finished,this,[=](QVector<int> list){
        for (int i = 0; i < list.size()-1; ++i) {

            ui->listWidget_Quick->addItem(QString::number(list.at(i)));
        }
    });

    connect(bubble,&BubbleSort::finished,this,[=](QVector<int> list){
        for (int i = 0; i < list.size()-1; ++i) {

            ui->listWidget_Bubble->addItem(QString::number(list.at(i)));
        }
    });

    connect(this,&MainWindow::destroyed,this,[=](){
        t1->quit();
        t1->wait();
        t1->deleteLater();

        t2->quit();
        t2->wait();
        t2->deleteLater();

        t3->quit();
        t3->wait();
        t3->deleteLater();

        randNum->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}


