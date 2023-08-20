#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "hero.h"

class Assassin : public Hero//英雄：刺客
{
public:
    Assassin(int mh, int nh, int sh); 
    QString getRoleImg(){
        return ":/Res/warrior_stand.png";
    }

};
#endif // ASSASSIN_H
