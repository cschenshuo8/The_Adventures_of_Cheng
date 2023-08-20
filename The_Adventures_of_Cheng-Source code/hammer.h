#ifndef HAMMER_H
#define HAMMER_H

#include "dircard.h"

class Hammer: public DirCard //卡牌：重锤
{
public:
    Hammer();
    void ChooseTarget(Hero * ,QVector<Monster *>);
    void Useit(Hero * ,QVector<Monster *>);
    void UseCard(Role * he, Role * tar);
};

#endif // HAMMER_H
