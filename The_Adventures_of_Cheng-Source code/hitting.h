#ifndef HITTING_H
#define HITTING_H

#include "dircard.h"

class Hitting: public DirCard //卡牌：全身撞击
{
public:
    Hitting();
    void ChooseTarget(Hero * ,QVector<Monster *>);
    void Useit(Hero * ,QVector<Monster *>);
    void UseCard(Role * he, Role * tar);
};

#endif // HITTING_H
