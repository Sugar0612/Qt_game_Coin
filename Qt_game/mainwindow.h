#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"choosewin.h"
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
