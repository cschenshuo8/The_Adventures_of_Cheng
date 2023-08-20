#ifndef DEFENSE_H
#define DEFENSE_H

#include "undircard.h"

class Defense: public UndirCard //卡牌：防御
{
public:
    Defense();
    void Useit(Hero * , QVector<Monster *>);
};

#endif // DEFENSE_H
