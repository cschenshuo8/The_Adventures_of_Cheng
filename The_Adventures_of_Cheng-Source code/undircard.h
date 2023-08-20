#ifndef UNDIRCARD_H
#define UNDIRCARD_H

#include "card.h"

class UndirCard: public Card //非指向性卡牌
{
public:
    UndirCard(QString ImgPath, int co);
    virtual void Useit(Hero *, QVector<Monster *>){}
};

#endif // UNDIRCARD_H
