QT       += core gui widgets

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
    angry.cpp \
    assassin.cpp \
    barrier.cpp \
    breakinglimits.cpp \
    card.cpp \
    choosecardscene.cpp \
    chooselevelscene.cpp \
    defense.cpp \
    devildragon.cpp \
    dircard.cpp \
    doublestrike.cpp \
    fightscene.cpp \
    hammer.cpp \
    hero.cpp \
    hitting.cpp \
    ignore.cpp \
    main.cpp \
    metallization.cpp \
    monster.cpp \
    muscle.cpp \
    pushbutton_press.cpp \
    role.cpp \
    rolescene.cpp \
    saberdragon.cpp \
    sakyamuni.cpp \
    slim.cpp \
    startscene.cpp \
    strike.cpp \
    undircard.cpp \
    warrior.cpp

HEADERS += \
    angry.h \
    assassin.h \
    barrier.h \
    breakinglimits.h \
    card.h \
    choosecardscene.h \
    chooselevelscene.h \
    defense.h \
    devildragon.h \
    dircard.h \
    doublestrike.h \
    fightscene.h \
    hammer.h \
    hero.h \
    hitting.h \
    ignore.h \
    metallization.h \
    monster.h \
    muscle.h \
    pushbutton_press.h \
    role.h \
    rolescene.h \
    saberdragon.h \
    sakyamuni.h \
    slim.h \
    startscene.h \
    strike.h \
    undircard.h \
    warrior.h

FORMS += \
    chooselevelscene.ui \
    startscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
