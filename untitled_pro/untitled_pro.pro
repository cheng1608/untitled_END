QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bossAlex.cpp \
    enemyBase.cpp \
    enemyExplosiveBase.cpp \
    enemyExplosiveSkeleton.cpp \
    enemyFire.cpp \
    enemyFireBubble.cpp \
    enemyWizard.cpp \
    enemyZomble.cpp \
    enemyZombleEarth.cpp \
    enemyZombleEarthGiant.cpp \
    enemyZombleFire.cpp \
    enemyZombleFireGiant.cpp \
    enemyZombleWind.cpp \
    enemyZombleWindGiant.cpp \
    gameEngine.cpp \
    heartLabel.cpp \
    magicBall.cpp \
    magicBase.cpp \
    magicFire.cpp \
    magicFireBallNomal.cpp \
    magicIce.cpp \
    magicIceBall.cpp \
    magicWater.cpp \
    magicWaterBall.cpp \
    main.cpp \
    gameWidget.cpp \
    player.cpp \
    startMenu.cpp

HEADERS += \
    bossAlex.h \
    enemyBase.h \
    enemyExplosiveBase.h \
    enemyExplosiveSkeleton.h \
    enemyFire.h \
    enemyFireBubble.h \
    enemyWizard.h \
    enemyZomble.h \
    enemyZombleEarth.h \
    enemyZombleEarthGiant.h \
    enemyZombleFire.h \
    enemyZombleFireGiant.h \
    enemyZombleWind.h \
    enemyZombleWindGiant.h \
    gameEngine.h \
    gameWidget.h \
    heartLabel.h \
    magicBall.h \
    magicBase.h \
    magicFire.h \
    magicFireBallNomal.h \
    magicIce.h \
    magicIceBall.h \
    magicWater.h \
    magicWaterBall.h \
    player.h \
    startMenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
