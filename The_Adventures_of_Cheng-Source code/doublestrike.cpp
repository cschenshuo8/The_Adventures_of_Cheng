#include "doublestrike.h"

DoubleStrike::DoubleStrike(): DirCard(":/Res/doublestrike.png", 1)
{

}

void DoubleStrike::ChooseTarget(Hero * he , QVector<Monster *> monster_set)
{
    ReleaseAllTarget(he,monster_set);
    for (auto mon: monster_set)
    {
        //qDebug() << mon->x() << " "<< mon->y() <<" "<< mon->banned << endl;
        if (!mon->dead) //判断怪物是否死亡，死亡则无法成为目标
        {
            connect(mon,&QPushButton::clicked,[=](){
                //qDebug()<< 1<< endl;
                DisconnectAll(he, monster_set);
                BanAllTarget(he,monster_set);
                UseCard(he, mon);

            });
        }
    }
}

void DoubleStrike::Useit(Hero * he , QVector<Monster *> monster_set)
{
    //qDebug() << 5<<endl;
    ChooseTarget(he, monster_set); //先选择目标
}

//效果：造成4点伤害两次
void DoubleStrike::UseCard(Role * he, Role * tar)
{
    if (this->width() > 160)
    {
        this->FlashCard();
    }
    he->Attack(tar,4);
    he->Attack(tar,4);
    //qDebug() << 1<<endl;
    emit this->FinishCard();
}
