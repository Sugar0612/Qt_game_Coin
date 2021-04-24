#include "choosewin.h"
#include<QPainter>
#include <QPixmap>
#include<QMenuBar>
#include<QLabel>
#include <QFont>
#include<QDebug>
#include<QTimer>
#include<qmath.h>
#include<QMessageBox>
#include"mybtn.h"

chooseWin::chooseWin(QWidget *parent) : QMainWindow(parent)
{

             //设置 返回音效
            QSound* bs = new QSound(":/coinfiles/back.wav");

            //设置 点击关卡音效
            QSound* s = new QSound(":/coinfiles/start.wav");

            // 主背景音乐
            QSound* mainplay = new QSound(":/coinfiles/play.wav");

            //背景音效
            QSound* wel = new QSound(":/coinfiles/wel.wav");
            wel ->play();

            //设置 选择窗口 的图标
            this -> setWindowIcon(QIcon(":/coinfiles/Coin0001.png"));

            //设置 选择窗口的 标题
            this -> setWindowTitle("选择关卡");

            //设置一个菜单 执行退出操作
            QMenuBar * menu = menuBar();
            setMenuBar(menu);

           QMenu* men1 =  menu->addMenu("菜单");
           QAction * ac =  men1 ->addAction("退出");

           //点击 退出按钮 退出程序
           connect(ac, &QAction::triggered, [=] () {
               this -> hide();
           });

           //在菜单中 加入 帮助文档
            QAction * ac1 =  men1 ->addAction("帮助");


            //点击帮助打开caption
            connect(ac1, &QAction::triggered, [=]() {
                cp = new caption();
                cp->show();
            });

            for(int i = 0; i < 20; ++i) {
                Mainplaywin* p = new Mainplaywin(i);
                playarr.push_back(p);
                if(i == 0) playarr[i] ->key = 1;
            }  // 定义20个场景 用playarr进行封装

            for (int i = 0; i < 20; ++i)  {
                mybtn * b = new mybtn(":/coinfiles/LevelIcon.png");
                b ->setParent(this);
                int x = (40 + b -> width()) * (i % 4) + 35;
                int y = (i / 4) * 80 + 80;
                b ->move((40 + b -> width() ) * (i % 4) + 35,  y);
                choosearr.push_back(b);
                //设置按钮的  关卡数 (标签)
                  QFont  f;
                  f.setFamily("华文新魏");
                  f.setPointSize(14);

                 //将标签字体 改变
                 QLabel * l = new QLabel(this);
                 l ->setFont(f);
                 l ->setText(QString("%1").arg(i + 1));
                 l ->move((40 + b -> width() ) * (i % 4) + 35 + b ->width() - 80, y + 15);
                 l ->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                 l -> setAttribute(Qt::WA_TransparentForMouseEvents);   // 鼠标 穿透 (这样可以 点击到 标签下的 按钮了)
            }




            //创建 back 按钮
            mybtn * backbtn = new  mybtn(":/coinfiles/BackButton.png", ":/coinfiles/BackButtonSelected.png");
            backbtn ->setParent(this);

            backbtn ->move(325, 620);

            connect(backbtn, &mybtn::clicked, [=] () {
                 bs ->play();
                 wel ->stop();
                emit backwindow();
            }); //点击 back 按钮 出发 backwindow 信号


            int i = 0;
            while(i < 20) {
                 //当点击按钮b 时 进入游戏主场景
                 connect(choosearr[i], &mybtn::clicked, [=] () {
                     choosearr[i]->uper();

                     s->play();
                     choosearr[i]->down();
                     if(playarr[i] ->key == 1 || capcity >= i) {
                         QTimer::singleShot(200, this, [=] () {
                             this ->hide();
                             playarr[i] ->show();
                             wel ->stop();
                             mainplay ->play();
                             connect(playarr[i], &Mainplaywin::winning, [=] () {
                                    mainplay ->stop();
                                    if(i + 1 < 20) {
                                        playarr[i + 1] ->key = 1;
                                        if(i + 1 > capcity) capcity = i + 1;
                                    }
                            });  // 如果winning 触发 那么说明 第i 关成功 开启 第 i + 1 (i+ 1 < 20) 关
                         });
                     } else {
                         QMessageBox::information(this, "提示", "你必须完成前面的关卡!", QMessageBox::Ok);
                     }

                     //接受 到 游戏主场景的信号 返回 到 选择 窗口
                     connect(playarr[i], &Mainplaywin::backchange, [=] () {
                         mainplay ->stop();
                         wel ->play();
                         QTimer::singleShot(400, this, [=] () {
                             int reindex = playarr[i] ->reidx;
                             if(reindex > capcity) capcity = reindex;
                             for(int i = 0; i <= reindex; ++i) {
                                 if(reindex < 20) playarr[i] ->key = 1;
                             }
                             playarr[i] ->hide();
                             this ->show();
                         });
                     });
                 });
                 i++;
            }

}

//选关界面 的 背景
void chooseWin::paintEvent(QPaintEvent *event) {
        QPainter pain(this);
        QPixmap pix;
        pix.load(":/coinfiles/PlayLevelSceneBg.png");
        pain.drawPixmap(0,0, this->width(), this ->height(), pix);
}
