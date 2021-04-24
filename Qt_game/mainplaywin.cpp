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
#include<QString>
#include<QPixmap>
#include<QPropertyAnimation>
#include"mybtn.h"

Mainplaywin::Mainplaywin (int i) {      //重写了 构造函数
                //让h 去代替 i
                h = i;

             //每个关卡的步数不一样  越到后面步数会越来越珍贵
             stap = i + 1;

             //重新开始按钮
             QString rebs = "min-width: 50px; min-height: 50px; max-width: 50px; max-height: 50px; border-radius: 25px;";
             mybtn* reb = new mybtn(":/coinfiles/rebegin_1.png", ":/coinfiles/rebegin_2.png");
             reb ->setParent(this);
             reb ->move(0 - reb->width(), 160);   // 175 160
             reb ->setStyleSheet(rebs);

             //下一关按钮
             const QString nexts= "min-width: 50px; min-height: 50px; max-width: 50px; max-height: 50px; border: 1px solid black; border-radius: 25px";
             mybtn* next = new mybtn(":/coinfiles/next_1.png", ":/coinfiles/next_2.png");
             next ->setParent(this);
             next ->setStyleSheet(nexts);
             next ->move(-next ->width(), 160);


             // 构建失败的游戏 标签
               QLabel* fail = new QLabel(this);
               QPixmap fail_pix;
               fail_pix.load(":/coinfiles/fail.png");
               fail ->setPixmap(fail_pix);
               fail ->resize(fail_pix.width(), fail_pix.height());
               fail ->setGeometry(75, -fail_pix.height(), fail_pix.width(), fail_pix.height());
               fail ->setStyleSheet(QString("border: 2px; border-radius: 80px"));     // 将标签设置成圆角


            //设置back 音效
            QSound* bs = new QSound(":/coinfiles/back.wav");
            //设置 翻硬币音效
            QSound* cs = new QSound(":/coinfiles/coinChange.wav");

            //设置 胜利音效
            QSound* ses = new QSound(":/coinfiles/seccess.wav");
            // 失败音效
            QSound* boo = new QSound(":/coinfiles/boo.wav");

            // 主背景音乐
            QSound* mainplay = new QSound(":/coinfiles/play.wav");

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

            QFont font;                                                  //设置Leven 的字体
            font.setFamily("华文新魏");
            font.setPointSize(20);

            QLabel * lev = new QLabel(QString("Lev %1").arg(i + 1), this);  //设置 游戏 关卡里面 的表示第几关的标签
            lev -> setFont(font);
            lev ->move(0, 610);

            //点击 back  触发(返回到 选择关卡窗口) 的信号
            connect(back, &mybtn::clicked, [=] () {
                bs ->play();
                mainplay ->stop();
                this ->reidx = h;
                emit backchange();
                h = i;
                lev ->setText(QString("Lev %1").arg(i + 1));
                QVector<int> bk = coin(i);
                for(int j = 0; j < bk.size(); ++j) {
                   buf[j] ->flag = (bk[j] == 1) ? 0 : 1;
                }

                for(int j = 0; j < bk.size(); ++j) {
                    buf[j] ->change(buf[j] ->flag);
                    buf[j] ->flag = buf[j] ->flag == 1 ? 0 : 1;
                }

                stap = i + 1;
                stapL ->setText(QString("步数: %1").arg(stap));  //步数初始化
                if(fail_fl == 1) {
                    QPropertyAnimation* repro = new QPropertyAnimation(fail, "geometry");
                    repro ->setDuration(500);
                    repro ->setStartValue(QRect(fail ->x(), fail ->y(), fail ->width(), fail ->height()));
                    repro ->setEndValue(QRect(fail ->x(), fail ->y() - 140, fail ->width(), fail ->height()));
                    repro ->setEasingCurve(QEasingCurve::OutBounce);
                    repro ->start();
                    fail_fl = 0; // 失败 标识变成0
                }

                if(v == 0) {
                    QPropertyAnimation* revpro = new QPropertyAnimation(l, "geometry");
                    revpro ->setDuration(500);
                    revpro ->setStartValue(QRect(l ->x(), l ->y(), l ->width(), l ->height()));
                    revpro ->setEndValue(QRect(l ->x(), l ->y() - 150, l ->width(), l ->height()));
                    revpro ->setEasingCurve(QEasingCurve::OutBounce);
                    revpro ->start();
                    v = 1;   //现在不胜利
                    flag = 0; // 胜利标签可以下移了
                }

                //关于reb 按钮的退场方式
                rebout(reb);
                reflag = 0;

                //关于next 按钮的退场方式
                rebout(next);
            });


            // 设置显示步数的标签
            stapL = new QLabel(QString("步数:  %1").arg(stap), this);
            stapL ->setFont(font);
            stapL ->move(250,160);

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

            //如果reb 被点击那么本关游戏重新开始
            connect(reb, &mybtn::clicked, [=]() {
                QVector<int> rebnt = coin(h);
                for(int j = 0; j < rebnt.size(); ++j) {
                   buf[j] ->flag = (rebnt[j] == 1) ? 0 : 1;
                }

                for(int j = 0; j < rebnt.size(); ++j) {
                    buf[j] ->change(buf[j] ->flag);
                    buf[j] ->flag = buf[j] ->flag == 1 ? 0 : 1;
                }
                mainplay ->play();
                stap = h + 1;
                stapL ->setText(QString("步数: %1").arg(stap));  //步数初始化
                if(fail_fl == 1) {
                    QPropertyAnimation* repro = new QPropertyAnimation(fail, "geometry");
                    repro ->setDuration(500);
                    repro ->setStartValue(QRect(fail ->x(), fail ->y(), fail ->width(), fail ->height()));
                    repro ->setEndValue(QRect(fail ->x(), fail ->y() - 140, fail ->width(), fail ->height()));
                    repro ->setEasingCurve(QEasingCurve::OutBounce);
                    repro ->start();
                    fail_fl = 0; // 失败 标识变成0
                }

                if(v == 0) {
                    QPropertyAnimation* revpro = new QPropertyAnimation(l, "geometry");
                    revpro ->setDuration(500);
                    revpro ->setStartValue(QRect(l ->x(), l ->y(), l ->width(), l ->height()));
                    revpro ->setEndValue(QRect(l ->x(), l ->y() - 150, l ->width(), l ->height()));
                    revpro ->setEasingCurve(QEasingCurve::OutBounce);
                    revpro ->start();
                    v = 1;   //现在不胜利
                    flag = 0; // 胜利标签可以下移了
                }

                //关于reb 按钮的退场方式
                rebout(reb);
                reflag = 0;
                //关于next 按钮的退场方式
                if(next ->x() > 0) {
                    QPropertyAnimation* reban = new QPropertyAnimation(next,"geometry");
                    reban ->setDuration(500);
                    reban ->setStartValue(QRect(next ->x(), next ->y(), next ->width(), next ->height()));
                    reban ->setEndValue(QRect(next ->x()  - 140, next ->y(), next ->width(), next ->height()));
                    reban ->setEasingCurve(QEasingCurve::OutQuint);
                    reban ->start();
                }
            });


            //如果点击了 next 那么 进入下一关
            connect(next, &mybtn::clicked, [=] () {
                   h = h + 1;
                  if (h < 20)  {
                      v = 1;   //现在不胜利
                      flag = 0; // 胜利标签可以下移了
                      QVector<int> nextwin = coin(h);
                      stap = h + 1;
                      stapL ->setText(QString("步数: %1").arg(stap));  //步数初始化
                      lev ->setText(QString("Lev %1").arg(h + 1));

                      for(int k = 0; k < nextwin.size(); ++k) {
                            buf[k] ->flag = (nextwin[k] == 1) ? 0 : 1;
                      }

                      for(int k = 0; k < buf.size(); ++k) {
                          buf[k] ->change(buf[k] ->flag);
                          buf[k] ->flag = (buf[k] ->flag == 1) ? 0 : 1;
                      }

                      mainplay ->play();
                      QPropertyAnimation* revpro = new QPropertyAnimation(l, "geometry");
                      revpro ->setDuration(500);
                      revpro ->setStartValue(QRect(l ->x(), l ->y(), l ->width(), l ->height()));
                      revpro ->setEndValue(QRect(l ->x(), l ->y() - 150, l ->width(), l ->height()));
                      revpro ->setEasingCurve(QEasingCurve::OutBounce);
                      revpro ->start();

                      //关于reb 按钮的退场方式
                      rebout(reb);
                      reflag = 0;   // 可以进入了

                      //关于next 按钮的退场方式
                      if (next ->x() > 0) {
                          QPropertyAnimation* reban = new QPropertyAnimation(next,"geometry");
                          reban ->setDuration(500);
                          reban ->setStartValue(QRect(next ->x(), next ->y(), next ->width(), next ->height()));
                          reban ->setEndValue(QRect(next ->x()  - 140, next ->y(), next ->width(), next ->height()));
                          reban ->setEasingCurve(QEasingCurve::OutQuint);
                          reban ->start();
                      }

                 }
            });

            // 判断 是否 胜利
             v = 1;
             // 判断是否 失败了
             fail_fl = 0;

            //实现 硬币的反转功能
            for (int i = 0; i < 16; ++i) {
                connect(buf[i], &mycoin::clicked, [=] () {
                    if(v == 1 && fail_fl == 0) {
                           stap--; //步数减一
                           cs ->play();   //金币反转音效
                           stapL ->setText(QString("步数:  %1").arg(stap));
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
                    }

                       for (int k = 0; k< 16; ++k) {
                           if(buf[k] ->flag == 0) {
                               v = 1;
                               break;
                           }

                           if(k == 15 && buf[k] ->flag == 1) v = 0;
                        }

                        if (v == 0 && flag == 0 && fail_fl == 0)  {    // 如果 胜利 了 那么label 显示 图标
                            ses ->play();
                            mainplay ->stop();
                            QPropertyAnimation * an = new QPropertyAnimation(l, "geometry");
                            an->setDuration(1000);   // 动画时间
                            an->setStartValue(QRect(l->x(), l ->y(), l ->width(), l ->height()) );
                            an ->setEndValue(QRect(l->x(), l ->y() + 150, l->width(), l ->height()));
                            an->setEasingCurve(QEasingCurve::OutBounce);
                            an ->start();
                            flag = 1;   //标签不能下移了

                            //关于reb 按钮的进入方式
                            rebin(reb);

                            //显示next按钮
                            if(next ->x() < 0) {
                                QPropertyAnimation* reban = new QPropertyAnimation(next,"geometry");
                                reban ->setDuration(1000);
                                reban ->setStartValue(QRect(next ->x(), next ->y(), next ->width(), next ->height()));
                                reban ->setEndValue(QRect(next ->x()  + 140, next ->y(), next ->width(), next ->height()));
                                reban ->setEasingCurve(QEasingCurve::OutQuint);
                                reban ->start();
                            }
                            emit winning();
                        }

                        if(stap == 0 && v == 1) {    //如果失败了显示失败的图标
                            boo ->play();
                            mainplay ->stop();
                            if(fail_fl  ==  0) {
                                QPropertyAnimation* fa = new QPropertyAnimation(fail, "geometry");
                                fa ->setDuration(1000);
                                fa ->setStartValue(QRect(fail ->x(), fail ->y(), fail ->width(), fail ->height()));
                                fa ->setEndValue(QRect(fail ->x(), fail ->y() + 140, fail ->width(), fail ->height()));
                                fa ->setEasingCurve(QEasingCurve::OutBounce);
                                fa ->start();
                                fail_fl = 1;
                                //关于reb 按钮的进入方式
                                if(reflag == 0) {
                                    rebin(reb);
                                    reflag = 1; // 1时不可进入了
                                }
                            }
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


 //游戏场景的 背景 渲染
void  Mainplaywin ::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QPixmap pix;
    pix.load(":/coinfiles/OtherSceneBg.png");
    p.drawPixmap(0,0,this->width(), this ->height(), pix);
}

//关于按钮的进入方式
void Mainplaywin::rebin(mybtn* reb) {
    if(reb ->x() < 0) {
        QPropertyAnimation* reban = new QPropertyAnimation(reb,"geometry");
        reban ->setDuration(1000);
        reban ->setStartValue(QRect(reb ->x(), reb ->y(), reb ->width(), reb ->height()));
        reban ->setEndValue(QRect(reb ->x()  + 220, reb ->y(), reb ->width(), reb ->height()));
        reban ->setEasingCurve(QEasingCurve::OutQuint);
        reban ->start();
    }
}

//关于按钮的退场方式
void Mainplaywin::rebout(mybtn* reb) {
    if(reb ->x() > 0) {
        QPropertyAnimation* reban = new QPropertyAnimation(reb,"geometry");
        reban ->setDuration(500);
        reban ->setStartValue(QRect(reb ->x(), reb ->y(), reb ->width(), reb ->height()));
        reban ->setEndValue(QRect(reb ->x()  - 220, reb ->y(), reb ->width(), reb ->height()));
        reban ->setEasingCurve(QEasingCurve::OutQuint);
        reban ->start();
    }
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
        0, 0, 1, 1,
        0, 1, 1, 1,
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
