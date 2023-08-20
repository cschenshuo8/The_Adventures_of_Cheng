#ifndef SABERDRAGON_H
#define SABERDRAGON_H

#include<monster.h>

class SaberDragon: public Monster //怪物：刀龙
{
public:
    SaberDragon(int mh, int nh, int sh,int att);
    QString getRoleImg();
    void MonsterAttack(Hero *,int round);
};

#endif // SABERDRAGON_H
