#ifndef ENEMYZOMBLEEARTH_H
#define ENEMYZOMBLEEARTH_H

#include"enemyBase.h"

class EnemyZombleEarth:public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyZombleEarth(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

    enum earthState{
        notEarth,
        isEarth
    };

protected:
    QMovie* m_movie;

    void load() override;
    void Pathfinding ()override;
    void hurt(qreal damage)override;

    earthState nowState=notEarth;
    void earthSkill();
};

#endif // ENEMYZOMBLEEARTH_H
