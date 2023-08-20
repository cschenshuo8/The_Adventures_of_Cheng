#ifndef DOUBLESTRIKE_H
#define DOUBLESTRIKE_H

#include "dircard.h"

class DoubleStrike : public DirCard //卡牌：双重打击
{
public:
    DoubleStrike();
    void ChooseTarget(Hero * ,QVector<Monster *>); //选择目标
    void Useit(Hero * ,QVector<Monster *>); //使用卡牌
    void UseCard(Role * he, Role * tar); //选择目标后卡牌生效
};

#endif // DOUBLESTRIKE_H
