#include "slim.h"
#include "monster.h"

Slim::Slim(int mh,int nh,int sh,int a): Monster(mh, nh, sh, ":/Res/slim.png", a)
{

}

QString Slim::getRoleImg()
{
    return ":/Res/slim.png";
}

//每3回合进行一次重击。
void Slim::MonsterAttack(Hero * he,int round)
{
    if (round % 3 != 0)
        this->Attack(he,att);
    else
        this->Attack(he,(int)att * 1.5);
}
