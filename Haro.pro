QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += multimedia

SOURCES += \
    dresswin.cpp \
    main.cpp \
    haro.cpp \
    musicwin.cpp \
    setwin.cpp

HEADERS += \
    dresswin.h \
    haro.h \
    musicwin.h \
    setwin.h

FORMS += \
    dresswin.ui \
    haro.ui \
    musicwin.ui \
    setwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    images/appearance/body/Gundam_body.png \
    images/movement/blink/动作1.png \
    images/movement/blink/动作2.png \
    images/movement/blink/动作3.png \
    images/movement/blink/动作4.png \
    images/movement/blink/动作5.png \
    images/movement/blink/动作6.png
