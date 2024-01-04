#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>

#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include "choose.h"
#include "yonghu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
//    void paintEvent(QPaintEvent *event);


private:
    Ui::Widget *ui;
    choose *chooseScene=NULL;
};
#endif // WIDGET_H
