#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#include <QImage>


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
    con=new Controller;
    con->operate("rtsp://admin:ad53937301@49.91.240.77:554/h264/ch1/main/av_stream");
    connect(con,&Controller::image,player,&PlayerWidget::updateFrame);
    connect(this,&Widget::Alarm,player,&PlayerWidget::updateAlarm);
}



 void Widget::timerEvent(QTimerEvent *event)
 {
     qDebug()<<"Widget::timeoutslot()";
     //emit image(QPixmap("/Users/xuxudong/Mycode/PlayerWidget/test.jpg"));
     n+=5;
     QVector<QRect> rectvec={QRect(n,n,100,100),QRect(n+5,n+10,100,100),QRect(210,210,100,100)};
     emit Alarm(rectvec);
 }

Widget::~Widget()
{
    delete ui;
}
