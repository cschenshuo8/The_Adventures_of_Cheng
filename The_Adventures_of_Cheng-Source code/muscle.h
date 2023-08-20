#ifndef MUSCLE_H
#define MUSCLE_H

#include "undircard.h"

class Muscle : public UndirCard //卡牌：活动肌肉
{
public:
    Muscle();
    void Useit(Hero * , QVector<Monster *>);
};

#endif // MUSCLE_H
