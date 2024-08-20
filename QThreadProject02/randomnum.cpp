#include "randomnum.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>

RandomNum::RandomNum()
{

}

void RandomNum::working(int num)
{

    qDebug()<<"生成随机数的当前线程的地址: "<<QThread::currentThread();

    //计时
    QElapsedTimer time;
    time.start();
    QVector<int> list;
    for(int i = 0; i < num; ++i)
    {
        list.push_back(rand() %100000);
    }
    int milsec = time.elapsed();
    emit sendRandomArray(list);
    qDebug()<<"生成 "<< num <<" 个随机数耗时: " << milsec <<" 毫秒";
}
