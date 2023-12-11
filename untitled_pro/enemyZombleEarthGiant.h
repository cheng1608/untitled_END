#ifndef ENEMYZOMBLEEARTHGIANT_H
#define ENEMYZOMBLEEARTHGIANT_H

#include"enemyZombleEarth.h"

class EnemyZombleEarthGiant:public EnemyZombleEarth
{
public:
    explicit EnemyZombleEarthGiant(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
protected:
    void load()override;
};

#endif // ENEMYZOMBLEEARTHGIANT_H
