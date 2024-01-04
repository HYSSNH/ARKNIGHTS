#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QIcon>
#include <QList>
#include <QString>
#include <QPainter>
#include <QSize>
#include <QTimer>
#include <QPixmap>
#include <QMouseEvent>

#include <choose.h>
#include <legends.h>
#include <legend_location.h>
#include <waypoint.h>
#include <enemy.h>
#include <bullet.h>
#include "lose.h"
#include "win.h"
#include "selectbutton.h"
#include "selectbutton2.h"

class legends;
class legend_location;
class enemy;
class bullet;


namespace Ui {
class gamescene;
}

class gamescene : public QWidget
{
    Q_OBJECT

public:
    explicit gamescene(QWidget *parent = nullptr);
    ~gamescene();
    //  添加航点
    void addWayPoint1();
    void addWayPoint2();
    //  添加传奇坐标
    void addLegendLocation1();
    void addLegendLocation2();

    //  可以购买
    bool canBuy1();
    bool canBuy2();
    bool canBuy3();
    //  可以升级
    bool canUpdate1();
    bool canUpdate2();
    //  基地扣血函数
    void getHpDamaged();
    //  敌人死亡，奖励金钱
    void awardMoney();
    //  画出当前基地血量的信息
    void drawHp(QPainter * painter)const;
    //  画出当前玩家金钱的信息
    void drawGlod(QPainter * painter)const;
    //  画出当前的波数信息
    void drawWaves(QPainter * painter)const;
    //  游戏结束
    void gameOver();
    //  游戏暂停
    void pause();
    //  移除敌人
    void removeEnemy(enemy * enemy);
    //  移除子弹
    void removeBullet(bullet * bullet);
    //  移除legend
    void removeLegend(legends*legend);
    //  移除button
    void removeButton(selectButton * button);
    void removeButton2(selectButton2 * button);
    //  添加子弹
    void addBullet(bullet * bullet);
    //  添加新的航点
    void setPath(QString path);
    //  加载敌人
    bool  loadWaves();
    //  是否点击
    bool hasPresspos(QPoint presspos, QPoint point, QSize size);
    //  得到图片路径
    QString getPath();
    //  得到图片高度
    int getHeight();
    //  得到敌人列表
    QList<enemy *> getMyEnemyList();
    //  得到子弹列表
    QList<bullet *> getMyBulletList();
    //  递归函数获取字符串便于打印
    QString getMoneyPath(QString path,int money);

protected:
    //  鼠标事件
    void mousePressEvent(QMouseEvent *event) ;
    //  绘图事件
    void paintEvent(QPaintEvent *event) ;

private slots:
    //  显示地图
    void upDateMap();
    //  游戏开始
    void gameStart();

private:
    Ui::gamescene *ui;
    //  地图路径
    QString myPath;
    //  新航点的列表
    QList<waypoint*>myNextWayPointList;
    //  legend坐标链表
    QList<legend_location> myLegendLoclist;
    //  legend类型列表
    QList< legends*> myLegendList;
    //  敌人列表
    QList<enemy *> myEnemyList;
    //  子弹列表
    QList<bullet *> myBulletList;
    //  选择按钮列表
    QList<selectButton *> mySelectButtonList;
    //  升级/移除列表
    QList<selectButton2 *> mySelectButton2List;
    //  我的金钱
    int myMoney;
    //  我的基地血量
    int myHomeHp;
    //  敌人波数
    int myWave;
    //  胜利
    bool myWin;
    //  失败
    bool myLose;
    QTimer *timer ;
    //控制暂停状态的变量
    int flag1 = 1;
};

#endif // GAMESCENE_H
