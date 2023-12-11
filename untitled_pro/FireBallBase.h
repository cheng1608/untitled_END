
#ifndef FIREBALLBASE_H
#define FIREBALLBASE_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>

#include "enemyBase.h"


class FireBallBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit FireBallBase(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, QObject *parent = nullptr);

    static QTimer *attackTimer;

signals:

protected:
    void enemyHitCheck();
    virtual void move();
    QGraphicsScene *m_scene;
    qreal m_speed;
    qreal m_damage;
    int m_penetration;
    QList<EnemyBase*> hurt_enemy_list;
    int hurt_count;
};

#endif // FIREBALLBASE_H
