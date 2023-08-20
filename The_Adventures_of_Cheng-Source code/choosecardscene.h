#ifndef CHOOSECARDSCENE_H
#define CHOOSECARDSCENE_H

#include "card.h"
#include <QMainWindow>
#include <QTime>

class ChooseCardScene : public QMainWindow //选择卡牌场景
{
    Q_OBJECT
public:
    ChooseCardScene(QVector<Card *>& );

    QVector<Card *>& card_set; //手牌集合

    //随机生成的三张卡牌
    Card * ca1 = NULL;
    Card * ca2 = NULL;
    Card * ca3 = NULL;

    //随机生成的三张卡牌的编号
    int tmp1 = 0;
    int tmp2 = 0;
    int tmp3 = 0;

    int GenerateRandomNumber(int); //获取随机数
    Card* GetACard(int ); //获取对应卡牌编号的卡牌
    void ChangeIntoHandCard(Card * ca); //将选中的卡牌放入手牌集合
signals:
    void FinishSelect(); //完成选择卡牌信号
};

#endif // CHOOSECARDSCENE_H
