#ifndef SELECTBUTTON2_H
#define SELECTBUTTON2_H

#include <QPainter>
#include <QRect>
#include <QPoint>

#include "gamescene.h"
#include "legends.h"

class gamescene;
class legends;

class selectButton2:QObject
{
    Q_OBJECT
private:
    gamescene * myGame;
    legends * myLegend;
    QPoint myPos;
    int myWidth;
    int myHeight;
public:
    selectButton2(QPoint pos,gamescene* game,int width,int height);
    ~selectButton2();
    void draw(QPainter * painter)const;
    void getRemoved();
    legends * getLegend();
    void setLegend(legends *legend);
    bool containPos(QPoint pos);
    QPoint getPos();
};
#endif // SELECTBUTTON2_H
