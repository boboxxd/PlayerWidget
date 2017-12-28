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
/// basic show layer
class Basiclabel : public QLabel
{
    Q_OBJECT
public:
    explicit Basiclabel(QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *);
    void addvec(const QRect &rect);
    void setFrame(const QPixmap &);
    bool isRectEmpty();
    void clearRect();

    void resizeEvent(QResizeEvent *);
    //void setStyle();
signals:
public slots:
private:
    QVector<QRect> rectvec;     //alarm rect
    QPixmap pix;
    QPen pen;
    QPainter p;
    bool pixchanged;
};

///
/// \brief The ShowWidget class
///
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
/// main show image layer
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