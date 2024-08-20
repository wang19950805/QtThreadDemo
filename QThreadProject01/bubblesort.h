#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QThread>

class BubbleSort : public QThread
{
        Q_OBJECT
public:
    BubbleSort();
    void revList(QVector<int> list);

protected:
    void run() override;

private:
    QVector<int> m_sortArr;
    void bubbleSort(QVector<int> &list);

signals:
    void finished(QVector<int> list);
};

#endif // BUBBLESORT_H
