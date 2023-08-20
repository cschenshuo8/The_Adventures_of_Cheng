#include "angry.h"

Angry::Angry(): UndirCard(":/Res/angry.png", 0) //卡牌路径、 卡牌能量消耗
{

}

//效果：能量+1
void Angry::Useit(Hero * he, QVector<Monster *> monster_set)
{
    //刷新卡牌图片状态
    if (this->width() > 160)
    {
        this->FlashCard();
    }

    //使用卡牌
    he->addenergy += 1;
    emit this->FinishCard(); //卡牌使用完成，发送信号
}
