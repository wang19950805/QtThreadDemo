#ifndef RANDOMNUM_H
#define RANDOMNUM_H

#include <QThread>
#include <QVector>

class RandomNum : public QThread
{
    Q_OBJECT
public:
    RandomNum();
    void revNum(int num);

protected:
    void run() override;
signals:
    void sendRandomArray(QVector<int> list);
private:
    int m_revNum;



};

#endif // RANDOMNUM_H
