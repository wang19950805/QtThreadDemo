#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randomnum.h"

#include <BubbleSort.h>
#include <Quick.h>
#include <QThreadPool>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RandomNum *randNum = new RandomNum;
    Quick *quick = new Quick;
    BubbleSort *bubble = new BubbleSort;

    connect(this,&MainWindow::starting,randNum,&RandomNum::revNum);

    connect(ui->btnStart,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        QThreadPool::globalInstance()->start(randNum);
    });

    connect(randNum,&RandomNum::sendRandomArray,quick,&Quick::revList);
    connect(randNum,&RandomNum::sendRandomArray,bubble,&BubbleSort::revList);

    connect(randNum,&RandomNum::sendRandomArray,this,[=](QVector<int> list){
        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start(quick);
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


}

MainWindow::~MainWindow()
{
    delete ui;
}


