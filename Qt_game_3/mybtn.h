#ifndef MYBTN_H
#define MYBTN_H

#include <QWidget>
#include<QPushButton>
class mybtn : public QPushButton
{
    Q_OBJECT
public:
//    explicit mybtn(QPushButton *parent = nullptr);
    mybtn(QString enter, QString back = "");
    QString enter;
    QString back;



    //创建按钮的动作: 向上跳 (up), 向下跳(down)

    void uper();
    void down();

    //鼠标点击两个图片之间的切换
     void mousePressEvent(QMouseEvent *e);
     void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYBTN_H
