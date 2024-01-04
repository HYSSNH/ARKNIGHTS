#include "bullet.h"
#include "legends.h"
#include "gamescene.h"
#include "enemy.h"

#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QPropertyAnimation>

const QSize bullet::myFixedSize(8,8);

bullet::bullet()
{
}

bullet::bullet(QPoint startPos,QPoint targetPos,int damage,enemy * targetEnemy,gamescene * game,QString path):
    myStartPos(startPos),myTargetPos(targetPos),myDamage(damage),myPath(path),myTargetEnemy(targetEnemy),myGame(game)
{
}

//获取当前坐标
QPoint bullet::getCurrentPos()
{
    return mycurrentPos;
}

//设定当前坐标
void bullet::setCurrentPos(QPoint pos)
{
    mycurrentPos = pos;
}

void bullet::move()
{
    //子弹飞行的时间，经过 30ms 击中敌人
    static int duration = 150;
    QPropertyAnimation * animation = new QPropertyAnimation(this,"mycurrentPos");
    //设置持续时间
    animation->setDuration(duration);
    //设置起始坐标
    animation->setStartValue(myStartPos);
    //设置目标坐标
    animation->setEndValue(myTargetPos);
    //击中敌人后，子弹动态运动结束
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
    animation->start();
    //    qDebug() <<"move";
}

// bullet类的getdamage()函数，返回子弹的伤害值
int bullet::getDamage()
{
    // 返回子弹的伤害值
    return myDamage;
}

// bullet类的getrect()函数，返回子弹的矩形区域
QRect bullet::getRect()
{
    // 获取子弹的当前位置
    QPoint pos = getCurrentPos();
    // 获取子弹的图片大小
    QSize size = QPixmap(myPath).size();
    // 返回一个以pos为中心，size为大小的矩形
    return QRect(pos.x() - size.width() / 2, pos.y() - size.height() / 2, size.width(), size.height());
}

void bullet::hitTarget()
{
    //如果敌人列表中，有子弹击中的这个敌人，该敌人受到相应的伤害
    if(myGame->getMyEnemyList().indexOf(myTargetEnemy) != -1)
    {
        myTargetEnemy->getDamaged(myDamage);
    }
    //击中敌人后子弹就要消失
    myGame->removeBullet(this);
}

void bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(mycurrentPos,myPath);
}
