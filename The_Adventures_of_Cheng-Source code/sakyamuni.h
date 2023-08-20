#ifndef SAKYAMUNI_H
#define SAKYAMUNI_H

#include "monster.h"

class Sakyamuni: public Monster //怪物：圣主
{
public:
    Sakyamuni(int mh, int nh, int sh,int att);
    QString getRoleImg();
    void MonsterAttack(Hero *,int round);
};

#endif // SAKYAMUNI_H
