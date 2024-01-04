#include "selectbutton2.h"
#include "gamescene.h"
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QString>


static const int towerupdate1Cost=40;//塔第一次升级的价钱
static const int towerupdate2Cost=50;//第二次升级

selectButton2::selectButton2(QPoint pos,gamescene * game,int width,int height):
    myGame(game),
    myPos(pos),
    myWidth(width),
    myHeight(height)
{
}

selectButton2::~selectButton2()
{
    myGame = NULL;
    myLegend = NULL;
}

QPoint selectButton2::getPos()
{
    return myPos;
}

void selectButton2::getRemoved()
{
    myGame->removeButton2(this);
}


void selectButton2::setLegend(legends *legend)
{
    myLegend = legend;
}

void selectButton2::draw(QPainter *painter) const
{
    int level = myLegend->getLevel();
    painter->save();
    painter->setPen(Qt::red);
    if(level == 1)
    {
        painter->drawText(QRect(myPos.x(),myPos.y(),100,25),QString("update: %1").arg(towerupdate1Cost));
    }
    else
    {
        painter->drawText(QRect(myPos.x(),myPos.y(),100,25),QString("update: %1").arg(towerupdate2Cost));
    }
    painter->drawText(QRect(myPos.x(),myPos.y()+25,100,25),QString("remove"));
    painter->restore();
}

bool selectButton2::containPos(QPoint pos)
{
    bool xInHere = pos.x() > myPos.x() && pos.x() < myPos.x() + myWidth;
    bool yInHere = pos.y() > myPos.y() && pos.y() < myPos.y() + myHeight;
    return xInHere && yInHere;
}
