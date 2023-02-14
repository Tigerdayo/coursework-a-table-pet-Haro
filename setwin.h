#ifndef SETWIN_H
#define SETWIN_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QString>

namespace Ui {
class SetWin;
}

class SetWin : public QWidget
{
    Q_OBJECT

public:
    explicit SetWin(QWidget *parent = nullptr);
    ~SetWin();

    void setSize(int);//设置size值

    int getSize();//外部获取size值

private slots:


    void on_sizeSlider_valueChanged(int value);//滑动条槽函数

private:

    int haroSize;//haro大小参数

    QLabel *sizeNum;//显示size值标签

    Ui::SetWin *ui;
};

#endif // SETWIN_H
