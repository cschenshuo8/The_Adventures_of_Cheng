#include "chooselevelscene.h"
#include "ui_chooselevelscene.h"
#include "pushbutton_press.h"
#include "fightscene.h"
#include "warrior.h"
#include "slim.h"
#include "devildragon.h"
#include "saberdragon.h"
#include "sakyamuni.h"
#include "monster.h"
#include "strike.h"
#include "defense.h"
#include "doublestrike.h"
#include "angry.h"
#include "breakinglimits.h"
#include "ignore.h"
#include "muscle.h"
#include "hammer.h"
#include "barrier.h"
#include "hitting.h"
#include "metallization.h"

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QPainter>
#include <QMessageBox>

ChooseLevelScene::ChooseLevelScene(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseLevelScene)
{
    ui->setupUi(this);
    srand((int)time(0));

    //初始画面设置
    setFixedSize(1600,900);
    setWindowIcon(QIcon(":/Res/Icon.png"));
    setWindowTitle("成龙历险记");

    //返回按钮
    PushButton_press * back_Btn = new PushButton_press(":/Res/saveandexitbutton.png");
    back_Btn->setParent(this);
    back_Btn->move(this->width() - back_Btn->width(),this->height() - back_Btn->height());

    connect(back_Btn,&QPushButton::clicked,[=](){
        back_Btn->Zoom_down();
        back_Btn->Zoom_up();
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //创建怪物
    InitMonster();

    //创建卡牌
    InitCard();

    //ChooseCard();

    //qDebug()<< 1<<endl;
    //当前关卡标签
    nowLevelLabel = new QLabel("当前所在关卡：1",this);
    nowLevelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    nowLevelLabel->setStyleSheet("color:blue;");
    nowLevelLabel->setGeometry(this->width() / 2 - 100,30,400,50);


    //关卡创建
    //第1关
    l1_Btn = new PushButton_press(":/Res/monster.png","",0.5);
    l1_Btn->setParent(this);
    l1_Btn->move(100,100);
    levelLabel = new QLabel("1",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(130,170,50,50);


    //第2关
    l2_Btn = new PushButton_press(":/Res/monster.png","",0.5);
    l2_Btn->setParent(this);
    l2_Btn->move(300,300);
    l2_Btn->banned = 1;
    levelLabel = new QLabel("2",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(330,370,50,50);

    //第3关
    l3_Btn = new PushButton_press(":/Res/monster.png","",0.5);
    l3_Btn->setParent(this);
    l3_Btn->move(700,600);
    l3_Btn->banned = 1;
    levelLabel = new QLabel("4",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(730,670,50,50);

    //第4关
    l4_Btn = new PushButton_press(":/Res/monster.png","",0.5);
    l4_Btn->setParent(this);
    l4_Btn->move(1000,300);
    l4_Btn->banned = 1;
    levelLabel = new QLabel("5",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(1030,370,50,50);

    //最终关
    l5_Btn = new PushButton_press(":/Res/elite monster.png","",0.5);
    l5_Btn->setParent(this);
    l5_Btn->move(1300,700);
    l5_Btn->banned = 1;
    levelLabel = new QLabel("7",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(1330,770,50,50);

    //第一个营地
    r1_Btn = new PushButton_press(":/Res/camp.png","",0.5);
    r1_Btn->setParent(this);
    r1_Btn->move(500,400);
    r1_Btn->banned = 1;
    levelLabel = new QLabel("3",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(530,470,50,50);

    //第二个营地
    r2_Btn = new PushButton_press(":/Res/camp.png","",0.5);
    r2_Btn->setParent(this);
    r2_Btn->move(1200,500);
    r2_Btn->banned = 1;
    levelLabel = new QLabel("6",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(1230,570,50,50);

    //随机关卡
    u1_Btn = new PushButton_press(":/Res/unknown.png","",0.5);
    u1_Btn->setParent(this);
    u1_Btn->move(450,600);
    u1_Btn->banned = 1;
    levelLabel = new QLabel("3",this);
    levelLabel->setFont(QFont("微软雅黑", 18, QFont::Bold));
    levelLabel->setStyleSheet("color:yellow;");
    levelLabel->setGeometry(480,670,50,50);

    //关卡生成
    //第1关
    connect(l1_Btn,&PushButton_press::clicked,[=](){
        BeforeFighting();
        f_scene = new FightScene(he, monster_set[0], card_set); //新建关卡（怪物集合、手牌集合）
        f_scene->show();
        this->hide();

        //胜利信号
        connect(f_scene,&FightScene::WinTheGame,[=](){
            f_scene->hide();
            this->show();
            AfterFighting();           
            ChooseCard(); //获得新卡牌

            //解锁新关卡
            l2_Btn->banned = 0;
            nowLevelLabel->setText("当前所在关卡：2");
        });

        //败北信号
        connect(f_scene,&FightScene::LoseTheGame,[=](){
            //生成提示框，游戏失败
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("很遗憾，您战败了，请重新开始游戏。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                f_scene->hide();
                this->show();
                emit this->chooseSceneBack();
            }
        });
        f_scene->StartYourTurn();
        l1_Btn->banned = 1; //禁用本关
    });

    //第2关
    connect(l2_Btn,&PushButton_press::clicked,[=](){
        BeforeFighting();
        f_scene = new FightScene(he, monster_set[1], card_set);
        f_scene->show();
        this->hide();
        connect(f_scene,&FightScene::WinTheGame,[=](){
            f_scene->hide();
            this->show();
            AfterFighting();
            ChooseCard();
            r1_Btn->banned = 0;
            u1_Btn->banned = 0;
            nowLevelLabel->setText("当前所在关卡：3");
        });
        connect(f_scene,&FightScene::LoseTheGame,[=](){
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("很遗憾，您战败了，请重新开始游戏。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                f_scene->hide();
                this->show();
                emit this->chooseSceneBack();
            }
        });
        f_scene->StartYourTurn();
        l2_Btn->banned = 1;
    });

    //第3关
    connect(l3_Btn,&PushButton_press::clicked,[=](){
        BeforeFighting();
        f_scene = new FightScene(he, monster_set[2], card_set);
        f_scene->show();
        this->hide();
        connect(f_scene,&FightScene::WinTheGame,[=](){
            f_scene->hide();
            this->show();
            AfterFighting();
            ChooseCard();
            l4_Btn->banned = 0;
            nowLevelLabel->setText("当前所在关卡：5");
        });
        connect(f_scene,&FightScene::LoseTheGame,[=](){
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("很遗憾，您战败了，请重新开始游戏。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                f_scene->hide();
                this->show();
                emit this->chooseSceneBack();
            }
        });
        f_scene->StartYourTurn();
        l3_Btn->banned = 1;
    });

    //第4关
    connect(l4_Btn,&PushButton_press::clicked,[=](){
        BeforeFighting();
        f_scene = new FightScene(he, monster_set[3], card_set);
        f_scene->show();
        this->hide();
        connect(f_scene,&FightScene::WinTheGame,[=](){
            f_scene->hide();
            this->show();
            AfterFighting();
            ChooseCard();
            r2_Btn->banned = 0;
            nowLevelLabel->setText("当前所在关卡：6");
        });
        connect(f_scene,&FightScene::LoseTheGame,[=](){
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("很遗憾，您战败了，请重新开始游戏。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                f_scene->hide();
                this->show();
                emit this->chooseSceneBack();
            }
        });
        f_scene->StartYourTurn();
        l4_Btn->banned = 1;
    });

    //第5关
    l5_Btn->banned = 0;
    connect(l5_Btn,&PushButton_press::clicked,[=](){
        BeforeFighting();
        f_scene = new FightScene(he, monster_set[4], card_set);
        f_scene->show();
        this->hide();
        connect(f_scene,&FightScene::WinTheGame,[=](){
            f_scene->hide();
            this->show();
            AfterFighting();
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("恭喜您击败圣主，成功通关本游戏。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                f_scene->hide();
                this->show();
                emit this->chooseSceneBack();
            }
            //ChooseCard();
        });
        connect(f_scene,&FightScene::LoseTheGame,[=](){
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("很遗憾，您战败了，请重新开始游戏。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                f_scene->hide();
                this->show();
                emit this->chooseSceneBack();
            }
        });
        f_scene->StartYourTurn();
        l5_Btn->banned = 1;
    });

    //第一个营地
    connect(r1_Btn,&PushButton_press::clicked,[=](){
        r1_Btn->banned = 1;
        u1_Btn->banned = 1;
        he->hell((int) (he->max_hp * 0.4)); //回复最大生命值40%的HP
        tmpMessage = QMessageBox::information(this, tr("提示"), tr("路过营地，回复最大生命值40%的生命值。"), QMessageBox::Ok);
        if (tmpMessage == QMessageBox::Ok)
        {
            //解锁新关卡
            nowLevelLabel->setText("当前所在关卡：4");
            l3_Btn->banned = 0;
        }
    });

    //第二个营地
    connect(r2_Btn,&PushButton_press::clicked,[=](){
        r2_Btn->banned = 1;
        he->hell((int) (he->max_hp * 0.4));
        tmpMessage = QMessageBox::information(this, tr("提示"), tr("路过营地，回复最大生命值40%的生命值。"), QMessageBox::Ok);
        if (tmpMessage == QMessageBox::Ok)
        {
            nowLevelLabel->setText("当前所在关卡：7");
            l5_Btn->banned = 0;
        }
    });

    //随机关卡
    connect(u1_Btn,&PushButton_press::clicked,[=](){
        r1_Btn->banned = 1;
        u1_Btn->banned = 1;
        int randtmp = rand() % 3; //随机事件
        randtmp = 2;
        if (randtmp == 0) //回血
        {
            he->hell(20);
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("您在路上捡到一个神奇的苹果，吃下后回复了20点生命值。"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                nowLevelLabel->setText("当前所在关卡：4");
                l3_Btn->banned = 0;
            }
        } else
        if (randtmp == 1) //掉血
        {
            he->beAttack(10);
            tmpMessage = QMessageBox::information(this, tr("提示"), tr("您在路上遇到山体滑坡，不慎被滑落的岩石砸中，损失10点生命值"), QMessageBox::Ok);
            if (tmpMessage == QMessageBox::Ok)
            {
                nowLevelLabel->setText("当前所在关卡：4");
                l3_Btn->banned = 0;
            }
        } else //战斗
        {
            BeforeFighting();
            f_scene = new FightScene(he, monster_set[5], card_set);
            f_scene->show();
            this->hide();

            //战斗胜利
            connect(f_scene,&FightScene::WinTheGame,[=](){
                f_scene->hide();
                this->show();
                AfterFighting();
                ChooseCard();
                l3_Btn->banned = 0;
                nowLevelLabel->setText("当前所在关卡：4");
            });

            //战斗败北
            connect(f_scene,&FightScene::LoseTheGame,[=](){
                tmpMessage = QMessageBox::information(this, tr("提示"), tr("很遗憾，您战败了，请重新开始游戏。"), QMessageBox::Ok);
                if (tmpMessage == QMessageBox::Ok)
                {
                    f_scene->hide();
                    this->show();
                    emit this->chooseSceneBack();
                }
            });
            f_scene->StartYourTurn();
        }
    });
}

ChooseLevelScene::~ChooseLevelScene()
{
    delete ui;
}

void ChooseLevelScene::BeforeFighting()
{
    //如果是刺客，开局获得3点力量
    if (he->hero_ID == 2) he->strange = 3;
        else he->strange = 0;

    //重置其他属性
    he->strange00 = 0;
    he->weak = 0;
    he->injured = 0;
    he->drawcard = 0;
    he->addenergy = 0;
    he->shieldforever = 0;
    he->shield = 0;
    he->dead = 0;
}

void ChooseLevelScene::AfterFighting()
{
    //重置属性
    he->strange = 0;
    he->strange00 = 0;
    he->weak = 0;
    he->injured = 0;
    he->drawcard = 0;
    he->addenergy = 0;
    he->shieldforever = 0;
    he->shield = 0;
    he->dead = 0;

    //如果是战士，回复10点生命值
    if (he->hero_ID == 1) he->hell(10);
}

void ChooseLevelScene::ChooseCard()
{
    c_scene = new ChooseCardScene(card_set);
    this->hide();
    c_scene->show();
    connect(c_scene, &ChooseCardScene::FinishSelect,[=](){
        c_scene->hide();
        this->show();
    });
}

void ChooseLevelScene::InitMonster()
{
    //组合1：三只史莱姆
    QVector<Monster*> tmp;
    PushSlim(tmp,11,11,0,4);
    PushSlim(tmp,10,10,0,4);
    PushSlim(tmp,12,12,0,4);
    monster_set.push_back(tmp);

    //组合2：三只史莱姆
    tmp.clear();
    PushSlim(tmp,20,20,0,6);
    PushSlim(tmp,20,20,0,6);
    PushSlim(tmp,20,20,0,6);
    monster_set.push_back(tmp);

    //组合3：三只恶龙
    tmp.clear();
    PushDevilDragon(tmp,30,30,0,6);
    PushDevilDragon(tmp,30,30,0,6);
    PushDevilDragon(tmp,30,30,0,6);
    monster_set.push_back(tmp);

    //组合4：两只恶龙，一只刀龙
    tmp.clear();
    PushDevilDragon(tmp,30,30,0,6);
    PushSaberDragon(tmp,20,20,0,8);
    PushDevilDragon(tmp,30,30,0,6);
    monster_set.push_back(tmp);

    //组合5：一只圣主
    tmp.clear();
    PushSakyamuni(tmp,70,70,0,5);
    monster_set.push_back(tmp);

    //组合6：一只恶龙，一只史莱姆
    tmp.clear();
    PushSlim(tmp,20,20,0,5);
    PushDevilDragon(tmp,30,30,0,6);
    monster_set.push_back(tmp);
}

void ChooseLevelScene::PushSlim(QVector<Monster*>& mon, int mh, int nh, int sh, int att)
{

    Slim * tmp = new Slim(mh, nh, sh, att);
    mon.push_back(tmp);
}

void ChooseLevelScene::PushSaberDragon(QVector<Monster*>& mon, int mh, int nh, int sh, int att)
{

    SaberDragon * tmp = new SaberDragon(mh, nh, sh, att);
    mon.push_back(tmp);
}

void ChooseLevelScene::PushSakyamuni(QVector<Monster*>& mon, int mh, int nh, int sh, int att)
{

    Sakyamuni * tmp = new Sakyamuni(mh, nh, sh, att);
    mon.push_back(tmp);
}

void ChooseLevelScene::PushDevilDragon(QVector<Monster*>& mon, int mh, int nh, int sh, int att)
{

    DevilDragon * tmp = new DevilDragon(mh, nh, sh, att);
    mon.push_back(tmp);
}

void ChooseLevelScene::InitCard()
{
    //起始手牌为5张打击，5张防御
    for (int i = 0; i < 5; i++)
        PushStrike();
    for (int i = 0; i < 5; i++)
        PushDefense();
}

void ChooseLevelScene::PushStrike()
{
    Strike * ca = new Strike();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushDefense()
{
    Defense * ca = new Defense();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushDoubleStrike()
{
    DoubleStrike * ca = new DoubleStrike();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushAngry()
{
    Angry * ca = new Angry();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushBreakingLimits()
{
    BreakingLimits * ca = new BreakingLimits();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushIgnore()
{
    Ignore * ca = new Ignore();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushMuscle()
{
    Muscle * ca = new Muscle();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushHammer()
{
    Hammer * ca = new Hammer();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushBarrier()
{
    Barrier * ca = new Barrier();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushHitting()
{
    Hitting * ca = new Hitting();
    card_set.push_back(ca);
}

void ChooseLevelScene::PushMetallization()
{
    Metallization * ca = new Metallization();
    card_set.push_back(ca);
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Res/chooselevelscenebg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //关卡之间的连线
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 160, 230), 2.5));
    painter.drawLine(QPointF(170,170),QPointF(330,330));
    painter.drawLine(QPointF(370,370),QPointF(530,430));
    painter.drawLine(QPointF(570,470),QPointF(730,630));
    painter.drawLine(QPointF(770,630),QPointF(1030,370));
    painter.drawLine(QPointF(1070,370),QPointF(1230,530));
    painter.drawLine(QPointF(1270,570),QPointF(1330,730));
    painter.drawLine(QPointF(370,370),QPointF(480,630));
    painter.drawLine(QPointF(520,650),QPointF(730,650));
}
