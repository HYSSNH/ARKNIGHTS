#include "lose.h"
#include "ui_lose.h"

lose::lose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lose)
{
    ui->setupUi(this);
    this->setWindowTitle("ARKNIGHTS");
    //    设置窗口大小
    this->setFixedSize(1440,526);
    //     设置图标
    this->setWindowIcon(QIcon("://cal.ico.png"));
}

lose::~lose()
{
    delete ui;
}

void lose::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString path=":/lose.png";
    painter.drawPixmap(0,0,1440,526,path);
}

void lose::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton==event->button())
    {
        choose *a=new choose;
        this->hide();
        a->show();
    }
}
