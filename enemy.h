#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QPainter>
#include <QSize>
#include<cmath>

#include "waypoint.h"
#include "gamescene.h"
#include "legends.h"

class gamescene;
class legends;
class waypoint;

class enemy:public QObject
{
    Q_OBJECT
public:
   enemy(waypoint * startPoint, gamescene * game,QString path=":/0-1enemy.png");
    ~enemy();
    //绘画函数
    void virtual draw(QPainter * painter)const;
    //控制敌人的移动
    void move();
    //得到敌人的当前位置
    QPoint getPos();
    //被legend攻击
    void getAttacked(legends * legend0);
    //敌人被攻击受到伤害
    void getDamaged(int damage);
    //当血量非正时，敌人死亡，需要移除
    void getRemoved();
    //得到敌人的当前血量
    int getCurrentHp() const;
    //敌人脱离tower的攻击范围
    void getLostSight(legends * legend0);
    //碰撞函数
    bool ifCrash(QPoint p1,QPoint p2,int r1,int r2);
    //获取移动状态
    bool getMyactive();
    //返回矩形区域
    QRect getRect();
    //重置血量
    void reSetHp(int maxHp);


protected:
    //最大血量
    int myMaxHp;
    //当前血量
    int myCurrentHp;
    //移动速度
    int myWalkingSpeed;
    //是否可以移动
    bool myActive;
    //目标航点的指针
    waypoint * myDestinationWayPoint;
    //指向游戏的指针
    gamescene * myGame;
    //当前位置
    QPoint myPos;
    //图片路径
    QString myPath;
    //正在攻击该敌人的防御塔list
    QList<legends*> myAttackingLegendList;
    //    图片固定大小
    static const QSize myFixedSize;

public slots:
    void doActive();//敌人是否可以移动
};


#endif // ENEMY_H
