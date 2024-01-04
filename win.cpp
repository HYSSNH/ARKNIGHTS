#include "win.h"
#include "ui_win.h"

win::win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::win)
{
    ui->setupUi(this);
    this->setWindowTitle("ARKNIGHTS");
    this->setFixedSize(1920,1182 );
    this->setWindowIcon(QIcon(":/ark1.ico"));
}

win::~win()
{
    delete ui;
}

void win::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString path=":/win.jpg";
    painter.drawPixmap(0,0,1920,1182,path);
}
void win::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton==event->button())
    {
        choose *a=new choose;
        this->hide();
        a->show();
    }
}
