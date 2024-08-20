#ifndef RANDOMNUM_H
#define RANDOMNUM_H

#include <QRunnable>
#include <QThread>
#include <QVector>

class RandomNum : public QObject,public QRunnable
{
    Q_OBJECT
public:

    explicit RandomNum(QObject *parent = nullptr);
    void revNum(int num);
    void run() override;

signals:
    void sendRandomArray(QVector<int> list);
private:
    int m_revNum;



};

#endif // RANDOMNUM_H
