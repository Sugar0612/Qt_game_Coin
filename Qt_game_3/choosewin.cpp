#include "choosewin.h"
#include<QPainter>
#include <QPixmap>
#include<QMenuBar>
#include<QLabel>
#include <QFont>
#include<QDebug>
#include<QTimer>
#include"mybtn.h"
chooseWin::chooseWin(QWidget *parent) : QMainWindow(parent)
{
            //设置 选择窗口 的图标
            this -> setWindowIcon(QIcon(":/coinfiles/Coin0001.png"));

            //设置 选择窗口的 标题
            this -> setWindowTitle("coinGames");

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

            for (int i = 0; i < 20; ++i) {
                mybtn * b = new mybtn(":/coinfiles/LevelIcon.png");
                b ->setParent(this);
                int x = (40 + b -> width() ) * (i % 4) + 35;
                int y = (i / 4) * 80 + 80;
                b ->move((40 + b -> width() ) * (i % 4) + 35,  y);

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
                 l -> setAttribute(Qt::WA_TransparentForMouseEvents);  // 鼠标 穿透 (这样可以 点击到 标签下的 按钮了)

                 //当点击按钮b 时 进入游戏主场景
                 connect(b, &mybtn::clicked, [=] () {
                     b->uper();
                     b->down();
                     play = new  Mainplaywin(i);
                     QTimer::singleShot(200, this, [=] () {
                         this ->hide();
                         play ->show();
                     });

                     //接受 到 游戏主场景的信号 返回 到 选择 窗口
                     connect(play, &Mainplaywin::backchange, [=] () {
                         QTimer::singleShot(400, this, [=] () {
                             play ->hide();
                             this ->show();
                         });
                     });
                 });

            }




            //创建 back 按钮
            mybtn * backbtn = new  mybtn(":/coinfiles/BackButton.png", ":/coinfiles/BackButtonSelected.png");
            backbtn ->setParent(this);

            backbtn ->move(325, 620);

            connect(backbtn, &mybtn::clicked, [=] () {
                emit backwindow();
            }); //点击 back 按钮 出发 backwindow 信号
}

//选关界面 的 背景
void chooseWin::paintEvent(QPaintEvent *event) {
        QPainter pain(this);
        QPixmap pix;
        pix.load(":/coinfiles/PlayLevelSceneBg.png");
        pain.drawPixmap(0,0, this->width(), this ->height(), pix);
}
