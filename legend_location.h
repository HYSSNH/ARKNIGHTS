#ifndef LEGEND_LOCATION_H
#define LEGEND_LOCATION_H

#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QSize>

#include "legends.h"
#include "selectbutton.h"
#include "selectbutton2.h"

class legends;
class selectButton;
class selectButton2;

class legend_location
{
public:
    legend_location(QPoint pos,const QPixmap & sprite =QPixmap(":/legend_location.png"));
    ~legend_location();

    QPoint centerPos()const ;
    QPoint getPos();
    int getWidth();
    int getHeight();

    void setLegend(legends * legend);//设置私有成员legend
    void setButton(selectButton * button);//设置私有成员button
    void setButton2(selectButton2 * button);//设置私有成员button2

    legends * getLegend();//得到私有成员tower
    selectButton * getButton();//得到私有成员button
    selectButton2 * getButton2();//得到私有盛有button2

    //对防御塔的判断
    void setHasLegend(bool hasLegend);
    bool hasLegend();

    void setHasLegend1(bool hasLegend1);
    bool hasLegend1();

    void setHasLegend2(bool hasLegend2);
    bool hasLegend2();

    void setHasLegend3(bool hasLegend3);
    bool hasLegend3();

    void setHasButton(bool hasButton);
    bool hasButton();

    void setHasButton2(bool hasButton);
    bool hasButton2();

    void setHasUpdate1(bool hasUpdate1);
    bool hasUpdate1();

    void setHasUpdate2(bool hasUpdate2);
    bool hasUpdate2();

    void setRemoveLegend();//移除Legend
    bool containPoint(const QPoint pos)const;

    void draw(QPainter * painter)const;

    bool myHasLegend;

private:
    bool myHasLegend1;
    bool myHasLegend2;
    bool myHasLegend3;

    bool myHasButton;
    bool myHasButton2;

    bool myHasUpdate1;
    bool myHasUpdtae2;

    legends * myLegend;
    selectButton * myButton;
    selectButton2 * myButton2;

    QPoint myPos;
    QPixmap mySprite;
    static const QSize myFixedSize;

};

#endif // LEGEND_LOCATION_H
