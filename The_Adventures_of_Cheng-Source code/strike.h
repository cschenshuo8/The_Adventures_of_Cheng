#ifndef STRIKE_H
#define STRIKE_H

#include "dircard.h"
class Strike: public DirCard //卡牌：打击
{
public:
    Strike();
    void ChooseTarget(Hero * ,QVector<Monster *>);
    void Useit(Hero * ,QVector<Monster *>);
    void UseCard(Role * he, Role * tar);
};

#endif // STRIKE_H
