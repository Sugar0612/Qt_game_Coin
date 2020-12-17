#ifndef MAINPLAYWIN_H
#define MAINPLAYWIN_H

#include <QMainWindow>
#include<QVector>
#include"mainplaywin.h"

class Mainplaywin : public QMainWindow
{
    Q_OBJECT
public:
//    explicit Mainplaywin(QWidget *parent = nullptr);
    Mainplaywin (int i = -1);
    void paintEvent(QPaintEvent *event);  //给游戏 主窗口背景
signals:
     void backchange();
public slots:
};

#endif // MAINPLAYWIN_H
