#ifndef MYBTN_H
#define MYBTN_H

#include <QWidget>
#include<QPushButton>
class mybtn : public QPushButton
{
    Q_OBJECT
public:
//    explicit mybtn(QPushButton *parent = nullptr);
    mybtn(QString enter, QString back = "");
    QString enter;
    QString back;



    //创建按钮的动作: 向上跳 (up), 向下跳(down)

    void uper();
    void down();
signals:

public slots:
};

#endif // MYBTN_H
