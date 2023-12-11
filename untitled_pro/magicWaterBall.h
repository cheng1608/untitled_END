#ifndef MAGICWATERBALL_H
#define MAGICWATERBALL_H


#include "magicBall.h"

class magicWaterBall : public MagicBall
{
    Q_OBJECT
public:
    explicit magicWaterBall
        (QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration, QGraphicsScene *scene, QObject *parent = nullptr);
};

#endif // MAGICWATERBALL_H
