#ifndef ENEMYZOMBLE_H
#define ENEMYZOMBLE_H

#include"enemyBase.h"

class EnemyZomble:public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyZomble(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
private:
    QMovie* m_movie;
    void load() ;
    void Pathfinding ();

};

#endif // ENEMYZOMBLE_H
