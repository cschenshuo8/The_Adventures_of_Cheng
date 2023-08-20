#ifndef IGNORE_H
#define IGNORE_H

#include "undircard.h"

class Ignore: public UndirCard //卡牌：耸肩无视
{
public:
    Ignore();
    void Useit(Hero * , QVector<Monster *>);
};

#endif // IGNORE_H
