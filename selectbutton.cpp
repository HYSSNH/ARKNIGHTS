#include "selectbutton.h"

selectButton::selectButton(QPoint pos,gamescene * game,int width,int height):
    myGame(game),
    myPos(pos),
    myWidth(width),
    myHeight(height)
{
    mySelectBoxImagePath[0]=":/teaxs_legend1.png";
    mySelectBoxImagePath[1]=":/o_teaxs_legend2.png";
    mySelectBoxImagePath[2]=":/mostima_legend3.png";
}

selectButton::~selectButton()
{
    myGame = NULL;
}

void selectButton::draw(QPainter *painter) const
{
        painter->save();
        painter->drawPixmap(myPos.x(),myPos.y(),mySelectBoxImagePath[0]);
        painter->drawPixmap(myPos.x() + 35,myPos.y(),mySelectBoxImagePath[1]);
        painter->drawPixmap(myPos.x() + 70,myPos.y(),mySelectBoxImagePath[2]);
        painter->restore();
}

void selectButton::getRemoved()
{
    myGame->removeButton(this);
}

bool selectButton::containPos(QPoint pos)
{
    bool xInHere = pos.x() > myPos.x() && pos.x() < myPos.x() + myWidth;
    bool yInHere = pos.y() > myPos.y() && pos.y() < myPos.y() + myHeight;
    return xInHere&&yInHere;
}

QPoint selectButton::getPos()
{
    return myPos;
}

