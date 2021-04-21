#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include<QLabel>
class myLabel : public QLabel
{
    Q_OBJECT
public:
    //explicit myLabel(QWidget *parent = nullptr);
    myLabel (QString files);     //mylabel 构造 函数
    void lowerL ();             //执行 mylabel 的 从 上到下弹入的动作
    QString files;    //文件 名的放入

signals:

public slots:
};

#endif // MYLABEL_H
