
#include "fire.h"

Fire::Fire(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, Player *pl, QObject *parent)
    : FireBallBase{pos_, angle_, speed_, damage_ ,penetration_, scene, parent}
{
    setPixmap(QPixmap(":/images/enemyFire.jpg"));
    setTransformOriginPoint(boundingRect().center());
    m_player = pl;
    disconnect(m_timer_static, &QTimer::timeout, this, &Fire::enemyHitCheck);
    connect(m_timer_static, &QTimer::timeout, this, &Fire::playerHitCheck);
    setZValue(114);
}

void Fire::playerHitCheck()
{
    if (collidesWithItem(m_player)) {
        m_player->hurt();
        m_scene->removeItem(this);
        deleteLater();
    }
    if (x() < 0 || x() > 4800 || y() < 0 || y() > 2700) deleteLater();
}

