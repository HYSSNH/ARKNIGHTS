#ifndef USER_H
#define USER_H

#include <QString>
#include <QWidget>

typedef struct
{
    QString tel_num;
    QString password;
}UserInfo;

class User : public QWidget
{
    Q_OBJECT
public:
    explicit User(QWidget *parent = nullptr);

signals:

public slots:
    int judgeTel_numAndPassword(UserInfo user);
    int registerUser(UserInfo user);
};

#endif // USER_H
