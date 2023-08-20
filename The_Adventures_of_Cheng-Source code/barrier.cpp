#include "barrier.h"

Barrier::Barrier(): UndirCard(":/Res/barrier.png",3)
{

}

//效果：回合开始时，护盾不会消失
void Barrier::Useit(Hero * he, QVector<Monster *> monster_set)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->shieldforever = 1;
    emit this->FinishCard();
}
