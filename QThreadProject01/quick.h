#ifndef QUICK_H
#define QUICK_H

#include <QThread>
#include <QVector>
#include <QVector>

class Quick : public QThread
{
    Q_OBJECT
public:
    Quick();
    void revList(QVector<int> list);
protected:
    void run() override;

private:

    QVector<int> m_sortArr;

    int partition(QVector<int> &list, int low, int high);
    void quicksort(QVector<int> &list, int low, int high);

signals:
    void finished(QVector<int> list);


};

#endif // QUICK_H
