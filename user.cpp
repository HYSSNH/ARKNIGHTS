#include "user.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QList>
#include <QRegularExpression>

QFile file("D:\\QTProject\\ARKNIGHTS\\user.txt");
//更改为user.txt的目录，格式仿照上面

User::User(QWidget *parent) : QWidget(parent)
{

}

/*
 * 0 账号密码正确
 * 1 账号或密码空
 * 2 账号或密码错误
 * 3 不能以tel_num或password来作为账号密码
*/
int User::judgeTel_numAndPassword(UserInfo user)
{
    if(user.tel_num.isEmpty() || user.password.isEmpty())  return 1;
    else
    {
        if(user.tel_num == "tel_num" || user.password=="password")    return 3;

        //读取文件数据存储处
        QList<UserInfo> storUser;

        //读取文件内容存储进入str
        char str[1024] = {0};

        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!file.atEnd())
            {
                file.read(str,sizeof str);
            }

            //debug检测一下是否有信息
            qDebug() << str << "\n";
            file.close();
        }

        //解析存储
        QString coun = (QString)str;// 将str转换为QString
        QString newstr = coun.simplified();//去除新行等空白符
        QStringList arr = newstr.split(QRegularExpression("(tel_num)|(password)|( )|(:)"));// 使用正则表达式split字符串为QStringList
        //for循环存储list对象
        for (int i = 0; i < arr.length(); ++i)
        {
            UserInfo uc;
            if (i < arr.size()) // 检查i变量是否小于arr对象的长度
            {
                uc.tel_num = arr[i];// 存储tel_num
                i = i+3;
                if (i < arr.size()) // 检查i变量是否小于arr对象的长度
                {
                    uc.password = arr[i];
                    storUser.append(uc);// 追加到QList
                }
            }
        }

        //判断tel_num和password是否一致
        for (int jg = 0; jg < storUser.length(); ++jg)
        {
            if(user.tel_num.compare(storUser.at(jg).tel_num) == 0 && user.password.compare(storUser.at(jg).password) == 0)
            {
                return 0;
            }
        }
        return 2;//
    }
}
/*
 * 0 注册成功
 * 1 账号或密码空
*/
int User::registerUser(UserInfo user)
{
    if(user.tel_num.isEmpty() || user.password.isEmpty())  return 1;
    else
    {
        QString n = "tel_num:"+user.tel_num;
        QString p = "password:"+user.password;

        QStringList arr;
        arr.append(n);
        arr.append(p);

        //QIODevice::WriteOnly文件不存在则会自动创建并且只写不读
        //QIODevice::Append有新数据则覆盖旧数据
        if(file.open(QIODevice::Append))
        {
            QTextStream in(&file);
            in << n << "\n"; //对文件的每一行写入用户名和密码
            in << p << "\n";

            //如果乱码
            //            file.write(n.toUtf8());
            //            file.write(p.toUtf8());
            file.close();
            return 0;//注册成功返回0
        }
        file.close();
        return 1;//注册失败返回1
    }
}
