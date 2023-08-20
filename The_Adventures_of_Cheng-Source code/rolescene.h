#ifndef ROLESCENE_H
#define ROLESCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
class RoleScene : public QMainWindow //选择英雄场景
{
    Q_OBJECT
public:
    explicit RoleScene(QWidget *parent = nullptr);

    int role_ID = 0; //已选英雄的ID
    QLabel * herointroduce = new QLabel("请选择英雄",this); //英雄介绍

    void paintEvent(QPaintEvent *);
    void UpdatePainting(); //更新英雄画面

    ChooseLevelScene * chooseLevelScene = NULL;
signals:
    void roleSceneBack(); //返回信号
};

#endif // ROLESCENE_H
