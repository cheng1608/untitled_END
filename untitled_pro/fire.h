
#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include "FireBallBase.h"
#include "player.h"

class Fire : public FireBallBase
{
    Q_OBJECT
public:
    explicit Fire(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, Player *pl, QObject *parent = nullptr);

private:
    void playerHitCheck();
    Player *m_player;
};

#endif // BULLETENEMY_H
