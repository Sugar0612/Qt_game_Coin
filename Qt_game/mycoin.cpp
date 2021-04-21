#include "mycoin.h"
 #include <QPainter>
#include<QPixmap>
#include <QMessageBox>
#include <QTimer>
#include<QDebug>
//建立一个 金币 类 用来实现 金币的 翻金币 的 功能
mycoin::mycoin(QString s) {
    this ->s = s;
    this -> flag = flag;

      if (s == "")  {
          QMessageBox ::information(this, "错误!", "未录入图片资源文件", QMessageBox::Ok);
          return ;
      }

      //构建硬币 的背景图片
      QPixmap pix;
      pix.load(s);

      //设置硬币 大小
      this ->resize(pix.width(), pix.height());

      //设置按钮 的 风格
      this -> setStyleSheet("QPushButton{border:0px;}");

      //设置硬币 的背景图片
      this ->setIcon(QIcon(pix));

      //设置图片大小
      this ->setIconSize(QSize(pix.width(), pix.height()));
}

//chnange 函数 的功能是 实现 硬币的反转
void mycoin::change(int flag) {
    //启动反转 定时器
  time1 = new QTimer(this);
  time2 = new QTimer(this);
  time1 ->start(30);
  time2->start(30);


    if (flag == 1) {
            connect(time1, &QTimer::timeout, [=] {
                QPixmap pix1;
                QString file = QString(":/coinfiles/Coin000%1").arg(index++);
                pix1.load(file);
                this ->resize(QSize(pix1.width(), pix1.height()));
                this ->setStyleSheet("QPushButton{border:0px;}");

                this ->setIcon(QIcon(pix1));

                this ->setIconSize(QSize(pix1.width(), pix1.height()));
                if (index > 8) {
                    index = 2;
                    time1->stop();
                }
        });
    }
    else {
        connect(time2, &QTimer::timeout, [=] {
            QPixmap pix2;
            QString file = QString(":/coinfiles/Coin000%1").arg(index_--);
            pix2.load(file);
            this ->resize(QSize(pix2.width(), pix2.height()));

            this ->setStyleSheet("QPushButton{border:0px;}");

            this ->setIcon(QIcon(pix2));

            this ->setIconSize(QSize(pix2.width(), pix2.height()));
            if (index_ <  1) {
                index_ = 7;
                time2->stop();
            }
        });
    }
}


void mycoin::mouseDoubleClickEvent(QMouseEvent *event) {} //禁止使用 鼠标双击
