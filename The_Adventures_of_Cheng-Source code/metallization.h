#ifndef METALLIZATION_H
#define METALLIZATION_H

#include "undircard.h"

class Metallization: public UndirCard //卡牌：金属化
{
public:
    Metallization();
    void Useit(Hero * , QVector<Monster *>);
};

#endif // METALLIZATION_H
