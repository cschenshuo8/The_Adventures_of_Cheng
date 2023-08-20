#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "fightscene.h"
#include "choosecardscene.h"
#include "monster.h"
#include "card.h"
#include <QVector>
using namespace std;

namespace Ui {
class ChooseLevelScene;
}

class ChooseLevelScene : public QMainWindow //选择关卡场景
{
    Q_OBJECT

public:
    explicit ChooseLevelScene(QMainWindow *parent = nullptr);
    ~ChooseLevelScene();

    Hero * he =NULL; //英雄

    FightScene * f_scene = NULL; //战斗场景

    ChooseCardScene * c_scene = NULL; //选择卡牌场景

    QVector<QVector<Monster *> > monster_set; //怪物集合

    QVector<Card *> card_set; //手牌集合

    //战斗关卡按钮
    PushButton_press * l1_Btn = NULL;
    PushButton_press * l2_Btn = NULL;
    PushButton_press * l3_Btn = NULL;
    PushButton_press * l4_Btn = NULL;
    PushButton_press * l5_Btn = NULL;
    //营地按钮
    PushButton_press * r1_Btn = NULL;
    PushButton_press * r2_Btn = NULL;
    //随机关卡按钮
    PushButton_press * u1_Btn = NULL;
    QLabel * levelLabel = NULL; //关卡标签
    QLabel * nowLevelLabel = NULL; //当前所在关卡标签

    int tmpMessage = 0; //获取提示框信息

    void BeforeFighting(); //战斗前设置
    void AfterFighting(); //战斗后设置

    void ChooseCard(); //获得一张卡牌

    //把怪物加入怪物集合
    void InitMonster();
    void PushSlim(QVector<Monster*>& ,int ,int ,int ,int ); //怪物集合、 最大生命、 当前生命、 护盾、 攻击力
    void PushDevilDragon(QVector<Monster*>& ,int ,int ,int ,int );
    void PushSaberDragon(QVector<Monster*>& ,int ,int ,int ,int );
    void PushSakyamuni(QVector<Monster*>& ,int ,int ,int ,int );

    //把卡牌加入手牌
    void InitCard();
    void PushStrike();
    void PushDefense();
    void PushDoubleStrike();
    void PushAngry();
    void PushBreakingLimits();
    void PushIgnore();
    void PushMuscle();
    void PushHammer();
    void PushBarrier();
    void PushHitting();
    void PushMetallization();

    void paintEvent(QPaintEvent *); //背景图和关卡连线的绘画
private:
    Ui::ChooseLevelScene *ui;

signals:
    void chooseSceneBack(); //返回按钮信号
};

#endif // CHOOSELEVELSCENE_H
