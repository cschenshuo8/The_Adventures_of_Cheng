#ifndef DIRCARD_H
#define DIRCARD_H

#include "card.h"

class DirCard: public Card //指向性卡牌
{
public:
    DirCard(QString ImgPath, int co);
    virtual void ChooseTarget(Hero * ,QVector<Monster *>){} //选择目标
    virtual void Useit(Hero * ,QVector<Monster *>){} //使用卡牌
    //virtual void UseCard(Role *){}
    void DisconnectAll(Hero * , QVector<Monster *>); //断开目标连接，使所有目标无法被选择
    void BanAllTarget(Hero * ,QVector<Monster *>); //禁用所有目标
    void ReleaseAllTarget(Hero * ,QVector<Monster *>); //解放所有目标
};

#endif // DIRCARD_H
