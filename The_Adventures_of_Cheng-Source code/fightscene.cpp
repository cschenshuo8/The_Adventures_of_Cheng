#include "fightscene.h"
#include "hero.h"
#include "monster.h"
#include "card.h"
#include "pushbutton_press.h"
#include <QVector>
#include <QProgressBar>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QFont>
#include <QPropertyAnimation>
#include <algorithm>
#include <random>

FightScene::FightScene(Hero * hero0, QVector<Monster*> monster0, QVector<Card *> card0)
{
    //初始设置
    he = hero0;
    monster_set = monster0;
    card_set = card0;
    for (auto ca: card_set)
    {
        disconnect(ca,0,0,0);
    }
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //初始画面设置
    setFixedSize(1600,900);
    setWindowIcon(QIcon(":/Res/Icon.png"));
    setWindowTitle("成龙历险记");
    update();

    //初始回合
    round = 0;
    roundLabel = new QLabel("Round: " + QString::number(round));
    roundLabel->setParent(this);
    roundLabel->setStyleSheet("color:white;");
    roundLabel->setFont(QFont("Microsoft YaHei", 20, 75));
    roundLabel->setFixedSize(500,100);
    roundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    roundLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    roundLabel->move((this->width() - 500) / 2, 0);

    //初始能量
    energy = 3;
    energyLabel = new QLabel("energy: " + QString::number(energy));
    energyLabel->setParent(this);
    energyLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    energyLabel->setStyleSheet("color:white;");
    energyLabel->setFixedSize(300,100);
    energyLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    energyLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    energyLabel->move(50,650);

    //初始英雄
    he->setParent(this);
    if (he->hero_ID == 1)
    {
        he->move(100,200);
    } else if (he->hero_ID == 2)
    {
        he->move(100,200);
    }
    qDebug() << he->strange;


    //英雄血条
    hebl = new QProgressBar;
    hebl->setParent(this);
    hebl->move(200,600);
    hebl->setFixedSize(250,30);
    hebl->setTextVisible(false);
    hebl->setRange(0,he->max_hp);
    hebl->setValue(he->now_hp);

    //英雄血量显示
    heLabel = new QLabel("HP: " + QString::number(he->now_hp) + " / " + QString::number(he->max_hp));
    heLabel->setParent(this);
    heLabel->move(200,600);
    heLabel->setFixedSize(250,30);
    heLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    heLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //英雄盾量显示
    heShield = new QLabel(QString::number(he->shield));
    heShield->setParent(this);
    heShield->move(120,550);
    heShield->setFixedSize(100,100);
    heShield->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    heShield->setAttribute(Qt::WA_TransparentForMouseEvents);

    //初始怪物
    int cnt = 0;
    for (auto mon:monster_set)
    {
        mon->setParent(this);
        mon->move(1000 + cnt * 300,300);

        //怪物血条
        QProgressBar * tmpbl = new QProgressBar;
        tmpbl->setParent(this);
        tmpbl->move(1000 + cnt * 300,600);
        tmpbl->setFixedSize(150,30);
        tmpbl->setTextVisible(false);
        tmpbl->setRange(0,mon->max_hp);
        tmpbl->setValue(mon->now_hp);
        monster_setbl.push_back(tmpbl);

        //怪物血量显示
        QLabel * tmpLabel = new QLabel("HP: " + QString::number(mon->now_hp) + " / " + QString::number(mon->max_hp));
        tmpLabel->setParent(this);
        tmpLabel->move(1000 + cnt * 300,600);
        tmpLabel->setFixedSize(150,30);
        tmpLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        tmpLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        monster_setLabel.push_back(tmpLabel);

        //怪物盾量显示
        QLabel * tmpShield = new QLabel(QString::number(he->shield));
        tmpShield->setParent(this);
        tmpShield->move(920 + cnt * 300,550);
        tmpShield->setFixedSize(100,100);
        tmpShield->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        tmpShield->setAttribute(Qt::WA_TransparentForMouseEvents);
        monster_setShield.push_back(tmpShield);

        cnt++;
    }

    //更新血量和能量
    UpdateHP();
    UpdateEnergy();

    //初始牌堆
    InitCard();
    //qDebug()<< 1<< endl;

    //初始化结束回合按钮
    end_btn = new PushButton_press(":/Res/endyourturn.png");
    end_btn->banned = 0;
    end_btn->setParent(this);
    end_btn->move(1500,800);
    connect(end_btn,&PushButton_press::clicked,[=](){
        end_btn->Zoom_down();
        end_btn->Zoom_up();
        StartEnemyTurn();
    });

}


void FightScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    //背景
    pix.load(":/Res/fightscenebg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //盾 
    pix.load(":/Res/sheild.png");
    painter.drawPixmap(120,550,100,100,pix);

    for (int i = 0; i < monster_set.size(); i++)
    {
        painter.drawPixmap(920 + i * 300,550,100,100,pix);
    }
}

void FightScene::IsEnded()
{
    //输
    if ((he->dead == 1) && (!isGameOver))
    {
        isGameOver = 1;
        emit this->LoseTheGame();
    }

    //赢
    bool malive = 0;
    for (auto mon: monster_set)
        if (mon->dead == 0)
            malive = 1;
    if ((!malive) && (!isGameOver))
    {
        isGameOver = 1;
        emit this->WinTheGame();
    }
}

void FightScene::StartYourTurn()
{
    //结束所有怪物回合
    for (auto mon: monster_set)
    {
        AfterTurn(mon);
    }
    //开始你的回合
    BeforeTurn(he);
    BanAllCard();
    UpdateEnergy();
    UpdateHP();
    IsEnded();

    //更新回合数和能量
    round++;
    roundLabel->setText("Round: " + QString::number(round));
    energy = 3;

    UpdateEnergy();
    UpdateHP();
    IsEnded();

    //回合开始时抽5张牌
    DrawCard(5);
}

void FightScene::StartEnemyTurn()
{

    BanAllCard(); //禁用你的卡牌

    //把所有剩余的手牌丢到弃牌堆
    timer2->start(500);
    connect(timer2,&QTimer::timeout,[=](){
        if (hand_card.empty()) //弃牌完成
        {
            timer2->stop();

            AfterTurn(he);
            for (auto mon: monster_set)
            {
                BeforeTurn(mon);
            }

            disconnect(timer2,&QTimer::timeout,0,0);

            for (auto mon: monster_set) //怪物攻击
            {
                if (!mon->dead)
                    mon->MonsterAttack(he,round);
            }
            ReleaseAllCard();
            StartYourTurn();
        }
        if (hand_card.size())
            DiscardCard(hand_card[hand_card.size()-1]);
    });

}

void FightScene::NewCard(Card* ca, int x0, int y0) //卡牌，卡牌初始位置
{
    ca->setParent(this);
    ca->move(x0,y0);

    //点击使用卡牌
    connect(ca,&Card::clicked,[=]()
    {
        if (energy >= ca->cost)
        {
            BanAllCard();
            //qDebug() << 1 << endl;
            ca->Useit(he, monster_set);

        }
    });

    //卡牌使用完成
    connect(ca,&Card::FinishCard,this,[=]()
    {
        //qDebug() << 2 << endl;
        AfterCard();
        DiscardCard(ca);
        energy -= ca->cost;
        UpdateEnergy();
        UpdateHP();
        IsEnded();
    });
}

void FightScene::InitCard()
{
    hand_card.clear(); //清空手牌
    discard.clear(); //清空弃牌堆
    undrawn_card = card_set; //将所有牌放入抽牌堆
    std::shuffle(undrawn_card.begin(),undrawn_card.end(),std::default_random_engine()); //打乱抽牌堆
    for (auto ca: undrawn_card) //初始化所有卡牌
    {
        NewCard(ca,-500,1500);
    }
}

void FightScene::DrawCard(int nu)
{
    BanAllCard(); //禁用所有卡牌
    this->tmp0 = nu + 3;

    //开始抽牌
    timer1->start(500);
    connect(timer1,&QTimer::timeout,[=]()
    {
        if (tmp0 > 3) //抽一张牌
        {
            if (undrawn_card.empty()) //如果抽牌堆空了，就重置抽牌堆
            {
                undrawn_card = discard;
                discard.clear();
                std::shuffle(undrawn_card.begin(),undrawn_card.end(),std::default_random_engine());
                for (auto ca: undrawn_card)
                        ca->move(-500,1500);
            }
            Card * tmp = undrawn_card[0];
            undrawn_card.pop_front();
            hand_card.push_front(tmp);
            UpdateCard();
            tmp0--;
        } else //抽牌完成
        {
            ReleaseAllCard();
            timer1->stop();
            disconnect(timer1,&QTimer::timeout,0,0);
        }
    });
}

void FightScene::DiscardCard(Card * ca)
{
    BanAllCard(); //禁用所有卡牌
    discard.push_back(ca);
    if (ca->width() > 160)
    {
        ca->FlashCard();
    }
    for (QVector<Card*>::iterator it = hand_card.begin(); it != hand_card.end(); it++) //寻找特定卡牌在手牌中的位置，并删除
        if (*it == ca)
        {
            hand_card.erase(it);
            break;
        }

    //弃牌动画
    timer1->start(500);
    UpdateCard();
    connect(timer1,&QTimer::timeout,[=]()
    {
        ReleaseAllCard();
        timer1->stop();
        disconnect(timer1,&QTimer::timeout,0,0);
    });
}

void FightScene::UpdateCard()
{
    //卡牌动画
    int n = hand_card.size(), tmp = 0;
    //qDebug() << n << endl;
    for (auto ca: discard) //更新弃牌堆
    {
        //ca->move();
        QPropertyAnimation * animation1 = new QPropertyAnimation(ca,"geometry");
        //时间间隔
        animation1->setDuration(200);
        //起始位置
        animation1->setStartValue(QRect(ca->x(),ca->y(),ca->width(),ca->height()));
        //结束位置
        animation1->setEndValue(QRect(2300,1300,ca->width(),ca->height()));

        animation1->setEasingCurve(QEasingCurve::Linear);
        animation1->start();
        //ca->move(2300,1300);
    }
    for (auto ca: hand_card) //更新手牌
    {
        //ca->move();
        QPropertyAnimation * animation1 = new QPropertyAnimation(ca,"geometry");
        //时间间隔
        animation1->setDuration(200);
        //起始位置
        animation1->setStartValue(QRect(ca->x(),ca->y(),ca->width(),ca->height()));
        //结束位置
        animation1->setEndValue(QRect((this->width() - n * 200) / 2 + tmp * 200,this->height() - 200,ca->width(),ca->height()));

        animation1->setEasingCurve(QEasingCurve::Linear);
        animation1->start();
        //ca->move((this->width() - 500) / n * tmp + 250,this->height() - 200);

        tmp++;
    }
    for (auto ca: undrawn_card) //更新抽牌堆
    {
        //ca->move();
        QPropertyAnimation * animation1 = new QPropertyAnimation(ca,"geometry");
        //时间间隔
        animation1->setDuration(200);
        //起始位置
        animation1->setStartValue(QRect(ca->x(),ca->y(),ca->width(),ca->height()));
        //结束位置
        animation1->setEndValue(QRect(-500,1500,ca->width(),ca->height()));

        animation1->setEasingCurve(QEasingCurve::Linear);
        animation1->start();
        //ca->move(-500,1500);
    }
}

void FightScene::BanAllCard()
{
    end_btn->banned = 1;
    for (auto ca: discard)
        ca->banned = 1;
    for (auto ca: hand_card)
        ca->banned = 1;
    for (auto ca: undrawn_card)
        ca->banned = 1;
}

void FightScene::ReleaseAllCard()
{
    end_btn->banned = 0;
    for (auto ca: discard)
        ca->banned = 0;
    for (auto ca: hand_card)
        ca->banned = 0;
    for (auto ca: undrawn_card)
        ca->banned = 0;
}

void FightScene::BanAllTarget()
{
    he->banned = 1;
    for (auto mon:monster_set)
        mon->banned = 1;
}

void FightScene::ReleaseAllTarget()
{
    he->banned = 0;
    for (auto mon:monster_set)
        mon->banned = 0;
}

void FightScene::UpdateEnergy()
{
    energyLabel->setText("energy: " + QString::number(energy));
}

void FightScene::UpdateHP()
{
    //更新英雄
    hebl->setRange(0,he->max_hp);
    hebl->setValue(he->now_hp);
    heShield->setText(QString::number(he->shield));
    heLabel->setText("HP: " + QString::number(he->now_hp) + " / " + QString::number(he->max_hp));

    //更新怪物
    for (int i = 0; i < monster_set.size(); i++)
    {
        monster_setbl[i]->setRange(0,monster_set[i]->max_hp);
        monster_setbl[i]->setValue(monster_set[i]->now_hp);
        monster_setShield[i]->setText(QString::number(monster_set[i]->shield));
        monster_setLabel[i]->setText("HP: " + QString::number(monster_set[i]->now_hp) + " / " + QString::number(monster_set[i]->max_hp));
    }
}

void FightScene::AfterCard()
{
    if (he->drawcard > 0) //如果卡牌有抽牌效果，抽牌
    {
        DrawCard(he->drawcard);
        he->drawcard = 0;
    }
    if (he->addenergy > 0) //如果卡牌有加能量效果，加能量
    {
        energy += he->addenergy;
        he->addenergy = 0;
    }
    //更新能量和血量
    UpdateEnergy();
    UpdateHP();
    IsEnded(); //判断战斗是否结束
}

void FightScene::BeforeTurn(Role * tar)
{
    if (tar->shieldforever == 0) tar->shield = 0; //如果有护盾永久化，就不会重置护盾
    if (tar->weak > 0) tar->weak--;
    if (tar->injured > 0) tar->injured--;
    tar->strange00 = 0;
    //更新能量和血量
    UpdateEnergy();
    UpdateHP();
    IsEnded(); //判断战斗是否结束
}

void FightScene::AfterTurn(Role * tar)
{
    tar->gainShield(tar->shieldeveryround); //每回合获得护盾
    //更新能量和血量
    UpdateEnergy();
    UpdateHP();
    IsEnded(); //判断战斗是否结束
}
