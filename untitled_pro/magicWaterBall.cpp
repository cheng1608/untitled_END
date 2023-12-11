#include "magicWaterBall.h"

magicWaterBall::magicWaterBall
    (QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, QObject *parent)
    : MagicBall{pos_, angle_, speed_, damage_, penetration_, scene, parent}
{
    setPixmap(QPixmap(":/images/waterBallSmall.png"));
}
