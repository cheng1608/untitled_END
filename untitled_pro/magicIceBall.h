#ifndef MAGICICEBALL_H
#define MAGICICEBALL_H


#include "magicBall.h"

class magicIceBall : public MagicBall
{
    Q_OBJECT
public:
    explicit magicIceBall
        (QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration, QGraphicsScene *scene, QObject *parent = nullptr);

    void enemyHitCheck()override;
};

#endif // MAGICICEBALL_H
