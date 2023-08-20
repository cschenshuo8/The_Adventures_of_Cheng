#include "card.h"

Card::Card(QString ImgPath, int co)
{   
    this->Img = ImgPath;
    cost = co;
    QPixmap pix;
    pix.load(this->Img);

    //设置图片固定大小
    this->setFixedSize(160,200);

    //设置样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(160,200));
}

void Card::enterEvent(QEvent * e)
{
    if (this->banned || this->ischoosecard || this->y() < 800) return QWidget::enterEvent(e);
    QPixmap pix;
    pix.load(this->Img);

    //设置图片固定大小
    this->move(this->x() - 80,this->y() - 200);

    this->setFixedSize(320,400);

    //设置样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(320,400));
    return QWidget::enterEvent(e);
}

void Card::leaveEvent(QEvent * e)
{
    if (this->banned || this->ischoosecard || this->y() > 800) return QWidget::enterEvent(e);
    QPixmap pix;
    pix.load(this->Img);

    //设置图片固定大小
    this->move(this->x() + 80,this->y() + 200);
    this->setFixedSize(160,200);

    //设置样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(160,200));
    return QWidget::leaveEvent(e);
}

void Card::mousePressEvent(QMouseEvent *e)
{
    if (this->banned)
    {
        return;
    } else
    {
        return QPushButton::mousePressEvent(e);
    }

}

void Card::FlashCard()
{
    QPixmap pix;
    pix.load(this->Img);

    //设置图片固定大小
    this->move(this->x() + 80,this->y() + 200);
    this->setFixedSize(160,200);

    //设置样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图片大小
    this->setIconSize(QSize(160,200));
}
