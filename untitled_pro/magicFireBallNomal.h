#ifndef MAGICFIREBALLNOMAL_H
#define MAGICFIREBALLNOMAL_H

#include "magicBall.h"

class magicFireBallNomal : public MagicBall
{
    Q_OBJECT
public:
    explicit magicFireBallNomal
        (QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration, QGraphicsScene *scene, QObject *parent = nullptr);
};

#endif // MAGICFIREBALLNOMAL_H
