QT       += core gui
QT += gui
QT += network
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
    card.cpp \
    connecttoserver.cpp \
    deck.cpp \
    forgetpassword.cpp \
    ground.cpp \
    history.cpp \
    main.cpp \
    login.cpp \
    maindatabase.cpp \
    massagelose.cpp \
    massagewin.cpp \
    menu.cpp \
    playclient.cpp \
    rules.cpp \
    rules2.cpp \
    rules3.cpp \
    rules4.cpp \
    rules5.cpp \
    setting.cpp \
    singup.cpp \
    skullgame.cpp \
    timer.cpp \
    user.cpp

HEADERS += \
    card.h \
    connecttoserver.h \
    deck.h \
    forgetpassword.h \
    ground.h \
    history.h \
    login.h \
    maindatabase.h \
    massagelose.h \
    massagewin.h \
    menu.h \
    playclient.h \
    rules.h \
    rules2.h \
    rules3.h \
    rules4.h \
    rules5.h \
    setting.h \
    singup.h \
    skullgame.h \
    timer.h \
    user.h

FORMS += \
    forgetpassword.ui \
    history.ui \
    login.ui \
    massagelose.ui \
    massagewin.ui \
    menu.ui \
    playclient.ui \
    rules.ui \
    rules2.ui \
    rules3.ui \
    rules4.ui \
    rules5.ui \
    setting.ui \
    singup.ui \
    skullgame.ui \
    timer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc \
    rules_picture.qrc

DISTFILES += \
    login icon.jpg
