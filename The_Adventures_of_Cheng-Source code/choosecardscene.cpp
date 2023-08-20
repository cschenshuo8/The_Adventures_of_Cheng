#include <QPushButton>
#include <QVector>
#include <QDebug>
#include "choosecardscene.h"
#include "doublestrike.h"
#include "angry.h"
#include "breakinglimits.h"
#include "ignore.h"
#include "muscle.h"
#include "hammer.h"
#include "barrier.h"
#include "hitting.h"
#include "metallization.h"
#include <QLabel>

ChooseCardScene::ChooseCardScene(QVector<Card *>& card_set00): card_set(card_set00)
{
    srand((int)time(0));
    //基础面板设置
    setFixedSize(1600,900);
    setWindowIcon(QIcon(":/Res/Icon.png"));
    setWindowTitle("成龙历险记");

    //标题设置
    QLabel * titleLabel = new QLabel("恭喜您获得本场战斗的胜利，请选择一张卡牌加入您的牌库。",this);
    titleLabel->setGeometry(this->width() / 2 - 300,30,1000,100);
    titleLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    titleLabel->setStyleSheet("color:black;");

    //生成三张牌
    tmp1 = tmp2 = tmp3 = -1;
    tmp1 = GenerateRandomNumber(9);
    while (tmp2 == tmp1 || tmp2 == -1)
    {
        tmp2 = GenerateRandomNumber(9);
    }
    while (tmp3 == tmp2 || tmp3 == tmp1 || tmp3 == -1)
    {
        tmp3 = GenerateRandomNumber(9);
    }

    //tmp1 = tmp2 = tmp3 = 2;

    QPixmap pix;

    //卡牌1获取
    ca1 = GetACard(tmp1);
    ca1->ischoosecard = 1;
    pix.load(ca1->Img);
    ca1->setFixedSize(400,500);
    ca1->setStyleSheet("QPushButton{border:0px;}");
    ca1->setIcon(pix);
    ca1->setIconSize(QSize(400,500));
    ca1->setParent(this);
    ca1->move(260, 250);

    //卡牌2获取
    ca2 = GetACard(tmp2);
    ca2->ischoosecard = 1;
    pix.load(ca2->Img);
    ca2->setFixedSize(400,500);
    ca2->setStyleSheet("QPushButton{border:0px;}");
    ca2->setIcon(pix);
    ca2->setIconSize(QSize(400,500));
    ca2->setParent(this);
    ca2->move(760, 250);

    //卡牌3获取
    ca3 = GetACard(tmp3);
    ca3->ischoosecard = 1;
    pix.load(ca3->Img);
    ca3->setFixedSize(400,500);
    ca3->setStyleSheet("QPushButton{border:0px;}");
    ca3->setIcon(pix);
    ca3->setIconSize(QSize(400,500));
    ca3->setParent(this);
    ca3->move(1260, 250);

    //qDebug()<< 1 <<endl;

    //选择卡牌1
    connect(ca1, &Card::clicked,[=](){
        card_set.push_back(ca1);
        ChangeIntoHandCard(ca1);
        disconnect(ca1,&Card::clicked,0,0);
        disconnect(ca2,&Card::clicked,0,0);
        disconnect(ca3,&Card::clicked,0,0);
        emit this->FinishSelect();
    });

    //选择卡牌2
    connect(ca2, &Card::clicked,[=](){
        card_set.push_back(ca2);
        ChangeIntoHandCard(ca2);
        disconnect(ca1,&Card::clicked,0,0);
        disconnect(ca2,&Card::clicked,0,0);
        disconnect(ca3,&Card::clicked,0,0);
        emit this->FinishSelect();
    });

    //选择卡牌3
    connect(ca3, &Card::clicked,[=](){
        card_set.push_back(ca3);
        ChangeIntoHandCard(ca3);
        disconnect(ca1,&Card::clicked,0,0);
        disconnect(ca2,&Card::clicked,0,0);
        disconnect(ca3,&Card::clicked,0,0);
        emit this->FinishSelect();
    });
}

void ChooseCardScene::ChangeIntoHandCard(Card * ca)
{
    QPixmap pix;
    pix.load(ca->Img);

    //设置图片固定大小
    ca->setFixedSize(160,200);

    //设置样式
    ca->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    ca->setIcon(pix);

    //设置图片大小
    ca->setIconSize(QSize(160,200));

    ca->ischoosecard = 0;
}

int ChooseCardScene::GenerateRandomNumber(int highest)
{
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int ret = rand() % highest;
    return ret;
}

Card* ChooseCardScene::GetACard(int cad)
{
    //按编号返回对应卡牌
    if (cad == 0)
    {
        Card * ca = new DoubleStrike();
        return ca;
    } else
    if (cad == 1)
    {
        Card * ca = new Angry();
        return ca;
    } else
    if (cad == 2)
    {
        Card * ca = new BreakingLimits();
        return ca;
    } else
    if (cad == 3)
    {
        Card * ca = new Ignore();
        return ca;
    } else
    if (cad == 4)
    {
        Card * ca = new Muscle();
        return ca;
    } else
    if (cad == 5)
    {
        Card * ca = new Hammer();
        return ca;
    } else
    if (cad == 6)
    {
        Card * ca = new Barrier();
        return ca;
    } else
    if (cad == 7)
    {
        Card * ca = new Hitting();
        return ca;
    } else
    if (cad == 8)
    {
        Card * ca = new Metallization();
        return ca;
    } else
        return NULL;
}
