#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    this->setWindowTitle("ARKNIGHTS");
//    this->setFixedSize(1320,1320);
//    this->setWindowIcon(QIcon(":/ark1.ico"));
    yonghu *yonghu1 = new yonghu;
    yonghu1->show();

}

Widget::~Widget()
{
    delete ui;
}

//void Widget::paintEvent(QPaintEvent *)
//{   QPainter painter0(this);
//    QPixmap pix0;
//    pix0.load(":/2226.png");
//    //    编辑开始界面
//    painter0.drawPixmap(0,0,this->width(),this->height(),pix0);
//}
