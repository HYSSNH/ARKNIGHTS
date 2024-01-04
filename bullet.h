#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QString>
#include <QSize>

#include "enemy.h"
#include "legends.h"
#include "gamescene.h"

class enemy;
class gamescene;
class legends;

class bullet :public QObject
{
    Q_OBJECT
    //子弹动态移动
    Q_PROPERTY(QPoint mycurrentPos READ getCurrentPos WRITE setCurrentPos)
public:
    bullet();
    bullet(QPoint startPos,QPoint targetPos,int damage,enemy * targetEnemy,gamescene * game,QString path=":/bullet.jpg");
    //    得到子弹的当前位置
    QPoint getCurrentPos();
    //    设置子弹的当前位置
    void setCurrentPos(QPoint pos);
    //    子弹的移动
    void move();
    //    绘画子弹
    void draw(QPainter * painter)const;
    //返回伤害
    int getDamage();
    //返回矩形区域
    QRect getRect();


public slots:
    //    击中敌人的时候触发信号
    void hitTarget();

private:
    //    子弹出发的坐标
    QPoint myStartPos;
    //    子弹的目标坐标
    QPoint myTargetPos;
    //    子弹现在的坐标
    QPoint mycurrentPos;
    //    子弹附带的伤害
    int myDamage;
    //    图片的路径
    QString myPath;
    //    子弹所指向的敌人
    enemy * myTargetEnemy;
    //    指向游戏场景
    gamescene * myGame;
    //    图片固定大小
    static const QSize myFixedSize;
};

#endif // BULLET_H
