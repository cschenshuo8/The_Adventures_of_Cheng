#ifndef BARRIER_H
#define BARRIER_H

#include "undircard.h"

class Barrier : public UndirCard //卡牌：壁垒
{
public:
    Barrier();
    void Useit(Hero * , QVector<Monster *>);//使用卡牌
};

#endif // BARRIER_H
