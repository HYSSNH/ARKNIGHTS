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

SOURCES += \
    bullet.cpp \
    choose.cpp \
    enemy.cpp \
    gamescene.cpp \
    legend_location.cpp \
    legends.cpp \
    lose.cpp \
    main.cpp \
    selectbutton.cpp \
    selectbutton2.cpp \
    user.cpp \
    waypoint.cpp \
    widget.cpp \
    win.cpp \
    yonghu.cpp

HEADERS += \
    bullet.h \
    choose.h \
    enemy.h \
    gamescene.h \
    legend_location.h \
    legends.h \
    lose.h \
    selectbutton.h \
    selectbutton2.h \
    user.h \
    utility.h \
    waypoint.h \
    widget.h \
    win.h \
    yonghu.h

FORMS += \
    choose.ui \
    gamescene.ui \
    lose.ui \
    user.ui \
    widget.ui \
    win.ui \
    yonghu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc

DISTFILES +=
