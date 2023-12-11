#include "enemyFireBubble.h"

enemyFireBubble::enemyFireBubble(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, Player *pl, QObject *parent)
    : MagicBall{pos_, angle_, speed_, damage_ ,penetration_, scene, parent}
{
    setPixmap(QPixmap(":/images/enemyFireBubble.png"));
    setTransformOriginPoint(boundingRect().center());
    enemyPlayer = pl;
    disconnect(attackTimer, &QTimer::timeout, this, &enemyFireBubble::enemyHitCheck);
    connect(attackTimer, &QTimer::timeout, this, &enemyFireBubble::playerHitCheck);
    connect(attackTimer, &QTimer::timeout, this, &enemyFireBubble::explodeCheck);
    setZValue(114);

    exploreCountdown=400;
}

void enemyFireBubble::playerHitCheck()
{
    if (collidesWithItem(enemyPlayer)) {
        enemyPlayer->hurt();
        m_scene->removeItem(this);
        deleteLater();
    }
    if (x() < 0 || x() > 4000 || y() < 0 || y() > 2400){
        m_scene->removeItem(this);
        deleteLater();
    }
}

void enemyFireBubble::explodeCheck(){
    exploreCountdown--;
    if(exploreCountdown<0){
        m_scene->removeItem(this);
        deleteLater();
    }
}

void enemyFireBubble::move()
{
    QPointF fireballPos = pos();
    QPointF playerPos = enemyPlayer->pos();

    qreal targetAngle = qAtan2(playerPos.y() - fireballPos.y(), playerPos.x() - fireballPos.x());
    qreal angle = qRadiansToDegrees(targetAngle);

    setRotation(angle);

    qreal radian = qDegreesToRadians(angle);

    qreal distance = m_speed;

    qreal dy = distance * qSin(radian);
    qreal dx = distance * qCos(radian);

    moveBy(dx, dy);
}




