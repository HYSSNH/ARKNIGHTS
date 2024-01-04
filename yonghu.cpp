#include "yonghu.h"
#include "ui_yonghu.h"
#include "user.h"

yonghu::yonghu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yonghu)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
//    setWindowFlags(Qt::FramelessWindowHint | windowFlags());    //去窗口边框
//    setAttribute(Qt::WA_TranslucentBackground);  //把窗口背景设置为透明
    this->setGeometry(750,300,400,300);
    this->setFixedSize(400,300);

    this->setAutoFillBackground(true);

    btnA = new QPushButton(this);
    btnA->setText("登录");// 设置按钮的文本
    btnA->setGeometry(65, 200, 100, 50);   // 设置按钮的位置和大小
    btnA->setFlat(true);
    btnA->setStyleSheet("background-color: rgb(255,250,250);color: rgb(0,0,0);");
    btnA->show();

    btnB = new QPushButton(this);
    btnB->setText("注册");// 设置按钮的文本
    btnB->setGeometry(225, 200, 100, 50);   // 设置按钮的位置和大小
    btnB->setFlat(true);
    btnB->setStyleSheet("background-color: rgb(255,250,250);color: rgb(0,0,0);");
    btnB->show();

    tel_num = new QLabel(this);
    tel_num->setText("Tel_Num:");
    tel_num->setGeometry(50, 45, 68, 25);
    tel_num->setStyleSheet("QLabel{color: rgb(0,0,0);}");
    password = new QLabel(this);
    password->setText("PassWord:");
    password->setGeometry(50, 105, 68, 25);
    password->setStyleSheet("QLabel{color: rgb(0,0,0);}");

    tel_num_lineEdit = new QLineEdit(this);
    tel_num_lineEdit->setGeometry(160, 45, 170, 30);
    tel_num_lineEdit->setPlaceholderText("tel_num");
    QStringList tel_num_list;
        tel_num_list<<"12345"<<"12314"<<"24526"<<"2789665";//构建账号补全列表
    tel_number = new QCompleter(tel_num_list);
    tel_num_lineEdit->setCompleter(tel_number);

    password_lineEdit = new QLineEdit(this);
    password_lineEdit->setGeometry(160, 105, 170, 30);
    password_lineEdit->setPlaceholderText("password");
    password_lineEdit->setEchoMode(QLineEdit::Password);//设置密码的显示模式



    //注册
    connect(this->btnB,&QPushButton::clicked,[this](){
        if(this->tel_num_lineEdit->text().isEmpty() || this->password_lineEdit->text().isEmpty())
        {QMessageBox::critical(this,"警告","tel_num或password不能为空");
            return;}
        else{
            UserInfo user = {this->tel_num_lineEdit->text(),this->password_lineEdit->text()};
            User* call = new User();
            int ret = call->registerUser(user);
            switch (ret)
            {
            case 0:
                QMessageBox::information(this,"信息","注册成功！");
                break;
            case 1:
                QMessageBox::question(this,"信息","注册失败");
                break;
            }

        }
    });

    //登录
    //Lambda 表达式
    connect(this->btnA,&QPushButton::clicked,[this](){
        if(this->tel_num_lineEdit->text().isEmpty() || this->password_lineEdit->text().isEmpty())
        {
            QMessageBox::critical(this,"警告","tel_num或password不能为空");
            return;
        }
        else
        {
            UserInfo user = {this->tel_num_lineEdit->text(),this->password_lineEdit->text()};
            User* call = new User();

            int ret = call->judgeTel_numAndPassword(user);//验证tel_num和password

            switch (ret)
            {
            case 0:
            { QMessageBox::information(this,"信息","登录成功！");
                this->close();

                choose *w = new choose;
                w->show();

                break;}
            case 1:
                QMessageBox::question(this,"信息","登录失败");
                break;
            case 2:
                QMessageBox::critical(this,"信息","账号或密码错误");
                break;
            case 3:
                QMessageBox::critical(this,"信息","不能以tel_num或password来作为账号密码");
                break;
            }
        }
    });

}



yonghu::~yonghu()
{
    delete ui;
}
