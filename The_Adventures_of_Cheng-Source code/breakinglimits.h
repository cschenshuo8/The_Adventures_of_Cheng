#ifndef BREAKINGLIMITS_H
#define BREAKINGLIMITS_H

#include "undircard.h"

class BreakingLimits: public UndirCard //卡牌：突破极限
{
public:
    BreakingLimits();
    void Useit(Hero * , QVector<Monster *>);
};

#endif // BREAKINGLIMITS_H
