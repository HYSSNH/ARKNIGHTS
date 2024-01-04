#ifndef WIN_H
#define WIN_H

#include <QWidget>

#include"gamescene.h"
#include"choose.h"

class gamescene;
class choose;

namespace Ui {
class win;
}

class win : public QWidget
{
    Q_OBJECT

public:
    explicit win(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    ~win();

private:
    Ui::win *ui;
};

#endif // WIN_H
