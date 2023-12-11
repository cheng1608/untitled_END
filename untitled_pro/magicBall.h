
#ifndef MAGICBALL_H
#define MAGICBALL_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>

#include "enemyBase.h"


class MagicBall : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MagicBall(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, QObject *parent = nullptr);

    static QTimer *attackTimer;

signals:

protected:
    virtual void enemyHitCheck();
    virtual void move();
    QGraphicsScene *m_scene;
    qreal m_speed;
    qreal m_damage;
    int m_penetration;
    QList<EnemyBase*> hurtEnemyList;
    int hurtCount;
};

#endif // MAGICBALL_H
