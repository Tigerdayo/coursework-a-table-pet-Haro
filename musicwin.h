#ifndef MUSICWIN_H
#define MUSICWIN_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include<QPushButton>
#include<QFileDialog>
#include<QPlainTextEdit>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>
#include<QSlider>

namespace Ui {
class MusicWin;
}

class MusicWin : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWin(QWidget *parent = nullptr);
    ~MusicWin();

private:
    Ui::MusicWin *ui;

    QPushButton *next;//切换下一首按钮

    QPushButton *last;//切换上一首按钮

    QPushButton *pause;//暂停播放按钮

    QPushButton *play;//开始播放按钮

    QPushButton *add;//添加歌曲按钮

    QPlainTextEdit *musicName;//显示当前播放音乐名

    QPlainTextEdit *musicList;//显示音乐列表

    QMediaPlayer * player;//多媒体播放器

    QMediaPlaylist * playlist;//播放列表

    QSlider * volume;//音量滑动条

    QStringList fileList;//文件名列表

    void initBtn();//初始化按钮

    void initMedia();//初始化多媒体

    void playBtnPush();//各按钮事件↓

    void pauseBtnPush();

    void nextBtnPush();

    void lastBtnPush();

    void addBtnPush();

    void musicChangeEvent();//切换音乐事件

    void volumeChangeEvent();//调节音量事件
};

#endif // MUSICWIN_H
