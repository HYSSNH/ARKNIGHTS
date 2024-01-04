#include "legend_location.h"
#include"selectbutton.h"
#include <QSize>
#include <QPainter>
#include <QPixmap>

//设置图片的大小
const QSize legend_location::myFixedSize(120,120);

//初始化列表
legend_location::legend_location(QPoint pos,const QPixmap & sprite):
    myHasLegend(false),
    myHasLegend1(false),
    myHasLegend2(false),
    myHasLegend3(false),
    myHasButton(false),
    myHasButton2(false),
    myPos(pos),
    mySprite(sprite)
{

}

legend_location::~legend_location()
{

}

void legend_location::setHasLegend(bool hasLegend)
{
    myHasLegend = hasLegend;
}

bool legend_location::hasLegend()
{
    return myHasLegend;
}

void legend_location::setHasLegend1(bool hasLegend1)
{
    this->myHasLegend1 = hasLegend1;
    setHasLegend(hasLegend1);
}

bool legend_location::hasLegend1()
{
    return myHasLegend1;
}

void legend_location::setHasLegend2(bool hasLegend2)
{
    this->myHasLegend2 = hasLegend2;
    setHasLegend(hasLegend2);
}

bool legend_location::hasLegend2()
{
    return myHasLegend2;
}

void legend_location::setHasLegend3(bool hasLegend3)
{
    myHasLegend3 = hasLegend3;
    setHasLegend(hasLegend3);
}

bool legend_location::hasLegend3()
{
    return myHasLegend3;
}

void legend_location::setHasButton(bool hasButton)
{
    myHasButton = hasButton;
}

bool legend_location::hasButton()
{
    return myHasButton;
}

void legend_location::setHasButton2(bool hasButton2)
{
    myHasButton2 = hasButton2;
}

bool legend_location::hasButton2()
{
    return myHasButton2;
}

void legend_location::setHasUpdate1(bool hasUpdate1)
{
    myHasUpdate1 = hasUpdate1;
}

bool legend_location::hasUpdate1()
{
    return myHasUpdate1;
}

void legend_location::setHasUpdate2(bool hasUpdate2)
{
    myHasUpdtae2 = hasUpdate2;
}

bool legend_location::hasUpdate2()
{
    return myHasUpdtae2;
}

QPoint legend_location::centerPos() const
{
    QPoint tmp;
    tmp.setX(myPos.x() + myFixedSize.width()/2);
    tmp.setY(myPos.y() + myFixedSize.height()/2);
    return tmp;
}

bool legend_location::containPoint(const QPoint pos) const
{
    bool xInHere=(pos.x() > myPos.x()) && (pos.x() < myPos.x() + myFixedSize.width());
    bool yInHere=(pos.y() > myPos.y()) && (pos.y() < myPos.y() + myFixedSize.height());
    return xInHere && yInHere;
}

void legend_location::draw(QPainter *painter) const
{
    painter->drawPixmap(myPos.x(),myPos.y(),mySprite);
}

QPoint legend_location::getPos()
{
    return this->myPos;
}

void legend_location::setLegend(legends * legend)
{
    myLegend = legend;
}

void legend_location::setButton(selectButton *button)
{
    myButton = button;
}

void legend_location::setButton2(selectButton2 *button)
{
    myButton2 = button;
}

legends * legend_location::getLegend()
{
    return myLegend;
}

selectButton2 * legend_location::getButton2()
{
    return myButton2;
}

void legend_location::setRemoveLegend()
{
    setLegend(NULL);
    setHasLegend(false);
    setHasLegend1(false);
    setHasLegend2(false);
    setHasLegend3(false);
    setHasUpdate1(false);
    setHasUpdate2(false);
}

selectButton * legend_location::getButton()
{
    return myButton;
}

int legend_location::getWidth()
{
    return myFixedSize.width();
}

int legend_location::getHeight()
{
    return myFixedSize.height();
}
