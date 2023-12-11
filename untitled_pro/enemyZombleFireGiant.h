#ifndef ENEMYZOMBLEFIREGIANT_H
#define ENEMYZOMBLEFIREGIANT_H

#include "enemyBase.h"

class EnemyZombleFireGiant:public EnemyBase
{
public:
    explicit EnemyZombleFireGiant(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
private:
    QMovie *m_movie;
    int timeBuffer;

    void load();
    void Pathfinding();
    void FireSkill();
    int attack_count;
    const int attack_ceil;
};

#endif // ENEMYZOMBLEFIREGIANT_H
