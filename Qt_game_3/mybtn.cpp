#include "mybtn.h"
#include<QPushButton>
#include<QPixmap>
#include<QMessageBox>
#include<QPropertyAnimation>
 mybtn ::mybtn (QString enter, QString back) {
     this ->enter = enter;
     this ->back = back;

     QPixmap pix;
     bool flag;
     flag = pix.load(enter);

     //判断是否 图片加载错误
     if (flag == false) {
         QMessageBox::information(this,"加载错误", "图标btn 加载错误!", QMessageBox::Ok);
         return;
     }

     //按钮大小 固定
     this ->setFixedSize(pix.width(), pix.height());

     //设置 按钮 的风格
     this ->setStyleSheet("QPushButton{border:0px;}");

     //设置按钮图标
     this ->setIcon(QIcon(pix));

     //设置 图标 大小
     this ->setIconSize(QSize(pix.width(), pix.height()));
 }

 
 void mybtn::uper() {
     
        //设置 动态对象
       QPropertyAnimation * an = new QPropertyAnimation(this, "geometry");
       
       // 设置 动画时间
       an ->setDuration(400);
       
       //设置开始
       an ->setStartValue(QRect(this ->x(), this ->y(), this ->width(), this ->height()));
       
       //结束
       an ->setEndValue(QRect(this ->x(), this ->y() + 10, this ->width(), this ->height()));
       
       //设置 风格 
       an ->setEasingCurve(QEasingCurve::OutBounce);

       //开始 执行动作
       an -> start();
 }
 
 
 
void mybtn::down() {
    //设置 动态对象
   QPropertyAnimation * an = new QPropertyAnimation(this, "geometry");

   // 设置 动画时间
   an ->setDuration(400);

   //设置开始
   an ->setStartValue(QRect(this ->x(), this ->y() + 10, this ->width(), this ->height()));

   //结束
   an ->setEndValue(QRect(this ->x(), this ->y(), this ->width(), this ->height()));

   //设置 风格
   an ->setEasingCurve(QEasingCurve::OutBounce);

   //执行 动作
   an ->start();
}
 

//点下鼠标时 图片被改变

void mybtn::mousePressEvent(QMouseEvent *e) {
    QPixmap pix;
    bool flag =  pix.load(this ->back);


    //如果 back 存在 那么将切换按钮上的图片
        if (flag) {
            //改变图标
            this ->setIcon(QIcon(this ->back));
        }


        QPushButton::mousePressEvent(e);
}
//放开 鼠标时 图片返回原来的样子

void mybtn::mouseReleaseEvent(QMouseEvent *e) {
    QPixmap pix;
    bool flag = pix.load(this ->enter);

    if (flag) {
        this ->setIcon(QIcon(this->enter));
    }
    QPushButton::mouseReleaseEvent(e);
}
