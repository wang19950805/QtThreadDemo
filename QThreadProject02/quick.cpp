#include "quick.h"
#include <QDebug>


Quick::Quick()
{

}

void Quick::working(QVector<int> list)
{
    //快速排序
    qDebug()<<"快速排序的当前线程的地址: "<<QThread::currentThread();
    //计时
    QElapsedTimer time;
    time.start();
    quicksort(list,0,list.size() -1);

    int milsec = time.elapsed();
    emit finished(list);
    qDebug()<<"快速排序耗时: " << milsec <<" 毫秒";
}


void Quick::quicksort(QVector<int> &list, int low, int high) {
    if (low < high) {
        // 获取分区后的枢纽位置
        int pivot_index = partition(list, low, high);

        // 分别对枢纽左右两边的子数组进行递归排序
        quicksort(list, low, pivot_index - 1);
        quicksort(list, pivot_index + 1, high);
    }
}

int Quick:: partition(QVector<int> &list, int low, int high) {
    int pivot = list[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (list[j] < pivot) {
            i++;

            // 交换 arr[i] 和 arr[j]
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }

    // 将枢纽元素放置到正确的位置
    int temp = list[i + 1];
    list[i + 1] = list[high];
    list[high] = temp;

    return i + 1;
}

