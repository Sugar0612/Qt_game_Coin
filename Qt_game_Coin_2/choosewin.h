#ifndef CHOOSEWIN_H
#define CHOOSEWIN_H

#include <QMainWindow>

class chooseWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseWin(QWidget *parent = nullptr);
       void paintEvent(QPaintEvent *event);


signals:
        void backwindow(); // 点击 back 按钮 则 发送 信号 , 关闭选关界面, 重现开始 页面

public slots:
};

#endif // CHOOSEWIN_H
