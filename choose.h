#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>
#include<QIcon>
#include<QPainter>
#include<QPixmap>
#include<QPushButton>
#include<QEvent>

#include<gamescene.h>

namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();
    void paintEvent(QPaintEvent *);


private:
    Ui::choose *ui;
};

#endif // CHOOSE_H
