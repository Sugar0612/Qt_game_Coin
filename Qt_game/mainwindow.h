#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"caption.h"
#include"choosewin.h"
#include<QSound>
#include<QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

    //创建选择 关卡
    chooseWin * win = NULL;

    //关于窗口
    caption* cap = nullptr;


   int size = 0;  // 过了几关
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
