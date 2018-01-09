#include "getimage.h"
#include<QDebug>
#include <QPixmap>
void GetImage::doWork(const QString &path)
{
    qDebug()<<"void GetImage::doWork(const QString &path)";
    QPixmap pix;
    VideoCapture videoCap;
    Mat srcImage;
    videoCap.open(path.toStdString().c_str());
    for(;;){
        if(videoCap.isOpened())
        {
            //emit msg("连接摄像机:"+path+"成功");
            srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
            videoCap>>srcImage;
            if(srcImage.data)
            {
                qDebug()<<"get image ...";
                cvtColor(srcImage, srcImage, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
                pix=QPixmap::fromImage(QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888));
                emit resultReady(pix);
            }
        }else
        {
            emit msg("连接摄像机:"+path+"失败，请检查登录信息是否正确");
        }
    }

}

void Controller::handleResults(const QPixmap &_image)
{
    qDebug()<<"void Controller::handleResults(const QImage &_image)";
    emit msg(QString("从摄像机上取图成功,原图大小:%1*%2").arg(_image.width()).arg(_image.height()));
    emit image(_image);

}
void Controller::getmsg(const QString &_msg)
{
    emit msg(_msg);
}
