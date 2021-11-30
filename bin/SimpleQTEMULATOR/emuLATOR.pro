QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    4_Bit_High_Level.cpp \
    4_Bit_Low_Level.cpp \
    8_Bit_High_Level.cpp \
    components/alu.cpp \
    components/counter.cpp \
    components/decoder.cpp \
    components/lcd.cpp \
    components/ram.cpp \
    components/register.cpp \
    components/shiftreg.cpp \
    components/srlatch.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    components/alu.h \
    components/counter.h \
    components/decoder.h \
    components/lcd.h \
    components/ram.h \
    components/register.h \
    components/shiftreg.h \
    components/srlatch.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Aqua.qss
