#include "saberdragon.h"

SaberDragon::SaberDragon(int mh,int nh,int sh,int a): Monster(mh, nh, sh, ":/Res/saberdragon.png", a)
{
    this->setFixedSize(QSize(250,300));
    this->setIconSize(QSize(250,300));
}

QString SaberDragon::getRoleImg()
{
    return ":/Res/saberdragon.png";
}

//每5回合给英雄一个3回合的虚弱debuff，其他回合正常攻击。
void SaberDragon::MonsterAttack(Hero * he,int round)
{
    if (round % 5 == 1)
    {
        he->weak += 3;
    }
    else
    {
        this->Attack(he,att);
    }
}
