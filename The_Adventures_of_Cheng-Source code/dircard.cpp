#include "dircard.h"

DirCard::DirCard(QString ImgPath, int co): Card(ImgPath, co)
{

}

void DirCard::BanAllTarget(Hero * he, QVector<Monster *> monster_set)
{
    he->banned = 1;
    for (auto mon:monster_set)
        mon->banned = 1;
}

void DirCard::ReleaseAllTarget(Hero * he, QVector<Monster *> monster_set)
{
    he->banned = 0;
    for (auto mon:monster_set)
        mon->banned = 0;
}

void DirCard::DisconnectAll(Hero * he, QVector<Monster *> monster_set)
{
    disconnect(he,&QPushButton::clicked,0,0);
    for (auto mon: monster_set)
        disconnect(mon,&QPushButton::clicked,0,0);
}
