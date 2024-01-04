#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QObject>

#include "gamescene.h"

class gamescene;

class selectButton :QObject
{
    Q_OBJECT
private:
    gamescene * myGame;
    QPoint myPos;
    int myWidth;
    int myHeight;
    QString mySelectBoxImagePath[3];
public:
    selectButton(QPoint pos,gamescene * game,int width = 90,int height = 90);
    ~selectButton();
    void draw(QPainter * painter)const;
    //  选择框被点了一次，就要移除
    void getRemoved();
    //  判断这次的点击是否在选择框内
    bool containPos(QPoint pos);
    QPoint getPos();
};

#endif // SELECTBUTTON_H
