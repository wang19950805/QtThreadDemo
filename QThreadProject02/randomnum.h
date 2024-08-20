#ifndef RANDOMNUM_H
#define RANDOMNUM_H

#include <QObject>
#include <QVector>

class RandomNum : public QObject
{
    Q_OBJECT
public:
    RandomNum();
    void revNum(int num);

    void working(int num);

signals:
    void sendRandomArray(QVector<int> list);

};

#endif // RANDOMNUM_H
