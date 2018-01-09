#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "playerwidget.h"
#include <QTimer>
#include <QTime>
#include "getimage.h"

using namespace cv;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void timerEvent(QTimerEvent *event);
signals:
    void image(const QPixmap &);
    void Alarm(const QVector<QRect> &);
    void seturl(const QString&);

private:
    Ui::Widget *ui;
    PlayerWidget *player;
    QHBoxLayout *layout;
    int timerId;

    int n=-5;

    Controller *con;

};

#endif // WIDGET_H
