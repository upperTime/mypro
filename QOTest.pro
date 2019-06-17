#-------------------------------------------------
#
# Project created by QtCreator 2019-06-16T19:08:05
#
#-------------------------------------------------

QT       += core gui opengl

win32-g++:!contains(QMAKE_HOST.arch,x86_64){
    LIBS+="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\GlU32.Lib"
    LIBS+="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\OpenGL32.Lib"
}else{
     LIBS+="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\x64\GlU32.Lib"
    LIBS+="C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\x64\OpenGL32.Lib"
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QOTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        mainwindow.cpp \
    maze.cpp \
    main.cpp

HEADERS += \
        mainwindow.h \
    maze.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
