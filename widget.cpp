#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(1080,720);
    layout=new QHBoxLayout(this);
    player=new PlayerWidget(this);
    layout->addWidget(player);
    this->setLayout(layout);
    timerId=startTimer(1000);

    connect(this,&Widget::image,player,&PlayerWidget::updateFrame);
    connect(this,&Widget::Alarm,player,&PlayerWidget::updateAlarm);
//  emit image(QPixmap("/home/hhit/code/build-HHPlayer_v2-Desktop_Qt_5_9_2_GCC_64bit-Debug/output/alarm_1376.jpg"));
//  QVector<QRect> rectvec={QRect(0,0,100,100),QRect(105,105,100,100),QRect(210,210,100,100)};
//  emit Alarm(rectvec);

}



 void Widget::timerEvent(QTimerEvent *event)
 {
     qDebug()<<"Widget::timeoutslot()";
     emit image(QPixmap("/home/hhit/code/build-HHPlayer_v2-Desktop_Qt_5_9_2_GCC_64bit-Debug/output/alarm_1376.jpg"));
     n+=5;
     QVector<QRect> rectvec={QRect(n,n,100,100),QRect(n+5,n,100,100),QRect(210,210,100,100)};
     emit Alarm(rectvec);
 }

Widget::~Widget()
{
    delete ui;
}
