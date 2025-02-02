QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/Memory.cpp \
    ../src/RK3588Thermal.cpp \
    ui_src/MemoryLabel.cpp \
    ui_src/ThermalLabel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../src/Memory.h \
    ../src/RK3588Thermal.h \
    ui_src/MemoryLabel.h \
    ui_src/ThermalLabel.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += ../src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
