#ifndef DEVILDRAGON_H
#define DEVILDRAGON_H

#include "monster.h"

class DevilDragon: public Monster //怪物：恶龙
{
public:
    DevilDragon(int mh, int nh, int sh,int att);
    QString getRoleImg(); //获取图片路径
    void MonsterAttack(Hero *,int round); //攻击
};

#endif // DEVILDRAGON_H
