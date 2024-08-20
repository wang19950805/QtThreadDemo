#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QObject>

class BubbleSort : public QObject
{
        Q_OBJECT
public:
    BubbleSort();
    void working(QVector<int> list);

private:
    QVector<int> m_sortArr;
    void bubbleSort(QVector<int> &list);

signals:
    void finished(QVector<int> list);
};

#endif // BUBBLESORT_H
