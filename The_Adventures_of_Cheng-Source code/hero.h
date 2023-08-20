#ifndef HERO_H
#define HERO_H

#include "role.h"

class Hero: public Role //英雄
{
public:
    int hero_ID = 0; //英雄ID
    Hero(int mh, int nh, int sh, QString Img, int id);
    virtual QString getRoleImg(){ return ""; } //获取图片路径

};

#endif // HERO_H
