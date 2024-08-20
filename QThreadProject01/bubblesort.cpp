#include "bubblesort.h"
#include <QDebug>

BubbleSort::BubbleSort()
{

}

void BubbleSort::revList(QVector<int> list)
{
     m_sortArr = list;
}

void BubbleSort::run()
{
     //冒泡排序
     qDebug()<<"冒泡排序的当前线程的地址: "<<QThread::currentThread();
     //计时
     QElapsedTimer time;
     time.start();
     bubbleSort(m_sortArr);
     int milsec = time.elapsed();
     emit finished(m_sortArr);
     qDebug()<<"冒泡排序耗时: " << milsec <<" 毫秒";
}



void BubbleSort::bubbleSort(QVector<int> &list) {
     int n = list.size();
     for (int i = 0; i < n-1; i++) {
         for (int j = 0; j < n-i-1; j++) {
             if (list[j] > list[j+1]) {
                 // 交换 vec[j] 和 vec[j+1]
                 int temp = list[j];
                 list[j] = list[j+1];
                 list[j+1] = temp;
             }
         }
     }
}

