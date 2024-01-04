#ifndef LEGENDS_H
#define LEGENDS_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QPixmap>

#include "gamescene.h"
#include "enemy.h"



class gamescene;
class QPainter;
class enemy;
class QTimer;

class legends  :  QObject
{
    Q_OBJECT
public:
    legends(QPoint pos,gamescene *game0,const QPixmap & sprite,int damage);
    ~legends();
    legends();

    //  画出防御塔
    void draw(QPainter * painter)const;
    //  攻击敌人
    void attackEnemy();
    //  当目标被击杀后
    void targetKilled();
    //  从可以攻击的敌人中，选出攻击的敌人
    void chooseEnemyFromAttack(enemy * enemy0);
    //  移除防御塔产生的子弹
    void removeBullet();
    //  丢失攻击目标的视野
    void lostSightOfEnemy();
    //  检查敌人是否在攻击范围中
    void checkEnemyInRange();
    //  重置伤害
    void reSetDamage(int damage);
    //  改变等级
    void levelChange();
    //  移除legend
    void getRemoved();
    //  得到正在攻击的敌人
    enemy * getAttackedEnemy();
    //void updateBullets();  //更新子弹
    //  返回伤害
    int getDamgae();
    //  返回等级
    int getLevel();

private slots:
    void shootWeapon();

private:
    //  是否攻击
    bool myAttacking;
    //  传奇攻击范围
    int myAttackRange;
    //  伤害
    int myDamage;
    //  开火
    int myFireRate;
    //  等级
    int myLevel;
    //  选择目标
    enemy * myChooseEnemy;
    //  指向地图的指针
    gamescene * myGame = NULL;
    //  开火时间
    QTimer * myFireRateTime;
    //  legend坐标
     const QPoint myPos;
    //  legend图片路径
     const QPixmap mySprite;
    //  legend固定大小
    static const QSize myFixedSize;

};

#endif // LEGENDS_H
