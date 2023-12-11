#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "player.h"

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QSoundEffect>
#include <QUrl>
#include <qmath.h>
#include<QRandomGenerator>

class EnemyBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnemyBase(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
    virtual void hurt(qreal damage);
    virtual void frozen();
    static QTimer *enemyTimer;
    void updateHealthBar();
signals:
    void enemyDeath();
    void bossDeath();
protected:

    void hurtReload();
    void frozenReload();
    virtual void hitBoxCheck();
    virtual void death();
    virtual void load()=0;
    virtual void Pathfinding()=0;


    QRectF mapbounds;
    int timeBuffer;//时间缓冲器，用来实现一些寻路之类的时间推迟
    Player *enemyPlayer;
    QGraphicsScene *enemyScene;
    qreal speed;
    qreal maxHP;
    qreal nowHP;
    QGraphicsRectItem* healthBar;//血条
    QGraphicsRectItem* healthBarBackground;//血条后面的框框
    int xp;

    bool isHurt=0;
    QTimer hurtTimer;

    bool canFrozen=1;
    bool isFrozen=0;
    QTimer frozenTimer;


};

#endif // ENEMYBASE_H
