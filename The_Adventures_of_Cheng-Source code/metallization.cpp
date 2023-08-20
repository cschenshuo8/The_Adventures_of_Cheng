#include "metallization.h"

Metallization::Metallization(): UndirCard(":/Res/metallization.png", 1)
{

}

//效果：回合结束时，获得1点护盾
void Metallization::Useit(Hero * he, QVector<Monster *> monster_set)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->shieldeveryround = 1;
    emit this->FinishCard();
}
