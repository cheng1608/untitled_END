#ifndef ENEMYZOMBLEFIRE_H
#define ENEMYZOMBLEFIRE_H

#include "enemyBase.h"
#include"enemyFire.h"

class EnemyZombleFire : public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyZombleFire(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

private:
    QMovie *m_movie;
    int timeBuffer;

    void load();
    void Pathfinding();
    void FireSkill();
    int attackCount;
    const int attackCeil;
};

#endif // ENEMYZOMBLEFIRE_H
