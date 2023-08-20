#ifndef ROLE_H
#define ROLE_H
#include <QString>
#include <QPushButton>

class Role : public QPushButton
{
    Q_OBJECT
public:
    Role(int mh, int nh, int sh, QString Img);
    int max_hp; //最大生命
    int now_hp; //目前生命
    int shield; //护盾
    int dead; //是否死亡

    int strange; //力量：每次攻击造成的伤害+当前力量点数。
    int strange00; //临时力量：效果与力量相同，但是会在回合结束时消失。
    int weak; //虚弱：虚弱状态下，攻击伤害减少25%。
    int injured; //易伤：攻击易伤的角色，攻击伤害增加25%。
    int drawcard; //抽卡：使用卡牌后抽一定数量的卡牌。
    int addenergy; //增加能量：使用卡牌后增加一定数量的能量。
    int shieldforever; //永久护盾：拥有此状态，回合开始时护盾不会消失
    int shieldeveryround; //每回合的可获得的护盾

    int banned; //按钮是否可用

    void hell(int tmp); //治疗
    void gainShield(int tmp); //获得护盾
    void gainMax_hp(int tmp); //获得最大生命值
    void Attack(Role * tar, int tmp); //攻击
    void beAttack(int tmp); //受到攻击
    void mousePressEvent(QMouseEvent *e);

    virtual QString getRoleImg(){ return ""; }
signals:

};

#endif // ROLE_H
