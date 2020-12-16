#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QPainter>
#include<QPushButton>
#include<mybtn.h>
#include<QWidget>
#include<QDebug>
#include<QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //窗口大小 固定
    this ->setFixedSize(400, 650);

    //菜单退出
    connect(ui ->actiontuichu,&QAction::triggered, [=] () {
        this -> close();
    });

    //标题
    this ->setWindowTitle("coinGames");

    //软件图标
    this ->setWindowIcon(QIcon(":/coinfiles/Coin0001.png"));

    //设置 开始按钮图标
    mybtn * starebtn = new mybtn(":/coinfiles/MenuSceneStartButton.png");
    starebtn ->setParent(this);
    starebtn ->move(150, this ->height() - starebtn->height() * 2 );


    //点击按钮跳转 窗口 到选关窗口
    connect(starebtn,&mybtn::clicked,[=] () {
        starebtn->uper();
        starebtn->down();

        //延时进入 选关界面
        QTimer::singleShot(500,this, [=] () {
            win = new chooseWin;
            this ->hide();
            win -> setFixedSize(400, 650);
            win->show();                      

            //接收 由choosewindow 发送过来的信号 实现 开始窗口重现, 选择窗口关闭
            connect(win, &chooseWin::backwindow, [=] () {
                QTimer ::singleShot(200, this, [=] () {
                    win -> hide();
                    this -> show();
                });

            });
        });
    });





}


//主背景设置
void MainWindow::paintEvent(QPaintEvent *event) {
    QPixmap pix;
    QPainter pain (this);
    pix.load(":/coinfiles/MenuSceneBg.png");
    pain.drawPixmap(0,0,this->width(), this->height(), pix);
}


MainWindow::~MainWindow()
{
    delete ui;
}
