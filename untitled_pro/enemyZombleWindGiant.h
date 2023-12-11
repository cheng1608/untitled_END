#ifndef ENEMYZOMBLEWINDGIANT_H
#define ENEMYZOMBLEWINDGIANT_H


#include"enemyZombleWind.h"

class EnemyZombleWindGiant:public EnemyZombleWind
{
public:
    explicit EnemyZombleWindGiant(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
protected:
    void load()override;
};

#endif // ENEMYZOMBLEWINDGIANT_H
