#ifndef MONSTER_H
#define MONSTER_H
#include "role.h"
#include "hero.h"
class Monster: public Role //怪物
{
public:
    Monster(int mx,int mh,int sh,QString Img,int att);
    int att; //怪物攻击力
    virtual QString getRoleImg(){ return ""; }
    virtual void MonsterAttack(Hero * ,int ){} //怪物攻击
};

#endif // MONSTER_H
