#ifndef QUICK_H
#define QUICK_H

#include <QRunnable>
#include <QThread>
#include <QVector>
#include <QVector>

class Quick : public QObject,public QRunnable
{
    Q_OBJECT
public:

     explicit Quick(QObject *parent = nullptr);
    void revList(QVector<int> list);
    void run() override;

private:

    QVector<int> m_sortArr;

    int partition(QVector<int> &list, int low, int high);
    void quicksort(QVector<int> &list, int low, int high);

signals:
    void finished(QVector<int> list);


};

#endif // QUICK_H
