#include "assassin.h"
#include "hero.h"

Assassin::Assassin(int mh, int nh, int sh): Hero(mh, nh, sh, ":/Res/assassin_stand.png", 2)//最大生命值、 当前生命值、 护盾、 图片路径、 英雄ID
{
    //调整图片大小
    this->setFixedSize(QSize(400,300));
    this->setIconSize(QSize(400,300));
}
