#ifndef WARRIOR_H
#define WARRIOR_H
#include "hero.h"

class Warrior : public Hero //英雄：战士
{
public:
    Warrior(int mh, int nh, int sh);
    QString getRoleImg(){
        return ":/Res/warrior_stand.png";
    }

};

#endif // WARRIOR_H
