#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>


class waypoint
{
public:
    waypoint();
    waypoint(QPoint pos);
    //    设置下一个航点
    void setNextWayPoint(waypoint * nextWayPoint);
    //    下一个航点的指针,返回值为指针
    waypoint * getNextWayPoint();
    //    本航点的位置
    const QPoint getPos();
    //    画出本航点
    void draw(QPainter * painter) ;

private:
    //    航点的位置
    QPoint myPos;
    //    下一个航点指针
    waypoint *myNextPoint;

};

#endif // WAYPOINT_H
