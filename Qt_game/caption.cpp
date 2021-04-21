#include "caption.h"
#include<Qicon>
#include<QTextEdit>
#include<QFileDialog>
#include<QFile>
#include<QByteArray>
caption::caption(QWidget *parent) : QWidget(parent)
{
    this ->setWindowTitle("说明");  // 窗口的标题
    this ->setWindowIcon(QIcon(":/coinfiles/Coin0001.png"));  // 窗口的图标

    //创建文本文件 写入文本文字
      QString f = "E:/c++ QT/gameplay_github/caption.txt";
      QTextEdit* t = new QTextEdit(this); // 文本文框
       t ->resize(400, 650);

       //读取txt 文件的文件路径
       QFile file(f);
       file.open(QIODevice::ReadOnly);   // 设置成只读文件

       QByteArray text =  file.readAll(); // 读取内容放入text中
       t -> setText(text);                              // 文字读入
       t ->setFontFamily("华文新魏");   //字体


}
