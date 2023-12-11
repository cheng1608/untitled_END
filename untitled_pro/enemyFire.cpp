
#include "enemyFire.h"

enemyFire::enemyFire(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, Player *pl, QObject *parent)
    : MagicBall{pos_, angle_, speed_, damage_ ,penetration_, scene, parent}
{
    setPixmap(QPixmap(":/images/enemyFire.png"));
    setTransformOriginPoint(boundingRect().center());
    enemyPlayer = pl;
    disconnect(attackTimer, &QTimer::timeout, this, &enemyFire::enemyHitCheck);
    connect(attackTimer, &QTimer::timeout, this, &enemyFire::playerHitCheck);
    setZValue(114);
}

void enemyFire::playerHitCheck()
{
    if (collidesWithItem(enemyPlayer)) {
        enemyPlayer->hurt();
        m_scene->removeItem(this);
        deleteLater();
    }
    if (x() < 0 || x() > 4000 || y() < 0 || y() > 2400) deleteLater();
}

