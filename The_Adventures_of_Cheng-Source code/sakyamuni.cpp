#include "sakyamuni.h"

Sakyamuni::Sakyamuni(int mh,int nh,int sh,int a): Monster(mh, nh, sh, ":/Res/sakyamuni.png", a)
{
    this->setFixedSize(QSize(300,300));
    this->setIconSize(QSize(300,300));
}

QString Sakyamuni::getRoleImg()
{
    return ":/Res/sakyamuni.png";
}

//每回合造成的伤害+3，会一直累加。
void Sakyamuni::MonsterAttack(Hero * he,int round)
{
    this->Attack(he,att);
    this->strange += 3;
}
