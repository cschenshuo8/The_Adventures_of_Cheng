#include "warrior.h"
#include "hero.h"

Warrior::Warrior(int mh, int nh, int sh): Hero(mh, nh, sh, ":/Res/warrior_stand.png", 1)
{
    //调整图片大小
    this->setFixedSize(QSize(400,300));
    this->setIconSize(QSize(400,300));
}
