#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class mycoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit mycoin(QWidget *parent = nullptr);
    mycoin (QString s);
    QString s; // 硬币 的背景 图片 文件路径
    int flag; // 硬币 的 状态


    void change (int flag);  //实现 硬币 反转功能

     QTimer * time1;
     QTimer* time2;
     // 用来检索金币的图标文件
     int index = 2;
     int index_ = 7;

     //禁止 鼠标 双击事件
     void mouseDoubleClickEvent(QMouseEvent *event);
signals:

public slots:
};

#endif // MYCOIN_H
