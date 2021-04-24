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
    Mainplaywin (int);
    void paintEvent(QPaintEvent *event);  //给游戏 主窗口背景
     int  detect(QVector<mycoin*>& buf);                          //检测 硬币 是否都 已经成 金币了,如果是 那么游戏结束
    QVector <int> coin (int j);         //关卡模板
    QVector<mycoin*> buf;  //维护16个 金币按钮 coinb
    QLabel *l = NULL;
     int v;                           //判断 是否 全部胜利 的 标志.

     //两个鼠标事件
     void mousePressEvent(QMouseEvent *event);


     QLabel* stapL =NULL; // 这个标签用来显示还可以使用的步数
     int stap; // 设置步数, 当步数为零时 不可翻金币 游戏结束

     // 当key[i] 为1 可以进行这一关 否则key[i] 为0 你必须完成i 关前面的关卡才可以 玩第i 关
     int key = 0;

     // 当flag = 0 说明胜利标签还没有下移, 当flag = 1 胜利标签已经下移完成 不需要再次下移了
    int flag = 0;

    // fail_fl  = 1 时 说明失败了 要进行 相应的操作
    int fail_fl = 0;

    int reflag = 0;
    // 重新开始flag

    int h;  //  记录初始的 关卡号
    int reidx; // 返回 目前关卡号
    void rebin(mybtn*);      //关于reb的进场
    void rebout(mybtn*);   // 关于reb的退场
signals:
     void backchange();  // 返回到 choosewin
     void winning();   //胜利
     void winnext();   // 点击next 按钮进入下一关
public slots:
};

#endif // MAINPLAYWIN_H
