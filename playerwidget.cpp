#include "playerwidget.h"
#include <QPainter>
#include <QDebug>

///
/// \brief Basiclabel::Basiclabel
/// \param parent
///
Basiclabel::Basiclabel(QWidget *parent) : QLabel(parent)
{
    pixchanged=false;
    if(parent != nullptr)
    {
        this->setGeometry(0,0,parent->width(),parent->height());
        this->show();
    }
}

///
/// \brief Basiclabel::paintEvent
/// \param e
///
void Basiclabel::paintEvent(QPaintEvent *e)
{
    qDebug()<<"Basiclabel::paintEvent(QPaintEvent *e)";
    QLabel::paintEvent(e);
    if(!pix.isNull())
    {
        p.begin(this);
        p.drawPixmap(0,0,this->pix.width(),this->pix.height(),this->pix);
        p.end();
    }

    if(!isRectEmpty())
    {
        qDebug()<<"in event";
        p.begin(this);
        p.setPen(QPen(Qt::red, 3,Qt::SolidLine, Qt::RoundCap));
        for(int i=0;i<rectvec.count();i++)
            p.drawRect(rectvec[i]);
        p.end();
    }
}

///
/// \brief resizeEvent
///
void Basiclabel::resizeEvent(QResizeEvent *)
{
    qDebug()<<"Basiclabel::resizeEvent(QResizeEvent *)"<<this->width()<<":"<<this->height();
}

///
/// \brief Basiclabel::addvec
/// \param rect
///
void Basiclabel::addvec( const QRect &rect)
{
    qDebug()<<"Basiclabel::addvec( QRect rect)";
    rectvec.push_back(rect);
    qDebug()<<rectvec[0]<<this->width();
    this->update();
}

///
/// \brief Basiclabel::setFrame
///
void Basiclabel::setFrame(const QPixmap &pix)
{
    this->pix=pix;
    this->update();
}


///
/// \brief Basiclabel::isRectEmpty
/// \return
///
bool Basiclabel::isRectEmpty()
{
    qDebug()<<"Basiclabel::isRectEmpty()";
    if(rectvec.isEmpty())
        return true;
    return false;
}

///
/// \brief Basiclabel::clearRect
///
void Basiclabel::clearRect()
{
    qDebug()<<"Basiclabel::clearRect()";
    rectvec.clear();
}

//------------------------------------------------------------------------------------------------------

///
/// \brief ShowWidget::ShowWidget
/// \param parent
///
ShowWidget::ShowWidget(QWidget *parent):QWidget(parent)
{
    qDebug()<<"ShowWidget::ShowWidget(QWidget *parent)";
    if(parent != nullptr)
    {
        label[0].setParent(parent);
        label[1].setParent(qobject_cast<QWidget*>(&label[0]));
        for(int i=0;i<2;i++)
        {
            label[i].resize(parent->width(),parent->height());
        }
    }
}

///
/// \brief ShowWidget::updateImage
/// \param pix
///
void ShowWidget::updateImage(const QPixmap &pix)
{
    qDebug()<<"ShowWidget::updateImage(QPixmap pix)";
    label[0].setFrame(pix);
}

///
/// \brief ShowWidget::updaterect
/// \param rect
///
void ShowWidget::updaterect (const QVector<QRect> &rectvec)
{
    qDebug()<<"ShowWidget::updaterect(QRect rect)";
    label[1].clearRect();
    for(int i=0;i<rectvec.count();i++)
        label[1].addvec(rectvec[i]);
}


//------------------------------------------------------------------------------------------------------

///
/// \brief PlayerWidget::PlayerWidget
/// \param parent
///
PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"PlayerWidget::PlayerWidget(QWidget *parent)";
    if(parent != nullptr)
    {
        this->resize(parent->width(),parent->height());
        showwidget=new ShowWidget(this);
        layout=new QHBoxLayout(this);
        layout->addWidget(showwidget);
        parent->setLayout(layout);
        qDebug()<<"end";
    }
}

///
/// \brief PlayerWidget::updateFrame
/// \param pix
///
void PlayerWidget::updateFrame(const QPixmap& pix)
{
    showwidget->updateImage(pix);
}

///
/// \brief PlayerWidget::updateAlarm
/// \param rectvec
///
void PlayerWidget::updateAlarm(const QVector<QRect> &rectvec)
{
        showwidget->updaterect(rectvec);
}

///
/// \brief PlayerWidget::~PlayerWidget
///
PlayerWidget::~PlayerWidget()
{
    delete layout;
    delete showwidget;
}
