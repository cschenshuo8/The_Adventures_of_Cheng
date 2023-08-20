#include <QDebug>
#include "strike.h"
#include "role.h"

Strike::Strike(): DirCard(":/Res/strike.png", 1)
{
}

void Strike::ChooseTarget(Hero * he , QVector<Monster *> monster_set)
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

void Strike::Useit(Hero * he , QVector<Monster *> monster_set)
{
    //qDebug() << 5<<endl;

    ChooseTarget(he, monster_set);
}

//效果：造成5点伤害
void Strike::UseCard(Role * he, Role * tar)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->Attack(tar,6);
    //qDebug() << 1<<endl;
    emit this->FinishCard();
}
