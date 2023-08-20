#include "role.h"
#include <iostream>
#include <QDebug>
using namespace std;
Role::Role(int mh,int nh,int sh,QString Img):max_hp(mh), now_hp(nh), shield(sh), dead(0)
{
    QPixmap pix;
    pix.load(Img);
    banned = 1;
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    strange = 0;
    strange00 = 0;
    weak = 0;
    injured = 0;
    drawcard = 0;
    addenergy = 0;
    shieldforever = 0;
    shieldeveryround = 0;
}

void Role::hell(int tmp)
{
    if (!this->dead)
        now_hp = min(max_hp, now_hp + tmp);
}

void Role::gainShield(int tmp)
{
    shield += tmp;
}

void Role::gainMax_hp(int tmp)
{
    max_hp += tmp;
}

void Role::beAttack(int tmp)
{
    shield -= tmp;
    if (shield < 0)
    {
        now_hp += shield;
        shield = 0;
    }
    if (now_hp < 0) now_hp = 0;
    if (now_hp == 0) this->dead = 1;
}

void Role::Attack(Role *tar, int tmp)
{
    //qDebug() << this->weak;
    tmp += this->strange + this->strange00;
    if (this->weak > 0)
        tmp = (int)(tmp * 0.75);
    if (tar->injured > 0)
        tmp = (int)(tmp * 1.25);
    if (tmp < 0) tmp = 0;
    tar->beAttack(tmp);
}

void Role::mousePressEvent(QMouseEvent *e)
{
    //qDebug()<< << endl;
    if (banned) return;
    return QPushButton::mousePressEvent(e);
}
