#ifndef FIGHTSCENE_H
#define FIGHTSCENE_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include "pushbutton_press.h"
#include "hero.h"
#include "card.h"
#include "monster.h"

class FightScene : public QMainWindow //战斗场景
{
    Q_OBJECT
public:
    FightScene(Hero *, QVector<Monster*> ,QVector<Card*>);

    void IsEnded(); //判断战斗是否结束
    void StartFighting(); //开始战斗
    void StartYourTurn(); //开始你的回合
    void StartEnemyTurn(); //开始对手回合


    void paintEvent(QPaintEvent *); //绘制背景图和护盾标志

    void InitCard(); //初始化卡牌
    void NewCard(Card* ca, int x0,int y0); //将卡牌添加到战斗场景中
    void UpdateCard(); //更新卡牌位置，其中包括卡牌动画的制作
    void DrawCard(int nu); //抽nu张牌到手牌中
    void DiscardCard(Card * ca); //将指定卡牌放入弃牌堆中

    void UpdateEnergy(); //更新能量标签

    void UpdateHP(); //更新血量标签，护盾标签

    void ReleaseAllCard(); //解锁所有卡牌
    void BanAllCard(); //禁用所有卡牌
    void ReleaseAllTarget(); //解锁所有目标
    void BanAllTarget(); //禁用所有目标

    void BeforeTurn(Role * tar); //对指定角色在回合开始时的默认操作
    void AfterTurn(Role * tar); //对指定角色在回合结束时的默认操作
    void AfterCard(); //使用卡牌后的默认操作

    //两个计时器，主要用于卡牌动画制作
    QTimer * timer1;
    QTimer * timer2;

    int energy; //能量
    QLabel * energyLabel = NULL; //能量标签
    QLabel * roundLabel = NULL; //回合标签
    int tmp0;
    int round; //回合数

    PushButton_press * end_btn = NULL; //回合结束按钮
    bool end_btn_able; //回合结束按钮是否可用

    QVector<Monster *> monster_set; //怪物集合
    QVector<QLabel *> monster_setLabel; //怪物血量标签
    QVector<QLabel *> monster_setShield; //怪物护盾标签
    QVector<QProgressBar* > monster_setbl; //怪物血条

    QVector<Card *> card_set; //所有卡牌

    QVector<Card *> hand_card; //手牌
    QVector<Card *> undrawn_card; //抽牌堆中的牌
    QVector<Card *> discard; //弃牌堆中的牌

    Hero * he = NULL; //英雄
    QLabel * heLabel; //英雄血量标签
    QLabel * heShield; //英雄护盾标签
    QProgressBar * hebl; //英雄血条

    bool isGameOver = false;  //游戏是否结束

signals:
    void WinTheGame(); //游戏胜利信号
    void LoseTheGame(); //游戏失败信号
};

#endif // FIGHTSCENE_H
