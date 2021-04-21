#ifndef MAINPLAYWIN_H
#define MAINPLAYWIN_H

#include <QMainWindow>
#include<QVector>
#include<QLabel>
#include"mycoin.h"
#include"mybtn.h"
#include<QSound>
class Mainplaywin : public QMainWindow
{
    Q_OBJECT
public:
//    explicit Mainplaywin(QWidget *parent = nullptr);
    Mainplaywin (int i = -1);
    void paintEvent(QPaintEvent *event);  //给游戏 主窗口背景
     int  detect(QVector<mycoin*>& buf);                          //检测 硬币 是否都 已经成 金币了,如果是 那么游戏结束
    QVector <int> coin (int j);         //关卡模板
    QVector<mycoin*> buf;  //维护16个 金币按钮 coinb
    QLabel *l = NULL;
     int v;                           //判断 是否 全部胜利 的 标志.

     //两个鼠标事件
     void mousePressEvent(QMouseEvent *event);
     void mouseDoubleClickEvent(QMouseEvent *event);

     // 当key[i] 为1 可以进行这一关 否则key[i] 为0 你必须完成i 关前面的关卡才可以 玩第i 关
     int key = 0;


signals:
     void backchange();
     void winning();
public slots:
};

#endif // MAINPLAYWIN_H
