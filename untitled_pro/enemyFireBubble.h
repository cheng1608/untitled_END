#ifndef ENEMYFIREBUBBLE_H
#define ENEMYFIREBUBBLE_H

#include "magicBall.h"
#include "player.h"
#include"enemyFire.h"

class enemyFireBubble : public MagicBall
{
    Q_OBJECT
public:
   explicit enemyFireBubble(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, Player *pl, QObject *parent = nullptr);
private:
    void playerHitCheck();
    void explodeCheck ();
    void move()override;

    Player *enemyPlayer;
    int exploreCountdown;
};

#endif // ENEMYFIREBUBBLE_H
