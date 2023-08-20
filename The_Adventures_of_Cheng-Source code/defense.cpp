#include <QDebug>
#include "defense.h"

Defense::Defense(): UndirCard(":/Res/defense.png",1)
{

}

//效果：获得5点护盾
void Defense::Useit(Hero * he, QVector<Monster *> monster_set)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->gainShield(5);
    emit this->FinishCard();
}
