#ifndef DRESSWIN_H
#define DRESSWIN_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include<QWheelEvent>
#include<QPushButton>
#include<QButtonGroup>

using namespace std;

const int NUM = 8;//装扮数量

namespace Ui {
class DressWin;
}

class DressWin : public QWidget
{
    Q_OBJECT

public:
    explicit DressWin(QWidget *parent = nullptr);
    void accept(vector<QPixmap>& body,vector<QPixmap>& ears,int bodyNum,int earsNum);
    ~DressWin();
    void paintEvent(QPaintEvent *);//绘画事件
    void wheelEvent(QWheelEvent *event);//鼠标滚轮事件
    int getBodyNum();//返回对应装扮序号
    int getEarsNum();
private:
    void bodyChange(int);//槽函数-点击按钮切换对应装扮序号
    void earsChange(int);
    void initBtn();//初始化按钮
    vector<QPixmap> body,ears;//各部件对应图片容器
    QPushButton *bodyBtn[NUM],*earsBtn[NUM];//各部件对应按钮容器
    QButtonGroup *bodyBox,*earsBox;//按钮组
    int bodyNum,earsNum;//身体和耳朵对应装扮序号
    int y;//鼠标中键滑动轴对应y坐标
    int num;//装扮数量
    Ui::DressWin *ui;
};

#endif // DRESSWIN_H
