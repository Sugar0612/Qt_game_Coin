#include "mybtn.h"
#include<QPushButton>
#include<QPixmap>
#include<QMessageBox>
#include<QPropertyAnimation>
 mybtn ::mybtn (QString enter, QString back) {
     this ->enter = enter;
     this ->back = back;

     QPixmap pix;
     bool flag=
     flag = pix.load(enter);

     //判断是否 图片加载错误
     if (flag == false) {
         QMessageBox::information(this,"加载错误", "图标btn 加载错误!", QMessageBox::Ok);
         return;
     }

     //按钮大小 固定
     this ->setFixedSize(pix.width(), this ->height());

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
 
