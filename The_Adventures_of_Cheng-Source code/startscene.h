#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "rolescene.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartScene; }
QT_END_NAMESPACE

class StartScene : public QMainWindow //开始画面场景
{
    Q_OBJECT

public:
    StartScene(QWidget *parent = nullptr);
    ~StartScene();

    void paintEvent(QPaintEvent *);

private:
    Ui::StartScene *ui;

    RoleScene * roleScene = NULL;
};
#endif // STARTSCENE_H
