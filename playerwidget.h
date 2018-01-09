#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QRect>
#include <QVector>
#include <QPen>
#include <QHBoxLayout>
#include <QPainter>
///
/// \brief The mylabel class
/// 底层绘图类
class Basiclabel : public QLabel
{
    Q_OBJECT
public:
    explicit Basiclabel(QWidget *parent=nullptr); //构造函数
    void paintEvent(QPaintEvent *);  //重绘事件
    void addvec(const QRect &rect);  //绘制矩形框
    void setFrame(const QPixmap &);  //绘制图片
    bool isRectEmpty();  //判断是否含有矩形框
    void clearRect();  //清空缓存

signals:
public slots:
private:
    QVector<QRect> rectvec;     //矩形框
    QPixmap pix;
    QPen pen;
    QPainter p;
    bool pixchanged;
};

///
/// \brief The ShowWidget class
///接受信号处理类
class ShowWidget:public QWidget
{
    Q_OBJECT
public:
    ShowWidget(QWidget *parent);
public slots:
    void updateImage(const QPixmap &pix);
    void updaterect (const QVector<QRect> &rectvec);
private:
    Basiclabel label[2];
};



///
/// \brief The PlayerWidget class
/// 窗口显示类
class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent=nullptr);
    ~PlayerWidget();
signals:

public slots:
    void updateFrame(const QPixmap& pix);
    void updateAlarm(const QVector<QRect> &rectvec);
private:
    ShowWidget *showwidget;
    QBoxLayout *layout;
};

#endif // PLAYERWIDGET_H
