#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QVector>
#include "role.h"
#include "monster.h"
#include "hero.h"

class Card : public QPushButton //卡牌类，继承于类QPushButton
{
    Q_OBJECT
public:
    Card(QString ImgPath, int co);
    QString Img; //卡牌图片路径
    int cost; //卡牌能量消耗
    bool banned = 0; //卡牌能否使用
    bool ischoosecard = 0; //卡牌是在选择卡牌界面，还是在手牌中（两者的图片大小不同）

    //void Move();
    virtual void Useit(Hero *, QVector<Monster *>){} //使用卡牌(英雄，所有怪物）
    void leaveEvent(QEvent *); //鼠标进入后，卡牌自动放大
    void enterEvent(QEvent *); //鼠标离开后，卡牌自动还原
    void mousePressEvent(QMouseEvent *); //鼠标点击后，判断卡牌是否可用
    void FlashCard(); //重置卡牌至原始大小
signals:
    void FinishCard();
};

#endif // CARD_H
