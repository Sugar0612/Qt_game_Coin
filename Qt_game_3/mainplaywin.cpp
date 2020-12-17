#include "mainplaywin.h"
#include <QPainter>
#include <QPixmap>
#include "mybtn.h"
#include<QLabel>
#include<QFont>
#include <QVector>

Mainplaywin::Mainplaywin (int i) {      //重写了 构造函数
            this ->setFixedSize(400, 650);


             //建立 窗口的 图标
            this -> setWindowIcon(QIcon(":/coinfiles/Coin0001.png"));

            //设置 窗口的 标题
            this ->setWindowTitle("coinGames");

            //设置 back按钮 在游戏窗口
            mybtn * back = new  mybtn(":/coinfiles/BackButton.png", ":/coinfiles/BackButtonSelected.png");
            back ->move(325, 620);
            back ->setParent(this);


            //点击 back  触发(返回到 选择关卡窗口) 的信号
            connect(back, &mybtn::clicked, [=] () {
                emit backchange();
            });

            if (-1 != i) {
                QFont font;                                                  //设置Leven 的字体
                font.setFamily("华文新魏");
                font.setPointSize(20);

                QLabel * l = new QLabel(QString("Lev %1").arg(i + 1), this);  //设置 游戏 关卡里面 的表示第几关的标签
                l -> setFont(font);
                l ->move(0, 610);
            }


             //设置硬币的背景
            for (int i = 0; i < 16; ++i) {
                int x = (i % 4 * 50) + 100;
                int y = (i / 4 * 50) + 230;
                mybtn * lb = new mybtn(":/coinfiles/BoardNode.png");
                lb ->setParent(this);
                lb ->move(x, y);
            }
}



void  Mainplaywin ::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QPixmap pix;
    pix.load(":/coinfiles/OtherSceneBg.png");
    p.drawPixmap(0,0,this->width(), this ->height(), pix);
}

QVector <int> con (int i, QVector<QVector<int>>& count) {
    QVector<int> buf1;
    buf1 = {
        1,1,1,1,
        1,1,0,1,
        1,0,0,0,
        1,1,0,1
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
       1, 0, 1, 1,
       0, 0, 1, 1,
       1, 1, 0, 0,
       1, 1, 0, 1
    };
      count.push_back(buf1);
      buf1.clear();

     buf1 = {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    };
    count.push_back(buf1);
    buf1.clear();

    buf1 = {
        0, 1, 1, 1,
        1, 0, 0,1,
        1, 0, 1, 1,
        1, 1, 1,  1
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
       1, 0, 0, 1,
       0, 0, 0, 0,
       0, 0, 0, 0,
       1, 0,  0, 1
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
        1, 0, 0, 1,
        0, 1, 1, 0,
        0, 1, 1, 0,
         1, 0, 0, 1
    };
    count.push_back(buf1);
    buf1.clear();

    buf1 = {
        0, 1, 1, 1,
         1, 0, 1, 1,
         1, 1, 0, 1,
         1, 1, 1, 0
    };
    count.push_back(buf1);
    buf1.clear();

    buf1 = {
        0, 1, 0, 1,
        1, 0, 0, 0,
         0, 0, 0, 1,
         1, 0, 1, 0
    };
   count.push_back(buf1);
   buf1.clear();

     buf1= {
        1, 0, 1, 0,
        1, 0, 1, 0,
        0, 0, 1, 0,
        1, 0, 0, 1
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
        1, 0, 1, 1,
        1, 1, 0, 0,
        0, 0, 1, 1,
        1, 1, 0, 1
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
         0, 1, 1, 0,
        1, 0, 0, 1,
        1, 0, 0, 1,
        0, 1, 1, 0
    };

    buf1 = {
        0, 1, 1, 0,
        0, 0, 0, 0,
         1, 1, 1, 1,
        0, 0, 0, 0
    };
count.push_back(buf1);
buf1.clear();

     buf1 = {
        0, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
         0, 1, 1, 0
    };
    count.push_back(buf1);
    buf1.clear();


    buf1 = {
        1, 0, 1, 1,
        0, 1, 0, 1,
        1, 0, 1, 0,
         1, 1, 0, 1
    };
    count.push_back(buf1);
    buf1.clear();

    buf1 = {
        0, 1, 0, 1,
        1, 0, 0, 0,
        1, 0, 0, 0,
         0, 1, 0, 1
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
        0, 1, 1, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        0, 1, 1, 0
    };
   count.push_back(buf1);
   buf1.clear();

    buf1= {
        0, 1, 1, 1,
        0, 1, 0, 0,
        0, 0, 1, 0,
        1, 1, 1, 0
    };
    count.push_back(buf1);
    buf1.clear();

     buf1 = {
        0, 0, 0, 1,
        0, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 0, 0
    };
    count.push_back(buf1);
    buf1.clear();

    buf1 = {
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 1,
        0, 0, 0, 0
    };
    count.push_back(buf1);
    buf1.clear();

    buf1 = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    count.push_back(buf1);
    buf1.clear();
    return  count[i];
}
