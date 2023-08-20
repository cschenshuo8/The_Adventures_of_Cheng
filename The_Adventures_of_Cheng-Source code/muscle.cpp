#include "muscle.h"

Muscle::Muscle(): UndirCard(":/Res/muscle.png", 0)
{

}

//效果：获得2点力量，回合结束时失去两点力量
void Muscle::Useit(Hero * he, QVector<Monster *> monster_set)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->strange00 += 2;
    emit this->FinishCard();
}
