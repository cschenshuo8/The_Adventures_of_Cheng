#include "hammer.h"

Hammer::Hammer(): DirCard(":/Res/hammer.png", 3)
{

}

void Hammer::ChooseTarget(Hero * he , QVector<Monster *> monster_set)
{
    ReleaseAllTarget(he,monster_set);
    for (auto mon: monster_set)
    {
        //qDebug() << mon->x() << " "<< mon->y() <<" "<< mon->banned << endl;
        if (!mon->dead)
        {
            connect(mon,&QPushButton::clicked,[=](){
                //qDebug()<< 1<< endl;
                DisconnectAll(he, monster_set);
                BanAllTarget(he,monster_set);

                UseCard(he,mon);
            });
        }
    }
}

void Hammer::Useit(Hero * he , QVector<Monster *> monster_set)
{
    //qDebug() << 5<<endl;

    ChooseTarget(he, monster_set);
}

//效果：造成25点伤害
void Hammer::UseCard(Role * he, Role * tar)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->Attack(tar,25);
    //qDebug() << 1<<endl;
    emit this->FinishCard();
}
