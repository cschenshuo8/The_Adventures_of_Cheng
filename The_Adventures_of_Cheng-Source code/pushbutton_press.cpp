#include "pushbutton_press.h"
#include <QDebug>
#include <QPropertyAnimation>

PushButton_press::PushButton_press(QString normalImg, QString pressImg,double size)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    //加载图片
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret)
    {
        qDebug() << "图片加载失败" << endl;
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width()*size,pix.height()*size);

    //设置样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(pix.width()*size,pix.height()*size));

}

void PushButton_press::Zoom_up()
{
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //时间间隔
    animation1->setDuration(200);
    //起始位置
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void PushButton_press::Zoom_down()
{
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //时间间隔
    animation1->setDuration(200);
    //起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void PushButton_press::mousePressEvent(QMouseEvent *e)
{
    if (banned) return;
    if (this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if (!ret)
        {
            qDebug() << "图片加载失败" << endl;
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }

    return QPushButton::mousePressEvent(e);
}

void PushButton_press::mouseReleaseEvent(QMouseEvent *e)
{
    if (banned) return;
    if (this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if (!ret)
        {
            qDebug() << "图片加载失败" << endl;
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图片大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }

    return QPushButton::mouseReleaseEvent(e);
}
