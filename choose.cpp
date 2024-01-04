#include "choose.h"
#include "ui_choose.h"

choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    this->setWindowTitle("ARKNIGHTS");
    //    固定窗口大小
    this->setFixedSize(1920,1080);
    //    设置开始按钮
    this->setWindowIcon(QIcon(":/ark2.ico"));

    //  开始第一关
    connect(ui->btn1,&QPushButton::clicked,[=](){
        gamescene *game = new gamescene;
        this->hide();
        game->setPath(":/0-1.png");
        game->addWayPoint1();
        game->addLegendLocation1();
        game->show();
    });

    //  开始第二关
    connect(ui->btn2,&QPushButton::clicked,[=](){
        gamescene *game = new gamescene;
        this->hide();
        game->setPath(":/0-2.png");
        game->addWayPoint2();
        game->addLegendLocation2();
        game->show();
    });
}

choose::~choose()
{
    delete ui;
}

void choose::paintEvent(QPaintEvent *)
{
    QPainter painter1(this);
    QPixmap pix1;
    pix1.load(":/login.png");
    //    编辑选关界面
    painter1.drawPixmap(0,0,this->width(),this->height(),pix1);
}
