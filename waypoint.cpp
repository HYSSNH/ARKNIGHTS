#include "waypoint.h"

#include <QPoint>
#include <QPainter>

//   构造函数
waypoint::waypoint(QPoint pos)
{
    myPos = pos;
    myNextPoint = NULL;
}

//   设置下一个航点
void waypoint::setNextWayPoint(waypoint * nextWayPoint)
{
    this->myNextPoint = nextWayPoint;
}

//   下一个航点的指针
waypoint* waypoint::getNextWayPoint()
{
    return this->myNextPoint;
}

//返回值为const防止位置被修改
const QPoint waypoint::getPos()
{
    return this->myPos;
}

void waypoint::draw(QPainter * painter)
{
    painter->save();//保存原始的绘画参数
    painter->setPen(Qt::green);//设置画笔的颜色
    painter->drawEllipse(myPos,4,4);//画一个半径为4的圆
    painter->drawEllipse(myPos,1,1);//半径为1的圆
    painter->restore();//还原原来的画笔设置
}

