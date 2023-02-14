#include "dresswin.h"
#include "ui_dresswin.h"

DressWin::DressWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DressWin)
{

    ui->setupUi(this);

    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
    setWindowOpacity(0.95);//设置透明度
    setStyleSheet("background-color:white;");

    Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);//保持窗口置顶2

    this->setWindowIcon(QIcon(":/images/icon/dress.png")); //设置窗口图标

    y=0;
    num=NUM;

    initBtn();
}

void DressWin::accept(vector<QPixmap> &body, vector<QPixmap> &ears,int bodyNum,int earsNum)
{
    this->body = body;
    this->ears = ears;
    this->bodyNum = bodyNum;
    this->earsNum = earsNum;
    bodyBtn[bodyNum]->setChecked(1);
    earsBtn[earsNum]->setChecked(1);
}

DressWin::~DressWin()
{
    delete ui;
}

void DressWin::paintEvent(QPaintEvent *)
{
    static QPixmap dummy(":/images/appearance/body/dummy.png");
    QPainter painter(this);

    for(int i = 0;i<num;i++)
        painter.drawPixmap(0,y+i*240,240,240,body[i]);
    for(int i = 0;i<num;i++){
        painter.drawPixmap(200,y+i*240,240,240,dummy);
        painter.drawPixmap(200,y+i*240,240,240,ears[i]);
    }


}

void DressWin::wheelEvent(QWheelEvent *event)
{
    static int speed = 40;//滚动速度

    if(event->delta() > 0){
        if(y<0)
            y += speed;
    }
    else{
        if(y>-230*num+460)
        y -= speed;
    }
    for(int i=0;i<num;i++){
        bodyBtn[i]->move(80,y+i*240+210);
        earsBtn[i]->move(280,y+i*240+210);
    }
    update();//调用绘画事件函数-paintEvent来更新画面
}

void DressWin::bodyChange(int id)
{
    bodyNum = id;
}

void DressWin::earsChange(int id)
{
    earsNum = id;
}

int DressWin::getBodyNum()
{
    return bodyNum;
}

int DressWin::getEarsNum()
{
    return earsNum;
}

void DressWin::initBtn()
{

    setStyleSheet("QPushButton{border:none;"
                  "background-color:rgb(200,200,200)"
                  ";border-radius: 15px;"
                  "border-style:outset;}"
                  "QPushButton::hover{background-color:rgb(170,200,255);}"
                  "QPushButton:checked{background-color:rgb(100,120,230);}");

    bodyBox =  new QButtonGroup;
    earsBox =  new QButtonGroup;
    bodyBox->setExclusive(true);
    earsBox->setExclusive(true);
    for(int i=0;i<num;i++){
        bodyBtn[i] = new QPushButton(this);
        bodyBtn[i]->setFixedSize(80,40);
        bodyBtn[i]->move(80,y+i*230+210);
        bodyBtn[i]->setIcon(QIcon(":/images/icon/choose.png"));
        bodyBtn[i]->setCheckable(1);
        bodyBox->addButton(bodyBtn[i],i);

        earsBtn[i] = new QPushButton(this);
        earsBtn[i]->setFixedSize(80,40);
        earsBtn[i]->move(280,y+i*230+210);
        earsBtn[i]->setIcon(QIcon(":/images/icon/choose.png"));
        earsBtn[i]->setCheckable(1);
        earsBox->addButton(earsBtn[i],i);
    }

    //当信号存在重载函数时，需要使用函数指针进行强制类型转换
    connect(bodyBox,
            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this,&DressWin::bodyChange);
    connect(earsBox,
            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            this,&DressWin::earsChange);
}


