#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QRunnable>
#include <QThread>

class BubbleSort : public QObject,public QRunnable
{
        Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void revList(QVector<int> list);
    void run() override;

private:
    QVector<int> m_sortArr;
    void bubbleSort(QVector<int> &list);

signals:
    void finished(QVector<int> list);
};

#endif // BUBBLESORT_H
