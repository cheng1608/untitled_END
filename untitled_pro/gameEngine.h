#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QSettings>
#include <QFontDatabase>
#include <QApplication>
#include <QSoundEffect>
#include<QSettings>

#include "heartLabel.h"
#include"player.h"
#include "magicBase.h"
#include"bossAlex.h"

class GameEngine : public QGraphicsView
{
    Q_OBJECT

public:
    GameEngine(QString magic);
    void load(); // 加载贴图
    void updateBackground();
    void endgame_lose();
    void endgame_win();

signals:
    void Endgame();

private:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void setHealthBar();//血条更新
    void enemyGenerator();//怪物生成器
    int enemyNumberNote=0;//怪物数量初始记录

    QTimer *mainTimer;//唯一的主时钟

    Player *mainPlayer;
    MagicBase *mainMagic;
    QGraphicsScene *mainScene;
    QGraphicsScene *end_scene;
    QGraphicsPixmapItem *mainBackground;

    bool isFightingBoss=0;

    QPointF mousePos;
    QString magic;
    
    QList<HeartLabel*> heartList;

    // 倒计时
    int countdown_count=0;
    QGraphicsTextItem *countdown_text;
    QTime countdown_time;
    void updateCountdown();

    void phaseUp(); // 游戏阶段
    int phase=0;
    int phase_count=0;//游戏阶段更新的缓冲时钟
    int enemyNumberMax=5;
    qreal enemyZombleRate;//各种怪物比例
    qreal enemyZombleFireRate;
    qreal enemyZombleEarthRate;
    qreal enemyZombleWindRate;
    qreal enemyWizardRate;
    qreal enemyExplosiveSkeletonRate;
    qreal enemyBeGiantRate;//巨人化比例
};

#endif // GAMEENGINE_H
