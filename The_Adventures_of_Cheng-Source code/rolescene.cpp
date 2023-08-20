#include "rolescene.h"
#include "pushbutton_press.h"
#include "chooselevelscene.h"
#include "warrior.h"
#include "assassin.h"
#include <QLabel>
#include <QFont>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
RoleScene::RoleScene(QWidget *parent) : QMainWindow(parent)
{
    //初始画面设置
    setFixedSize(1600,900);
    setWindowIcon(QIcon(":/Res/Icon.png"));
    setWindowTitle("成龙历险记");

    //返回按钮
    PushButton_press * back_Btn = new PushButton_press(":/Res/exitbutton1.png");
    back_Btn->setParent(this);
    back_Btn->move(0,this->height() - back_Btn->height());

    connect(back_Btn,&QPushButton::clicked,[=](){
        back_Btn->Zoom_down();
        back_Btn->Zoom_up();
        QTimer::singleShot(500,this,[=](){
            emit this->roleSceneBack();
        });
    });

    //新建选择关卡界面
    chooseLevelScene = new ChooseLevelScene();
    connect(chooseLevelScene,&ChooseLevelScene::chooseSceneBack,[=](){
        this->hide();
        chooseLevelScene->hide();
        emit this->roleSceneBack();
    });

    //开始按钮
    PushButton_press * start_Btn = new PushButton_press(":/Res/gobutton.png");
    start_Btn->setParent(this);
    start_Btn->move(this->width() - start_Btn->width(), this->height() - start_Btn->height());

    //英雄介绍标签
    herointroduce->setGeometry(30,30,1000,100);
    herointroduce->setFont(QFont("微软雅黑", 18, QFont::Bold));
    herointroduce->setStyleSheet("color:yellow;");

    //选择角色1
    PushButton_press * role1_Btn = new PushButton_press(":/Res/warrior_btn.png");
    role1_Btn->setFixedSize(QSize(150,150));
    role1_Btn->setIconSize(QSize(150,150));
    role1_Btn->setParent(this);
    role1_Btn->move(300,this->height() - 200);

    connect(role1_Btn,&QPushButton::clicked,[=](){
        role1_Btn->Zoom_down();
        role1_Btn->Zoom_up();
        QTimer::singleShot(500,this,[=](){
            role_ID = 1; //更新英雄ID
            UpdatePainting();
            chooseLevelScene->he = new Warrior(90,90,0); //创建角色

            //重置开始按钮
            disconnect(start_Btn);
            connect(start_Btn,&QPushButton::clicked,[=](){
                start_Btn->Zoom_down();
                start_Btn->Zoom_up();
                QTimer::singleShot(500,this,[=](){
                    this->hide();
                    chooseLevelScene->show();
                });

            });
        });
    });

    //选择角色2
    PushButton_press * role2_Btn = new PushButton_press(":/Res/assassin_btn.png");
    role2_Btn->setFixedSize(QSize(150,150));
    role2_Btn->setIconSize(QSize(150,150));
    role2_Btn->setParent(this);
    role2_Btn->move(1200,this->height() - 200);

    connect(role2_Btn,&QPushButton::clicked,[=](){
        role2_Btn->Zoom_down();
        role2_Btn->Zoom_up();
        QTimer::singleShot(500,this,[=](){
            role_ID = 2; //更新英雄ID
            UpdatePainting();
            chooseLevelScene->he = new Assassin(60,60,0);//创建角色

            //重置开始按钮
            disconnect(start_Btn);
            connect(start_Btn,&QPushButton::clicked,[=](){
                start_Btn->Zoom_down();
                start_Btn->Zoom_up();
                QTimer::singleShot(500,this,[=](){
                    this->hide();
                    chooseLevelScene->show();
                });

            });
        });
    });
}

void RoleScene::UpdatePainting()
{
    //更新英雄介绍
    if (role_ID == 1)
    {
        herointroduce->setText("英雄技能：每场战斗结束后回复10点生命值。");
    } else if (role_ID == 2)
    {
        herointroduce->setText("英雄技能：每次攻击额外造成3点伤害。");
    } else
    {
        herointroduce->setText("请选择英雄");
    }

    //更新背景
    update();
}

void RoleScene::paintEvent(QPaintEvent *)
{
    //背景
    if (role_ID == 1)
    {
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/Res/warrior.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
    }
    else
    if (role_ID == 2)
    {
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/Res/assassin.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
    }
    else
    {
       QPainter painter(this);
       QPixmap pix;
       pix.load(":/Res/rolescenebg.png");
       painter.drawPixmap(0,0,this->width(),this->height(),pix);
    }
}
