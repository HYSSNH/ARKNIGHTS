#ifndef YONGHU_H
#define YONGHU_H


#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QtSql/QSqlTableModel>
#include <QCompleter>

#include <choose.h>
#include <QPaintEvent>

//#include <QIcon>
//#include <QPixmap>
//#include <QPainter>




namespace Ui {
class yonghu;
}

class yonghu : public QWidget
{
    Q_OBJECT

public:
    explicit yonghu(QWidget *parent = nullptr);
    void initwidget();   //初始化功能函数
    void clearall();  //清空LineEdit功能函数
    ~yonghu();

private:
    Ui::yonghu *ui;
    QFrame *f_login;
    QPushButton *btnA;
    QPushButton *btnB;
    QLabel *tel_num;
    QLabel *password;
    QLineEdit *tel_num_lineEdit;
    QLineEdit *password_lineEdit;
    QCompleter *tel_number;
};

#endif // YONGHU_H
