#include "musicwin.h"
#include "ui_musicwin.h"

MusicWin::MusicWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicWin)
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

    this->setWindowIcon(QIcon(":/images/icon/music.png")); //设置窗口图标

    initBtn();//初始化按钮
    initMedia();//初始化媒体
}

MusicWin::~MusicWin()
{
    delete ui;
}

void MusicWin::initBtn()
{
    //设置按钮样式
    setStyleSheet("QPushButton{border: none;"
                  "background-color:rgb(255,255,255);border-radius: 35px;}"
                  "QPushButton::hover{background-color:rgb(200,200,200);}"
                  "QPushButton:pressed{background-color:rgb(160,160,160);}");

    next = new QPushButton(this);
    last = new QPushButton(this);
    pause = new QPushButton(this);
    play = new QPushButton(this);
    add = new QPushButton(this);
    //图标载入
    next->setIcon(QIcon(":/images/icon/next.png"));
    last->setIcon(QIcon(":/images/icon/last.png"));
    pause->setIcon(QIcon(":/images/icon/pause.png"));
    play->setIcon(QIcon(":/images/icon/play.png"));
    add->setIcon(QIcon(":/images/icon/add.png"));

    //图标大小
    int btnSize = 80;
    QSize temp(btnSize,btnSize);
    next->setIconSize(temp);
    last->setIconSize(temp);
    pause->setIconSize(temp);
    play->setIconSize(temp);
    add->setIconSize(temp);

    //按钮位置
    int x=60;
    int y=300;
    next->setGeometry(x+180,y,btnSize,btnSize);
    last->setGeometry(x,y,btnSize,btnSize);
    pause->setGeometry(x+85,y-5,btnSize+10,btnSize+10);
    play->setGeometry(x+85,y-5,btnSize+10,btnSize+10);
    add->setGeometry(x+265,y+5,btnSize-10,btnSize-10);
    play->hide();

    //连接按钮信号与对应槽函数
    connect(play,&QPushButton::clicked,this,&MusicWin::playBtnPush);
    connect(pause,&QPushButton::clicked,this,&MusicWin::pauseBtnPush);
    connect(next,&QPushButton::clicked,this,&MusicWin::nextBtnPush);
    connect(last,&QPushButton::clicked,this,&MusicWin::lastBtnPush);
    connect(add,&QPushButton::clicked,this,&MusicWin::addBtnPush);

}

void MusicWin::initMedia()
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);//设置循环模式
    player->setPlaylist(playlist);//获取将播放列表要播放的文件
    player->setVolume(60);//设置音量初始值

    musicName = new QPlainTextEdit(this);
    musicList = new QPlainTextEdit(this);

    //将文本框背景透明化
    QPalette pl = musicName->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(0,0,0,0)));
    musicName->setPalette(pl);
    musicList->setPalette(pl);

    musicList->setGeometry(50,50,350,120);
    musicList->setReadOnly(true);
    musicName->setGeometry(50,180,350,100);
    musicName->setReadOnly(true);

    musicList->setPlainText("播放队列：");
    musicName->setPlainText("当前播放：");
    //当播放文件改变时，改变显示的音乐名↓
    connect(playlist,&QMediaPlaylist::currentMediaChanged,this,&MusicWin::musicChangeEvent);

    volume = new QSlider(this);
    volume->setMaximum(100);//设置最大值
    volume->setMinimum(0);//设置最小值
    volume->setValue(60);//设置初始值
    volume->setSingleStep(5);//设置步长
    volume->setOrientation(Qt::Horizontal);//水平样式
    volume->setTickPosition(QSlider::TicksAbove);//刻度线
    volume->setGeometry(60,400,330,30);//坐标和尺寸
    //当滑块值改变时，同步改变音量↓
    connect(volume,&QSlider::valueChanged,this,&MusicWin::volumeChangeEvent);
}

void MusicWin::playBtnPush()
{
    play->hide();
    pause->show();
    player->pause();
}

void MusicWin::pauseBtnPush()
{
    if(player->state()==QMediaPlayer::PausedState){
        pause->hide();
        play->show();
        player->play();
    }
}

void MusicWin::nextBtnPush()
{
    if(player->state()!=QMediaPlayer::StoppedState)
        playlist->next();

}

void MusicWin::lastBtnPush()
{
    if(player->state()!=QMediaPlayer::StoppedState)
        playlist->previous();

}

void MusicWin::addBtnPush()
{
    //打开文件夹选择音频文件
    QString curPash = "./music";
    QString dlgTitle="选择音乐";
    QString filter="音频文件(*.mp3 *.wav *.wma)mp3文件(*.mp3);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)";
    QStringList fileListTemp = QFileDialog::getOpenFileNames(this,dlgTitle,curPash,filter);

//    QDir dir( "./music");
//    QStringList nameFilters;
//    nameFilters << "*.mp3";
//    QStringList fileListTemp = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

        if(fileListTemp.count()<1)
        return;

    for(int i = 0;i<fileListTemp.count();i++){
        QString aFile = fileListTemp.at(i);
        playlist->addMedia(QUrl::fromLocalFile(aFile));//将文件加入播放列表
        QFileInfo fileInfo(aFile);
        fileList<<aFile;//将文件路径加入文件名列表
        musicList->appendPlainText(QString::number(fileList.count())+"."+(fileListTemp.at(i).section(QRegExp("[/.]"),-2,-2)));
        //fileListTemp.at(i).section(QRegExp("[/.]"),-2,-2))能对文件路径进行分割，将音乐名分割出来
    }

    if(player->state()==QMediaPlayer::StoppedState){
        playlist->setCurrentIndex(0);
        play->show();
        pause->hide();
        player->play();
    }

}

void MusicWin::musicChangeEvent()
{
    musicName->setPlainText("当前播放：");
    musicName->appendPlainText((fileList.at(playlist->currentIndex()).section(QRegExp("[/.]"),-2,-2)));
}

void MusicWin::volumeChangeEvent()
{
    player->setVolume(volume->value());
}
