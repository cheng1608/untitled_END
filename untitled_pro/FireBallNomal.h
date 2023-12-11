#ifndef FIREBALLNOMAL_H
#define FIREBALLNOMAL_H

#include "FireBallBase.h"

class FireBallNomal : public FireBallBase
{
    Q_OBJECT
public:
    explicit FireBallNomal
        (QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration, QGraphicsScene *scene, QObject *parent = nullptr);
};

#endif // FIREBALLNOMAL_H
