#include "mainplaywin.h"
#include <QPainter>
#include <QPixmap>
#include "mybtn.h"
#include<QLabel>
#include<QFont>
#include<QLabel>
#include <QVector>
#include<QDebug>
#include<QTimer>
#include<QPropertyAnimation>
Mainplaywin::Mainplaywin (int i) {      //重写了 构造函数

            //设置back 音效
            QSound* bs = new QSound(":/coinfiles/back.wav");
            //设置 翻硬币音效
            QSound* cs = new QSound(":/coinfiles/coinChange.wav");

            //设置 胜利音效
            QSound* ses = new QSound(":/coinfiles/seccess.wav");

            this ->setFixedSize(400, 650);
             //建立胜利 标签
            QLabel * l = new QLabel(this);
            QPixmap pixlabel;
            pixlabel.load(":/coinfiles/LevelCompletedDialogBg.png");
            l ->setPixmap(pixlabel);
            l ->setGeometry(75, -pixlabel.height(), pixlabel.width(),pixlabel.height());  //一开始 label 隐藏在 窗口 负半轴 看不见, 只有当 胜利时 ,才会出现

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
                bs ->play();
                emit backchange();
            });

            if (i >= 0) {
                QFont font;                                                  //设置Leven 的字体
                font.setFamily("华文新魏");
                font.setPointSize(20);

                QLabel * l = new QLabel(QString("Lev %1").arg(i + 1), this);  //设置 游戏 关卡里面 的表示第几关的标签
                l -> setFont(font);
                l ->move(0, 610);
            }

            //构建硬币图标
            QVector<int>  res = coin(i);

             //设置硬币的背景 (构造硬币)
            for (int k = 0; k < 16; ++k) {
                QLabel * lb = new QLabel(this);
                QPixmap pix;
                pix.load(":/coinfiles/BoardNode.png");
                int x = (k % 4 * 50) + 100;
                int y = (k / 4 * 50) + 230;
                lb->resize(pix.width(), pix.height());
                lb->setPixmap(pix);
                lb ->move(x, y);

                //建立金色硬币 的图标
                if (res[k] == 1) {
                    mycoin* coinb = new mycoin(":/coinfiles/Coin0001.png");
                    coinb  ->flag = res[k];
                    coinb -> setParent(this);
                    coinb ->move(x, y);
                    buf.push_back(coinb);
                }

                //建立银色硬币 的图标
                else if (res[k] == 0) {
                    mycoin* coinb = new mycoin(":/coinfiles/Coin0008.png");
                     coinb ->flag = res[k];
                     coinb ->setParent(this);
                     coinb ->move(x, y);
                     buf.push_back(coinb);
                }
            }
            //实现 硬币的反转功能
            for (int i = 0; i < 16; ++i) {
                connect(buf[i], &mycoin::clicked, [=] () {
                       cs ->play();
                       buf[i] ->change(buf[i] ->flag);
                       buf[i] ->flag = buf[i] ->flag == 1 ? 0 : 1;
                       if (i % 4 -1 >= 0) {
                           buf[i - 1] ->change(buf[i - 1] ->flag);
                            buf[i - 1] ->flag = buf[i - 1] ->flag == 1 ? 0 : 1;
                       }
                       if (i % 4  + 1 < 4) {
                           buf[i + 1] ->change(buf[i + 1] ->flag);
                            buf[i + 1] ->flag = buf[i + 1] ->flag == 1 ? 0 : 1;
                       }
                       if (i / 4 + 1 < 4) {
                           buf[i + 4] ->change(buf[i + 4] ->flag);
                            buf[i + 4] ->flag = buf[i + 4] ->flag == 1 ? 0 : 1;
                       }

                       if (i / 4 - 1 >= 0) {
                           buf[i - 4] ->change(buf[i - 4] ->flag);
                            buf[i - 4] ->flag = buf[i - 4] ->flag == 1 ? 0 : 1;
                       }

//                        v=0; // 判断 是否 胜利
                       v = 0;
                       for (int k = 0; k< 16; ++k) {
                           if(buf[k] ->flag == 0) {
                               v = 1;
                               break;
                           }
                        }
                        if (v == 0)  {    // 如果 胜利 了 那么label 显示 图标
                            ses ->play();
                            QPropertyAnimation * an = new QPropertyAnimation(l, "geometry");
                            an->setDuration(1000);
                            an->setStartValue(QRect(l->x(), l ->y(), l ->width(), l ->height()) );
                            an ->setEndValue(QRect(l->x(), l ->y() + 150, l->width(), l ->height()));
                            an->setEasingCurve(QEasingCurve::OutBounce);
                            an ->start();
                            emit winning();
                        }
                });
           }
}

void Mainplaywin::mousePressEvent(QMouseEvent *event) {
    if (v == 0) {
        qDebug() << "禁用!";
        return;
    }
    //else QMainWindow::mousePressEvent(event);
}

void Mainplaywin::mouseDoubleClickEvent(QMouseEvent* event) {
          return;

} // 鼠标禁用双击


 //游戏场景的 背景 渲染
void  Mainplaywin ::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QPixmap pix;
    pix.load(":/coinfiles/OtherSceneBg.png");
    p.drawPixmap(0,0,this->width(), this ->height(), pix);
}



//关卡模板的构建
QVector <int> Mainplaywin:: coin (int i) {
    QVector<QVector<int>> count;
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
        0, 1, 0, 0,
        0, 0, 1, 0,
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
