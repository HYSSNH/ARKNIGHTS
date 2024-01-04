#include "enemy.h"

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QVector2D>
#include <QDebug>

//敌人图片大小
const QSize enemy::myFixedSize(110,110);

enemy::enemy(waypoint * startWayPoint,gamescene *game,QString path):
    QObject(0),myGame(game),myPos(startWayPoint->getPos()),myPath(path)
{
    //初始生命值
    myMaxHp = 50;
    //当前生命值初始化
    myCurrentHp = myMaxHp;
    //移动速度初始化
    myWalkingSpeed = 2;
    //移动状态初始化
    myActive = false;
    //下一个航点初始化
    myDestinationWayPoint = startWayPoint->getNextWayPoint();
}

//析构后的善后
enemy::~enemy()
{
    //清除在攻击该敌人的防御塔
    myAttackingLegendList.clear();
    //全部设为空指针
    myDestinationWayPoint = NULL;
    myGame = NULL;
}

//判断是否碰撞
bool enemy::ifCrash(QPoint p1,QPoint p2,int r1,int r2)
{
    //点在r1,r2之间
    int xx = p1.x() - p2.x();
    int yy = p1.y() - p2.y();
    int distance = sqrt(xx * xx + yy * yy);
    if(distance < r1 + r2)
    {
        return true;
    }
    return false;
}

// bullet类的getrect()函数，返回子弹的矩形区域
QRect enemy::getRect()
{
    // 获取子弹的当前位置
    QPoint pos = getPos();
    // 获取子弹的图片大小
    QSize size = QPixmap(myPath).size();
    // 返回一个以pos为中心，size为大小的矩形
    return QRect(pos.x() - size.width() / 2, pos.y() - size.height() / 2, size.width(), size.height());
}


//绘画函数
void enemy::draw(QPainter *painter) const
{
    //如果敌人不能移动，就不对它进行绘画
    if(!myActive)
    {
        return ;
    }

    painter->save();
    //画出敌人
    //得到图片的左上点
    QPoint tmp(myPos.x() - myFixedSize.width() / 2,myPos.y() - myFixedSize.height() / 2);
    painter->drawPixmap(tmp.x(),tmp.y(),90,90,myPath);

    //设置血条的长度
    int barWidth = myFixedSize.width();
    int barHeight = 5;
    QPoint healthBarPoint = myPos + QPoint(-barWidth / 2, -myFixedSize.height() / 2 - barHeight - 5);

    //画出血条背景
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(QRect(healthBarPoint, QSize(barWidth, barHeight)));

    //画出当前血量的血条
    painter->setBrush(Qt::green);
    double healthRatio = (double)myCurrentHp / myMaxHp;
    int currentBarWidth = qMax(0, static_cast<int>(barWidth * healthRatio));
    painter->drawRect(QRect(healthBarPoint, QSize(currentBarWidth, barHeight)));

    painter->restore();
}


//得到敌人当前血量
int enemy::getCurrentHp() const
{
    return myCurrentHp;
}

//敌人移动状态设置
void enemy::move()
{
    //如果不能移动，就直接退出函数
    if(!myActive)
    {
        return ;
    }
    //如果到达了目标航点
    if(ifCrash(myPos,myDestinationWayPoint->getPos(),15,15))
    {
        //如果还存在下一个航点
        if(myDestinationWayPoint->getNextWayPoint())
        {
            //重新设置敌人的位置，和目标航点
            myPos = myDestinationWayPoint->getPos();
            myDestinationWayPoint = myDestinationWayPoint->getNextWayPoint();
        }
        //如果没有下一个航点了，代表敌人到达基地
        else
        {
            //更改行动状态
            myActive = false;
            //基地扣血
            myGame->getHpDamaged();
            //移除这个敌人
            myGame->removeEnemy(this);
            return ;
        }
    }
    //如果还在去目标航点的路上
    else
    {
        //采用QVectoer2D中的两点移动方法
        //获取目标航点
        QPoint targetPoint = myDestinationWayPoint->getPos();
        //定义移动速度
        double movementSpeed = myWalkingSpeed;
        QVector2D normailzed(targetPoint-myPos);
        normailzed.normalize();
        myPos=myPos + normailzed.toPoint() * movementSpeed;
    }
}

//敌人是否可以移动
void enemy::doActive()
{
    myActive = true;
}

bool enemy::getMyactive()
{
    return myActive;
}

//获取坐标
QPoint enemy::getPos()
{
    return myPos;
}

//攻击敌人的传奇
void enemy::getAttacked(legends *legend0)
{
    myAttackingLegendList.push_back(legend0);
}

//敌人被攻击
void enemy::getDamaged(int damage)
{
    //扣除血量
    myCurrentHp -= damage;
    //如果敌人没血，获取赏金并移除
    if(myCurrentHp <= 0)
    {
        myGame->awardMoney();
        getRemoved();
    }
    else
    {
        // 更新界面，确保血量正确显示
        myGame->update();
    }
}

//移除敌人的函数
void enemy::getRemoved()
{
    //判断
    if(myAttackingLegendList.empty())
    {
        return ;
    }
    else
    {
        foreach(legends *legend,myAttackingLegendList)
        {
            legend->targetKilled();
        }
        myGame->removeEnemy(this);
    }
}

//失去了敌人视野
void enemy::getLostSight(legends *legend0)
{
    myAttackingLegendList.push_back(legend0);
}

void enemy::reSetHp(int maxHp)
{
    myMaxHp = maxHp;
    myCurrentHp = maxHp;
}

