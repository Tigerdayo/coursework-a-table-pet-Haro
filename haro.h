#ifndef HARO_H
#define HARO_H

#include <QMainWindow>
#include<QMouseEvent>
#include<QtGlobal>
#include <QLabel>
#include<QPoint>
#include<QTimer>
#include<QPushButton>
#include<QCalendarWidget>
#include<QFile>
#include<QDataStream>

#include<QSystemTrayIcon>

#include"dresswin.h"
#include"setwin.h"
#include"musicwin.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Haro; }
QT_END_NAMESPACE

class Haro : public QMainWindow
{
    Q_OBJECT
private:
    Ui::Haro *ui;

    DressWin *dressWindow;//换装窗口指针

    SetWin *setWindow;//设置窗口指针

    MusicWin *musicWindow;//音乐窗口页面指针

    QCalendarWidget *calenWindow;//日历窗口指针

    QPoint moveLeftTop;//坐标点

    vector<QPixmap> movement;//表情图片容器

    vector<QPixmap> spMovement;//特殊动作图片容器

    vector<int>faceNum;//每个表情对应帧数与起始位置

    vector<QPixmap> body,ears1,ears2;//各部件对应图片容器

    QPixmap eyes,stripe;//眼睛和眼部遮罩

    QLabel *bodyImage,*earsImage,*eyesImage,*stripeImage;//各部件对应标签

    QTimer *timer;//定时器

    int size;//体型大小

    int btnSize;//按钮大小

    int bodyNum,earsNum;//身体和耳朵对应装扮序号

    int face;//表情序号

    int faceSum;//表情数量

    int spMove;//特殊动作序号

    int btnSwitch_1,btnSwitch_2;//菜单按钮显示开关

    QPushButton *closeBtn;//关闭按钮
    QPushButton *dressBtn;//换装按钮
    QPushButton *moreBtn;//展开更多按钮
    QPushButton *minBtn;//最小化按钮
    QPushButton *setBtn;//设置按钮
    QPushButton *musicBtn;//音乐按钮
    QPushButton *gameBtn;//游戏按钮
    QPushButton *calenBtn;//日历按钮

    QSystemTrayIcon* pSystemTray;//系统托盘
public:
    Haro(QWidget *parent = nullptr);
    ~Haro();  

    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件-虚函数

    void mousePressEvent(QMouseEvent *event);//鼠标点击事件-虚函数

    void eyesMovementLoad();//眼部动作载入

    void eyesMovement();//眼部动作表情

    inline void imageSet(QLabel *image,QPixmap map);//设置各部位图片

    void imageLoad();//各部位图片载入

    void initBtn();//初始化按钮

    void reInitBtn();//修改大小时再次初始化按钮

    void initSystemTray();//初始化系统托盘

    void closeBtnPush();//点击关闭按钮事件

    void dressBtnPush();//点击装扮按钮事件

    void moreBtnPush();//点击最展开更多按钮事件

    void minBtnPush();//点击最小化按钮事件

    void setBtnPush();//点击设置按钮事件

    void musicBtnPush();//点击设置按钮事件

    void gameBtnPush();//点击游戏按钮事件

    void calenBtnPush();//点击日历按钮事件

    void systemTrayPush();//点击系统托盘事件

    void btnSwitchRole();//根据btnSwitch切换按钮状态

    void specialMovementLoad();//特殊动作载入

    void specialMovement();//特殊动作事件

    void saveData();//存储数据

};




#endif // HARO_H

