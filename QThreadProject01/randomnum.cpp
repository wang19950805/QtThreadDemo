#include "randomnum.h"
#include <QElapsedTimer>
#include <QDebug>


RandomNum::RandomNum()
{

}

void RandomNum::revNum(int num)
{
    m_revNum = num;

}

void RandomNum::run()
{

    qDebug()<<"生成随机数的当前线程的地址: "<<QThread::currentThread();

    //计时
    QElapsedTimer time;
    time.start();
    QVector<int> list;
    for(int i = 0; i<m_revNum; ++i)
    {
        list.push_back(rand() %100000);
    }
    int milsec = time.elapsed();
    emit sendRandomArray(list);
    qDebug()<<"生成 "<<m_revNum<<" 个随机数耗时: " << milsec <<" 毫秒";
}
