#include "mylabel.h"
#include<QLabel>
#include<QPropertyAnimation>
#include<QPixmap>
#include<QMessageBox>
myLabel ::myLabel(QString files) : files(files)  {
    this -> move(- 200, -200); //初始位置



    QPixmap pix;   //构建标签 的  pixmap

    bool flag = pix.load(this ->files);   //如果 图片 无法 录入 那么 显示信息对话框
    if ( !flag ) {
        QMessageBox::information(this , "错误", "图片无法录入", QMessageBox::Ok);
        return;
    }

    this -> setGeometry(-pix.width(), -pix.height(),pix.width(), pix.height());   //设置胜利标签 的 初始位置

    this ->setPixmap(pix);   //将 this -> files所 录入 的 文件图片进行 渲染



}
