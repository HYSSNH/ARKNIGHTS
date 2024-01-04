#include "legends.h"
#include<QPoint>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

#include "gamescene.h"
#include "utility.h"
#include "bullet.h"
#include "enemy.h"

const QSize legends::myFixedSize(120,120);

legends::legends()
{
}

legends::legends(QPoint pos,gamescene * game, const QPixmap & sprite,int damage):
    myAttacking(false),
    myAttackRange(250),
    myDamage(damage),
    myFireRate(1000),
    myLevel(1),
    myChooseEnemy(NULL),
    myGame(game),
    myPos(pos),
    mySprite(sprite)
{
    myFireRateTime=new QTimer(this);
    connect(myFireRateTime,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}

legends::~legends()
{

    myFireRateTime = NULL;
    myChooseEnemy = NULL;
    myGame = NULL;
    delete myFireRateTime;
    delete myChooseEnemy;
}



void legends::draw(QPainter *painter) const
{
    //  保存第一次状态
    painter->save();

    //  画出防御塔的图片
    painter->drawPixmap(myPos.x() - myFixedSize.width() * 2/3,myPos.y() - myFixedSize.height() * 3/5,mySprite);
    //  保存第二次状态
    painter->save();

    painter->setPen(Qt::green);
    painter->drawEllipse(myPos,myAttackRange,myAttackRange);
    //  把防御塔的等级画出来
    painter->drawText(QRect(this->myPos.x() - 30,this->myPos.y() + 15,100,25),QString("level: %1").arg(myLevel));
    //  恢复第二次状态
    painter->restore();
    //  恢复第一次状态
    painter->restore();

}


void legends::chooseEnemyFromAttack(enemy *enemy0)
{
    myChooseEnemy = enemy0;
    attackEnemy();
    //  该敌人受到该防御塔的攻击
    myChooseEnemy->getAttacked(this);
}




void legends::attackEnemy()
{
    //  开始攻击
    myFireRateTime->start(myFireRate);
}

void legends::shootWeapon()
{
    //构造子弹，准备攻击敌人
    bullet * bullet = new class bullet(myPos,myChooseEnemy->getPos()
                                       ,myDamage,myChooseEnemy,myGame);
    bullet->move();
    //将该子弹添加到gamescene中
    myGame->addBullet(bullet);
}

void legends::targetKilled()
{
    if(myChooseEnemy)
    {
        myChooseEnemy = NULL;
    }
    //敌人死亡，停止开火
    myFireRateTime->stop();
}

void legends::lostSightOfEnemy()
{
    myChooseEnemy->getLostSight(this);
    if(myChooseEnemy)
    {
        myChooseEnemy = NULL;
    }
    myFireRateTime->stop();
}

void legends::checkEnemyInRange()
{
    if(myChooseEnemy)//如果有了攻击的敌人
    {
        QVector2D normalized(myChooseEnemy->getPos() - myPos);
        normalized.normalize();
        //当敌人不在范围内的时候
        if(!collisionWithCircle(myPos,myAttackRange,myChooseEnemy->getPos(),1))
        {
            lostSightOfEnemy();
        }
    }
    else//如果没有攻击的敌人，就遍历enemylist，找到在攻击范围内的敌人
    {
        QList<enemy * > enemyList = myGame->getMyEnemyList();
        foreach(enemy * enemy,enemyList)
            if(collisionWithCircle(myPos,myAttackRange,enemy->getPos(),1))
            {
                chooseEnemyFromAttack(enemy);
                break;
            }
    }
}
void legends::reSetDamage(int damage)
{
    myDamage = damage;
}

void legends::levelChange()
{
    myLevel++;
}

int legends::getLevel()
{
    return myLevel;
}

int legends::getDamgae()
{
    return myDamage;
}
enemy * legends::getAttackedEnemy()
{
    return myChooseEnemy;
}
void legends::getRemoved()
{
    if(getAttackedEnemy())//这里要判断是不是空指针NULL
    {
        getAttackedEnemy()->getLostSight(this);
    }
    myGame->removeLegend(this);
}
