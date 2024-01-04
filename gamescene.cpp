#include "gamescene.h"
#include "ui_gamescene.h"

#include <QDebug>
#include <QString>

/*static const int tower1Cost=300;//第一种塔的价钱
static const int tower2Cost=400;//第二种
static const int tower3Cost=500;//第三种
static const int towerupdate1Cost=300;//塔第一次升级的价钱
static const int towerupdate2Cost=400;//第二次升级*/

gamescene::gamescene(QWidget *parent) :
    QWidget(parent),ui(new Ui::gamescene),
    myMoney(1000),myHomeHp(3),myWave(0),myWin(false),myLose(false)
{
    ui->setupUi(this);
    this->setWindowTitle("ARKNIGHTS");
    this->setFixedSize(1280,720);
    this->setWindowIcon(QIcon(":/ark3.ico"));
    //    创建定时器
    timer = new QTimer(this);
    //每30毫秒刷新地图
    connect(timer,SIGNAL(timeout()),this,SLOT(upDateMap()));
    timer->start(30);
    //静态函数，300毫秒后开始游戏
    QTimer::singleShot(300,this,SLOT(gameStart()));
}

gamescene::~gamescene()
{
    delete ui;
}

void gamescene::setPath(const QString path)
{
    myPath = path;
}

QString gamescene::getPath()
{
    return myPath;
}

int gamescene::getHeight()
{
    // 返回游戏场景的高度，试用600
    return 600;
}

//判定是否可以购买
bool gamescene::canBuy1()
{
    if(myMoney >= 30)
    {
        return true;
    }
    return false;
}
bool gamescene::canBuy2()
{
    if(myMoney >= 40)
    {
        return true;
    }
    return false;
}
bool gamescene::canBuy3()
{
    if(myMoney >= 50)
    {
        return true;
    }
    return false;
}
bool gamescene::canUpdate1()
{
    if(myMoney >= 40)
    {
        return true;
    }
    return false;
}
bool gamescene::canUpdate2()
{
    if(myMoney >= 50)
    {
        return true;
    }
    return false;
}

//移除legend
void gamescene::removeLegend(legends *legend)
{
    Q_ASSERT(legend);
    myLegendList.removeOne(legend);
    delete legend;
}

//移除button
void gamescene::removeButton(selectButton *button)
{
    Q_ASSERT(button);
    mySelectButtonList.removeOne(button);
    delete button;
}

//移除button2
void gamescene::removeButton2(selectButton2 *button)
{
    Q_ASSERT(button);
    mySelectButton2List.removeOne(button);
    delete button;
}

//绘图事件
void gamescene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(myPath);
    painter.drawPixmap(0,0,this->width(),this->height(),getPath());

    //  画出legend预设位
    foreach(const legend_location & legendLoc,myLegendLoclist)
    {
        if(!legendLoc.myHasLegend)
        {
            legendLoc.draw(&painter);//把hasLegend改成了公有成员，这样可以再类外使用，实现了有防御塔时防御塔坑的隐藏
        }
    }
    //  画出legend
    foreach(const legends *legend0,myLegendList)
    {
        legend0->draw(&painter);
    }
    //  画出航点
    foreach( waypoint * waypoint0,myNextWayPointList)
    {
        waypoint0->draw(&painter);
    }
    //    画出敌人
    foreach(const enemy * enemy0,myEnemyList)
    {
        enemy0->draw(&painter);
    }
    //画出子弹
    foreach(const bullet * bullet0,myBulletList)
    {
        bullet0->draw(&painter);
    }
    foreach(const selectButton * button,mySelectButtonList)
    {
        button->draw(&painter);
    }
    foreach(const selectButton2 * button2,mySelectButton2List)
    {
        button2->draw(&painter);
    }

    //画出金钱数量
    QColor color (255,255,255);
    QFont font1("宋体",45,QFont::Bold);
    painter.setPen(color);
    painter.setFont(font1);
    QString moneyPath;  //存储金钱的信息。
    moneyPath = getMoneyPath(moneyPath,myMoney);
    std::reverse(moneyPath.begin(),moneyPath.end());    //把金钱字符串反转过来，以便从右往左显示
    painter.drawText(150,82,moneyPath);
    //画出波数
    QString wavePath = "0";  //存储波数的信息。
    wavePath += '0' + myWave + 1;
    wavePath += "/03波怪物";
    painter.drawText(430,82,wavePath);
    //画出生命
    QFont font2("宋体",42,QFont::Bold);
    painter.setFont(font2);
    QString lifePath;  //存储生命的信息
    lifePath = getMoneyPath(lifePath,myHomeHp);
    std::reverse(lifePath.begin(),lifePath.end());      //把生命字符串反转过来，以便从右往左显示
    painter.drawText(930,82,lifePath);

    //画出暂停
    QString pausePath=":/Pause (2).png";
    if(flag1 == 1)
        painter.drawPixmap(1020,0,100,100,pausePath);
}

void gamescene::mousePressEvent(QMouseEvent *event)
{
    //  获取点击的坐标
    QPoint pressPos = event->pos();


    //  创建legend列表
    auto it = myLegendLoclist.begin();
    //  遍历所有legend格子
    while(it != myLegendLoclist.end())
    {
        //如果是鼠标左键点击，可以实现传奇的建立，或者是在有button2时进行升级或者移除
        if(Qt::LeftButton == event->button())//如果是鼠标左键点击
        {
            //左键点击的情况下，可以实现防御塔选择button的出现和legend的选择,或者是在有button2的情况下，进行升级或移除的操作
            //在没有按钮的情况下点击，会出现button1
            if(it->containPoint(pressPos) && !it->hasButton() && !it->hasLegend() && !it->hasButton2())
            {
                //向左上角移动35 35，得到选择框的端点
                QPoint tmp(it->getPos().x() - 35,it->getPos().y() - 35);
                //构造一个选择框
                selectButton * button=new selectButton(tmp,this);
                //legend的放置，把这个button放到gamescene的一个list中
                mySelectButtonList.push_back(button);
                //设置这个legend坑处的button
                it->setButton(button);
                //这个坑有了button
                it->setHasButton(true);
                //更新gamescene，主要是更新paintevent
                update();
                break;
            }
            //下面的判断语句，要先判断hasbutton2，不能先判断containPos.因为如果没有button2，在进入这个判断框的时候，会先getbutton2，但是button2是NULL，程序会异常结束。
            else if(it->hasButton2() && it->getButton2()->containPos(pressPos) && !it->hasButton() && !it->containPoint(pressPos) && it->hasLegend())
            {
                //在有button2的情况下，点击button2的内部

                //设置第一个选择框的height是25
                if(pressPos.y() < (it->getButton2()->getPos().y() + 25) )
                {
                    //对legend进行升级
                    if(canUpdate1() && !it->hasUpdate1() && it->hasLegend())
                    {
                        it->setHasUpdate1(true);
                        myMoney -= 40;
                        it->getLegend()->reSetDamage(it->getLegend()->getDamgae() + 10);
                        it->getLegend()->levelChange();
                        //                        update();
                        //                        break;
                    }
                    else if(canUpdate2() && it->hasUpdate1() && !it->hasUpdate2())
                    {
                        it->setHasUpdate2(true);
                        myMoney -= 50;
                        it->getLegend()->reSetDamage(it->getLegend()->getDamgae() + 20);
                        it->getLegend()->levelChange();
                        //                        update();
                        //                        break;
                    }
                }
                else if(pressPos.y() > it->getButton2()->getPos().y() )
                {
                    //对防御塔进行移除

                    //移除防御塔奖励200
                    awardMoney();
                    it->getLegend()->getRemoved();
                    it->setRemoveLegend();
                    //                    update();
                    //                    break;
                }
                //点击了button2的内部，button2就要被移除
                it->getButton2()->getRemoved();
                it->setButton2(NULL);
                it->setHasButton2(false);
                update();
                break;
            }
            //在有button的情况下，选择三种legend
            else if(it->hasButton() && !it->hasLegend() && it->getButton()->containPos(pressPos))
            {
                //鼠标点在选择框中的第一个legend内
                if(pressPos.x() < it->getButton()->getPos().x() + 35)
                {
                    if(canBuy1())
                    {
                        it->setHasLegend1(true);
                        myMoney -= 30;
                        QString path = ":/teaxs_legend1.png";
                        //四个参数，分别是legend的中心点；主界面；legend图片路径；legend的攻击力。
                        legends * tower = new legends(it->centerPos(),this,path,10);
                        it->setLegend(tower);
                        myLegendList.push_back(tower);
                        update();
                        //                        break;
                    }
                }
                //鼠标点在第二个legend的图片中
                else if(pressPos.x() > it->getButton()->getPos().x() + 35 && pressPos.x() < it->getButton()->getPos().x() + 70)
                {
                    if(canBuy2())
                    {
                        it->setHasLegend2(true);
                        myMoney -= 40;
                        QString path = ":/o_teaxs_legend2.png";
                        legends * tower = new legends(it->centerPos(),this,path,15);
                        it->setLegend(tower);
                        myLegendList.push_back(tower);
                        update();
                        //break;
                    }
                }
                //第三个图片
                else if(pressPos.x() > it->getButton()->getPos().x() + 70 && pressPos.x() < it->getButton()->getPos().x() + 105)
                {
                    if(canBuy3())
                    {
                        it->setHasLegend3(true);
                        myMoney -= 50;
                        QString path = ":/mostima_legend3.png";
                        legends * legend = new legends(it->centerPos(),this,path,20);
                        it->setLegend(legend);
                        myLegendList.push_back(legend);
                        update();
                        //break;
                    }
                }
                //不能跳出循环是因为要执行下面的代码
                //下面的代码是对button的一个删除
                it->getButton()->getRemoved();
                it->setButton(NULL);
                it->setHasButton(false);
                update();
                break;
            }
        }
        //如果是鼠标右键点击
        else if(Qt::RightButton==event->button())
        {
            //在有防御塔的情况下，右键会出现选择框，升级还有移除
            if(it->containPoint(pressPos) && (!it->hasButton2()) && it->hasLegend())
            {
                it->setHasButton2(true);
                //把防御塔坑的右上顶点当作button2的端点
                QPoint tmp(it->getPos().x() + 35,it->getPos().y());
                selectButton2 * button2 = new selectButton2(tmp,this,100,100);
                //得到防御塔的等级，不同等级的cost不一样
                button2->setLegend(it->getLegend());
                mySelectButton2List.push_back(button2);
                it->setButton2(button2);
                update();
                break;
            }
        }
        ++it;
    }

    //如果点击暂停
    if(hasPresspos(pressPos,QPoint(1020,0),QSize(100,100)) && Qt::LeftButton == event->button())
    {   if(flag1 / 2 == 0)
        {
            flag1++;
            pause();
            qDebug() <<flag1<<endl;
        }
        else {
            timer->start(30);
            flag1--;
        }
    }


}

//判断用户点击的位置是否在指定的区域内
bool gamescene::hasPresspos(QPoint presspos, QPoint point, QSize size)
{
    //获取指定区域的右下角坐标
    QPoint bottomRight = point + QPoint(size.width(), size.height());
    //判断用户点击的位置是否在指定区域的水平范围内
    bool inHorizontal = presspos.x() >= point.x() && presspos.x() <= bottomRight.x();
    //判断用户点击的位置是否在指定区域的垂直范围内
    bool inVertical = presspos.y() >= point.y() && presspos.y() <= bottomRight.y();
    //返回用户点击的位置是否在指定区域内
    return inHorizontal && inVertical;
}

//   设置怪物移动的航点
void gamescene::addWayPoint1()
{
    waypoint *waypoint1 = new waypoint(QPoint(1127,376));
    myNextWayPointList.push_back(waypoint1);

    waypoint *waypoint2 = new waypoint(QPoint(992,363));
    waypoint1->setNextWayPoint(waypoint2);
    myNextWayPointList.push_back(waypoint2);

    waypoint *waypoint3 = new waypoint(QPoint(742,361));
    waypoint2->setNextWayPoint(waypoint3);
    myNextWayPointList.push_back(waypoint3);

    waypoint *waypoint4 = new waypoint(QPoint(742,282));
    waypoint3->setNextWayPoint(waypoint4);
    myNextWayPointList.push_back(waypoint4);

    waypoint *waypoint5 = new waypoint(QPoint(514,268));
    waypoint4->setNextWayPoint(waypoint5);
    myNextWayPointList.push_back(waypoint5);

    waypoint *waypoint6 = new waypoint(QPoint(510,368));
    waypoint5->setNextWayPoint(waypoint6);
    myNextWayPointList.push_back(waypoint6);

    waypoint *waypoint7 = new waypoint(QPoint(330,368));
    waypoint6->setNextWayPoint(waypoint7);
    myNextWayPointList.push_back(waypoint7);

    waypoint *waypoint8 = new waypoint(QPoint(281,253));
    waypoint7->setNextWayPoint(waypoint8);
    myNextWayPointList.push_back(waypoint8);
}

//   设置怪物移动的航点
void gamescene::addWayPoint2()
{
    waypoint *waypoint1 = new waypoint(QPoint(1130,370));
    myNextWayPointList.push_back(waypoint1);

    waypoint *waypoint2 = new waypoint(QPoint(920,370));
    waypoint1->setNextWayPoint(waypoint2);
    myNextWayPointList.push_back(waypoint2);

    waypoint *waypoint3 = new waypoint(QPoint(600,370));
    waypoint2->setNextWayPoint(waypoint3);
    myNextWayPointList.push_back(waypoint3);

    waypoint *waypoint4 = new waypoint(QPoint(600,285));
    waypoint3->setNextWayPoint(waypoint4);
    myNextWayPointList.push_back(waypoint4);

    waypoint *waypoint5 = new waypoint(QPoint(370,285));
    waypoint4->setNextWayPoint(waypoint5);
    myNextWayPointList.push_back(waypoint5);

    waypoint *waypoint6 = new waypoint(QPoint(350,370));
    waypoint5->setNextWayPoint(waypoint6);
    myNextWayPointList.push_back(waypoint6);

    waypoint *waypoint7 = new waypoint(QPoint(240,370));
    waypoint6->setNextWayPoint(waypoint7);
    myNextWayPointList.push_back(waypoint7);

    waypoint *waypoint8 = new waypoint(QPoint(145,370));
    waypoint7->setNextWayPoint(waypoint8);
    myNextWayPointList.push_back(waypoint8);

    //第二个出怪点
    waypoint *waypoint9 = new waypoint(QPoint(1130,250));
    myNextWayPointList.push_back(waypoint9);

    waypoint *waypoint10 = new waypoint(QPoint(920,250));
    waypoint9->setNextWayPoint(waypoint10);
    myNextWayPointList.push_back(waypoint10);

    waypoint *waypoint11 = new waypoint(QPoint(920,370));
    waypoint10->setNextWayPoint(waypoint11);
    myNextWayPointList.push_back(waypoint11);

    waypoint11->setNextWayPoint(waypoint2);

}

void gamescene::addLegendLocation1()
{
    //  设置传奇位置，用一维数组实现
    QPoint legendLoc[] =
    {
        QPoint(380,230),QPoint(590,325), QPoint(350,420),
        QPoint(830,425),QPoint(935,425),QPoint(695,155)
    };
    //用循环创建传奇列表
    int len = sizeof(legendLoc) / sizeof(legendLoc[0]);
    for(int i = 0; i < len ; i++)
    {
        myLegendLoclist.push_back(legendLoc[i]);
    }
}

void gamescene::addLegendLocation2()
{
    //  设置传奇位置，用一维数组实现
    QPoint legendLoc[] =
    {
        QPoint(360,170),QPoint(585,440), QPoint(320,440),
        QPoint(815,440),QPoint(920,440),QPoint(670,160)
    };
    //用循环创建传奇列表
    int len = sizeof(legendLoc) / sizeof(legendLoc[0]);
    for(int i = 0; i < len ; i++)
    {
        myLegendLoclist.push_back(legendLoc[i]);
    }
}

//基地扣血函数
void gamescene::getHpDamaged()
{
    //敌人进入基地，扣一滴血
    myHomeHp -= 1;
    if(myHomeHp <= 0)
    {
        //        gameOver();
        timer->stop();
        lose *b=new lose;
        b->show();
        this->hide();

    }
}

//   游戏暂停
void gamescene::pause()
{
    upDateMap();
    timer->stop();
}

//游戏失败
void gamescene::gameOver()
{
    if(!myLose)
    {
        myLose = true;
    }
}

//击杀敌人获取奖金
void gamescene::awardMoney()
{
    //杀死一个敌人，奖励200
    myMoney += 200;
}


//从敌人列表中移除敌人
void gamescene::removeEnemy(enemy *enemy)
{
    // 如果 enemy 不存在，输出调试信息并退出函数
    if (!enemy)
    {
        qDebug() << "Error: null enemy pointer!";
        return;
    }
    // 如果敌人血量为0，将其从敌人列表中移除
    if (enemy->getCurrentHp() <= 0) {
        myEnemyList.removeOne(enemy);
        delete enemy;
        // 如果本波敌人全部消灭
        if (myEnemyList.empty()) {
            ++myWave; // 新增下一波
            if (!loadWaves()) { // 如果所有波数都清零
                myWin = true;
                timer->stop();
                win *a=new win;
                a->show();
                this->hide();

            }
        }
    }
    else if(!enemy->getMyactive())
    {
        myEnemyList.removeOne(enemy);
        delete enemy;
        // 如果本波敌人全部消灭
        if (myEnemyList.empty())
        {
            ++myWave; // 新增下一波
            if (!loadWaves())
            {
                // 如果所有波数都清零
                myWin = true;
            }
        }
    }
}


void gamescene::addBullet(bullet *bullet)//创建新的子弹
{
    qDebug() <<"add bullet";
    Q_ASSERT(bullet);//检查是否有这个子弹，避免错误
    myBulletList.push_back(bullet);
}

//移除子弹
void gamescene::removeBullet(bullet *bullet)
{
    qDebug() <<"remove bullet";
    Q_ASSERT(bullet);//检查是否有这个子弹，避免错误
    myBulletList.removeOne(bullet);
}

//获取敌人列表
QList<enemy *> gamescene::getMyEnemyList()
{
    return myEnemyList;
}

//获取子弹列表
QList<bullet *> gamescene::getMyBulletList()
{
    return myBulletList;
}

//控制敌人一波波出现
bool gamescene::loadWaves()
{
    //    如果大于3波游戏结束
    if(myWave >= 3)
    {
        myWave--;
        return false;
    }
    int enemyStartTime[] = {500,1500,2500};//敌人出现的时间
    for(int i = 0 ; i < 2 ; i++)
    {
        //        创建开始航点
        waypoint * startWayPoint;
        if(getPath() == ":/0-2.png")
        {
            int a = rand()%100;
            if(a<50)
            {
                //        起点为航点列表的第一个
                startWayPoint = myNextWayPointList.first();
            }
            if(a>=50)
            {
                //        起点为航点列表的第9个
                startWayPoint = myNextWayPointList[8];
            }
        }
        else
        {
            startWayPoint = myNextWayPointList.first();
        }
        //        创建新的敌人
        enemy *enemy1 = new enemy(startWayPoint,this);
        //        将敌人放入列表
        myEnemyList.push_back(enemy1);
        enemy1->reSetHp(40+20*(0+myWave));//波数增加，怪物的血量增加，一次加20点
        //        静态函数，在每一波开始时调用一次
        QTimer::singleShot(enemyStartTime[i],enemy1,SLOT(doActive()));
    }
    return true;
}


//   游戏开始
void gamescene::gameStart()
{
    loadWaves();//    开始加载怪物波数

}

//    通过刷新屏幕使敌人移动
void gamescene::upDateMap()
{

    foreach (enemy *enemy, myEnemyList)
    {
        enemy->move();
        if(enemy->getCurrentHp() <= 0)
        {
            removeEnemy(enemy);
        }
    }
    foreach (legends *legend, myLegendList)
    {
        legend->checkEnemyInRange();
    }
    update();
}

//递归函数获取字符串便于打印
QString gamescene:: getMoneyPath(QString path,int money)
{
    if(money/10 != 0)
    {
        path+='0'+(money%10);
        return getMoneyPath(path,money/10);
    }
    return (path+='0'+money);
}
