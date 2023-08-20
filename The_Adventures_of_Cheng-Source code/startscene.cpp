#include "startscene.h"
#include "ui_startscene.h"
#include "pushbutton_press.h"
#include "rolescene.h"
#include <QTimer>
#include <QPainter>
#include <QPixmap>

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartScene)
{
    ui->setupUi(this);

    //初始画面设置
    setFixedSize(1600,900);
    setWindowIcon(QIcon(":/Res/Icon.png"));
    setWindowTitle("成龙历险记");

    //退出按钮
    PushButton_press * exit_Btn = new PushButton_press(":/Res/exitbutton1.png");
    exit_Btn->setParent(this);
    exit_Btn->move(this->width() * 0.5 - exit_Btn->width() * 0.5,this->height()*0.6);
    connect(exit_Btn,&PushButton_press::clicked,[=](){
        exit_Btn->Zoom_down();
        exit_Btn->Zoom_up();
        QTimer::singleShot(500,this,[=](){
            this->close();
        });
    });

    //开始按钮
    PushButton_press * start_Btn = new PushButton_press(":/Res/startbutton1.png");
    start_Btn->setParent(this);
    start_Btn->move(this->width() * 0.5 - start_Btn->width() * 0.5,this->height()*0.4);

    //选择角色场景
    roleScene = new RoleScene;

    connect(start_Btn,&PushButton_press::clicked,[=](){

        start_Btn->Zoom_down();
        start_Btn->Zoom_up();

        //显示选择角色场景
        QTimer::singleShot(500,this,[=]()
        {
            roleScene->setGeometry(this->geometry());
            this->hide();
            roleScene->show();
            connect(roleScene,&RoleScene::roleSceneBack,this,[=]()
            {
                this->setGeometry(roleScene->geometry());
                roleScene->hide();
                this->show();
            });
        });


    });
}

StartScene::~StartScene()
{
    delete ui;
}

void StartScene::paintEvent(QPaintEvent *)
{
    //背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Res/startscenebg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

