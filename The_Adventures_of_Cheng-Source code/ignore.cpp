#include "ignore.h"

Ignore::Ignore(): UndirCard(":/Res/ignore.png", 1)
{

}

//效果：获得4点护盾，抽一张牌
void Ignore::Useit(Hero * he, QVector<Monster *> monster_set)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->gainShield(4);
    he->drawcard += 1;
    emit this->FinishCard();
}
