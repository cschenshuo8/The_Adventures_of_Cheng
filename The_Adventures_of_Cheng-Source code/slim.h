#ifndef SLIM_H
#define SLIM_H
#include "monster.h"

class Slim: public Monster //怪物：史莱姆
{
public:
    Slim(int mh, int nh, int sh,int att);
    QString getRoleImg();
    void MonsterAttack(Hero *,int round);
};

#endif // SLIM_H
