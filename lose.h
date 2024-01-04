#ifndef LOSE_H
#define LOSE_H

#include <QWidget>

#include"gamescene.h"
#include"choose.h"

class Gamescene;
class choose;

namespace Ui {
class lose;
}

class lose : public QWidget
{
    Q_OBJECT

public:
    explicit lose(QWidget *parent = nullptr);
    ~lose();
    void paintEvent(QPaintEvent *event) ;
    void mousePressEvent(QMouseEvent *event) ;

private:
    Ui::lose *ui;
};

#endif // LOSE_H
