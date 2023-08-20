#ifndef PUSHBOTTON_PRESS_H
#define PUSHBOTTON_PRESS_H
#include <QPushButton>
#include <QWidget>

class PushButton_press : public QPushButton
{
    Q_OBJECT
public:
    //explicit PushBotton_press(QWidget *parent = nullptr);

    PushButton_press(QString normalImg,QString pressImg = "",double size = 1); //size：图片比例大小，默认为1。

    QString normalImgPath;
    QString pressImgPath;

    bool banned = 0; //按钮是否可用

    //图标弹跳动画
    void Zoom_down(); //图标向下
    void Zoom_up(); //图标向上

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // PUSHBOTTON_PRESS_H
