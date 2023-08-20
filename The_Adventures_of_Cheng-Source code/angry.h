#ifndef ANGRY_H
#define ANGRY_H

#include "undircard.h"

class Angry: public UndirCard//卡牌：盛怒
{
public:
    Angry();
    void Useit(Hero * , QVector<Monster *>);//使用卡牌
};

#endif // ANGRY_H
