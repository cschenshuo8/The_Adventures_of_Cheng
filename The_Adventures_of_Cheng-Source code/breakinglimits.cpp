#include "breakinglimits.h"

BreakingLimits::BreakingLimits(): UndirCard(":/Res/breakinglimits.png", 1)
{

}

//效果：将你的力量翻倍
void BreakingLimits::Useit(Hero * he, QVector<Monster *> monster_set)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->strange = (he->strange + he->strange00) * 2 - he->strange00;
    emit this->FinishCard();
}
