
#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include "magicBall.h"
#include "player.h"

class enemyFire : public MagicBall
{
    Q_OBJECT
public:
    explicit enemyFire(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, Player *pl, QObject *parent = nullptr);
private:
    void playerHitCheck();
    Player *enemyPlayer;
};

#endif // BULLETENEMY_H
