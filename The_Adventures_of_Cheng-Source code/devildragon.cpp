#include "devildragon.h"

DevilDragon::DevilDragon(int mh,int nh,int sh,int a): Monster(mh, nh, sh, ":/Res/devildragon.png", a) //最大生命值、 当前生命值、 护盾、 图片路径、 攻击力
{
    //重新设置卡牌大小
    this->setFixedSize(QSize(200,300));
    this->setIconSize(QSize(200,300));
}

QString DevilDragon::getRoleImg()
{
    return ":/Res/devildragon.png";
}

void DevilDragon::MonsterAttack(Hero * he,int round) //每回合造成一定的伤害
{
    this->Attack(he,att);
}
