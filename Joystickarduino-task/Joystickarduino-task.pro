QT       += core gui
QT       += core gui serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp \
    threadevent.cpp

HEADERS += \
    dialog.h \
    threadevent.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




unix|win32: LIBS += -L$$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/lib/x64/ -lSDL2

INCLUDEPATH += $$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/include
DEPENDPATH += $$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/lib/x64/ -lSDL2main
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/lib/x64/ -lSDL2main
else:unix: LIBS += -L$$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/lib/x64/ -lSDL2main

INCLUDEPATH += $$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/include
DEPENDPATH += $$PWD/../SDL2-devel-2.0.12-VC/SDL2-2.0.12/include
