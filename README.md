# Qt多线程的使用   
    
   ## 案例中使用RandomNum类来生成十万个随机数,并使用BubbleSort类和Quick类对十万个随机数进行冒泡排序和快速排序

### Demo1:
  
 #### 1.将该三个类都继承QThread类,并重写run()方法,点击开始按钮生成随机数
 ```c++     
            class RandomNum : public QThread{}
            class BubbleSort : public QThread{}
            class Quick : public QThread{}
             
            connect(this,&MainWindow::starting,randNum,&RandomNum::revNum);
            connect(ui->btnStart,&QPushButton::clicked,this,[=](){
                //发送信号,生成十万个随机数
                emit starting(10000);
                randNum->start();
            });
 ```
            
        
 ####  2.RandomNum在run()方法中生成随机数完成后,发送sendRandomArray()的信号,在mainwindow中连接的信号槽函数将剩余两个子线程启动
```c++      
            connect(randNum,&RandomNum::sendRandomArray,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {
                    bubble->start();
                    quick->start();
                    ui->listWidget_random->addItem(QString::number(list.at(i)));
                }
                //发送排序信号,将生成的随机数list传递
                emit sendArrList(list);      
            });
```
#### 3.BubbleSort::run()和Quick::run()执行完毕后,发送finished()信号,在主线程中进行ui数据显示
```c++       
            connect(quick,&Quick::finished,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {
                    ui->listWidget_Quick->addItem(QString::number(list.at(i)));
                }
            });

            connect(bubble,&BubbleSort::finished,this,[=](QVector<int> list){
                 for (int i = 0; i < list.size()-1; ++i) 
                  ui->listWidget_Bubble->addItem(QString::number(list.at(i)));
                }
            });
```
#### 4.回收资源
```c++ 
            connect(this,&MainWindow::destroyed,this,[=](){
                randNum->quit();
                randNum->wait();
                randNum->deleteLater();
        
                bubble->quit();
                bubble->wait();
                bubble->deleteLater();
        
                quick->quit();
                quick->wait();
                quick->deleteLater();
            });
```

### Demo2:  

 #### 1.将该三个类都继承QObject类,三个对象不在是线程对象,不需要重写run()方法,只需要编写需要执行的任务方法即可

 ```c++     
            class RandomNum : public QObject{ void working(int num); }
            class BubbleSort : public QObjectd{ void working(QVector<int> list);}
            class Quick : public QObject{ void working(QVector<int> list); }
             
            connect(this,&MainWindow::starting,randNum,&RandomNum::revNum);
            connect(ui->btnStart,&QPushButton::clicked,this,[=](){
                //发送信号,生成十万个随机数
                emit starting(10000);
                randNum->start();
            });
 ```
#### 2.创建三个子线程对象,调用moveToThread()方法,将任务对象加入到子线程中

 ```c++     
            QThread *t1 = new QThread;
            QThread *t2 = new QThread;
            QThread *t3 = new QThread;

            RandomNum *randNum = new RandomNum;
            Quick *quick = new Quick;
            BubbleSort *bubble = new BubbleSort;
    
            randNum->moveToThread(t1);
            quick->moveToThread(t2);
            bubble->moveToThread(t3);
 ```
#### 3.任务方法working()执行完毕后,发送finished()信号,同样的在主线程中进行ui数据显示

 ```c++     
           connect(quick,&Quick::finished,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {

                    ui->listWidget_Quick->addItem(QString::number(list.at(i)));
                }
            });

            connect(bubble,&BubbleSort::finished,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {

                    ui->listWidget_Bubble->addItem(QString::number(list.at(i)));
                }
            });
 ```

#### 4.回收资源
```c++ 
            connect(this,&MainWindow::destroyed,this,[=](){
                t1->quit();
                t1->wait();
                t1->deleteLater();
        
                t2->quit();
                t2->wait();
                t2->deleteLater();
        
                t3->quit();
                t3->wait();
                t3->deleteLater();
        
                randNum->deleteLater();
                bubble->deleteLater();
                quick->deleteLater();
            });
```

### QThreadpool:

 #### 1.将该三个类继承QObject和QRunnable,重写QRunnable类中的run()方法

```c++ 
            RandomNum::RandomNum(QObject *parent):QObject(parent),QRunnable(){ setAutoDelete(true); }
            BubbleSort::BubbleSort(QObject *parent):QObject(parent),QRunnable(){ setAutoDelete(true); }
            Quick::Quick(QObject *parent):QObject(parent),QRunnable(){ setAutoDelete(true); }
```
QRunnable下的setAutoDelete(bool autoDelete)方法,可以自动管理资源的释放,将函数中的布尔值参数设置成true即可

 #### 2.使用QThreadPool::globalInstance()->start(QRunnable *runnable, int priority = 0)方法来开启一个子线程
```c++ 
            connect(ui->btnStart,&QPushButton::clicked,this,[=](){
                emit starting(10000);
                QThreadPool::globalInstance()->start(randNum);
            });
```
 #### 3.同样的在RandomNumrun生成随机数完成后,开启另外两个子线程进行排序
 ```c++ 
             connect(randNum,&RandomNum::sendRandomArray,this,[=](QVector<int> list){
                 QThreadPool::globalInstance()->start(bubble);
                 QThreadPool::globalInstance()->start(quick);
                 for (int i = 0; i < list.size()-1; ++i) {
 
                    ui->listWidget_random->addItem(QString::number(list.at(i)));
                 }
                 emit sendArrList(list);

              });
```
 #### 4.在主线程中显示ui排序数据,由于QThreadpool设置了自动管理资源,最后不需要编写代码手动释放资源
 ```c++ 
            connect(quick,&Quick::finished,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {

                    ui->listWidget_Quick->addItem(QString::number(list.at(i)));
                }
            });

            connect(bubble,&BubbleSort::finished,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {
    
                    ui->listWidget_Bubble->addItem(QString::number(list.at(i)));
                }
            });
    
```

### 总结:  
        1.默认的线程在Qt中称之为窗口线程，也叫主线程，负责窗口事件处理或者窗口控件数据的更新
        
        2.子线程负责后台的业务逻辑处理，子线程中不能对窗口对象做任何操作，只有主线程才能操作程序中的窗口对象
        
        3.主线程和子线程之间如果要进行数据的传递，需要使用Qt中的信号槽机制
        
        4.如果要在一个子线程中处理多个任务，所有的处理逻辑都需要写到run()函数中，这样该函数中的处理逻辑就会变得非常混乱，不太容易维护
        
        5.使用创建任务对象的方式,将任务对象加入到子线程中执行,就可以避免上述情况,代码更容易维护
        
        6.使用线程池来减少子线程频繁的创建和销毁回收,可以提高系统执行效率













 
