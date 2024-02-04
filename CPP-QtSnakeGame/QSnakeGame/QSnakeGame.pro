QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    SnakyImpl.cpp

HEADERS += \
    mainwindow.h \
    Snaky.h \
    SnakyImpl.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    QSnakeGame_en_150.ts

RC_ICONS = Snaky.ico

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
