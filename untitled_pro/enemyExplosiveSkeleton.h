
#ifndef ENEMYEXPLOSIVESKELETON_H
#define ENEMYEXPLOSIVESKELETON_H

#include "enemyExplosiveBase.h"

class EnemyExplosiveSkeleton : public EnemyExplosiveBase
{
    Q_OBJECT
public:
    explicit EnemyExplosiveSkeleton(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
private:
    void Pathfinding()override;
    void load() override;
    void explode() override;

    QMovie* m_movie;
    QMovie *fx_explosion;
};

#endif // ENEMYEXPLOSIVESKELETON_H
