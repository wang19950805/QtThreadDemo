# Qt多线程的使用:    
    
     在案例中使用RandomNum类来生成十万个随机数,并使用BubbleSort类和Quick类对十万个随机数进行冒泡排序和快速排序

  Demo1:  
  
      1.将该三个类都继承QThread类,并重写run()方法,点击开始按钮生成随机数
    
            class RandomNum : public QThread{}
            class BubbleSort : public QThread{}
            class Quick : public QThread{}
               
            connect(this,&MainWindow::starting,randNum,&RandomNum::revNum);
            connect(ui->btnStart,&QPushButton::clicked,this,[=](){
                //发送信号,生成十万个随机数
                emit starting(10000);
                randNum->start();
            });
              
      2.RandomNum在run()方法中生成随机数完成后,发送sendRandomArray()的信号,在mainwindow中连接的信号槽函数将剩余两个子线程启动
      
            connect(randNum,&RandomNum::sendRandomArray,this,[=](QVector<int> list){
                for (int i = 0; i < list.size()-1; ++i) {
                    bubble->start();
                    quick->start();
                    ui->listWidget_random->addItem(QString::number(list.at(i)));
                }
                //发送排序信号,将生成的随机数list传递
                emit sendArrList(list);      
            });

      3.BubbleSort::run()和Quick::run()执行完毕后,发送finished()信号,在主线程中进行ui数据显示
      
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

      4.回收资源
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



















