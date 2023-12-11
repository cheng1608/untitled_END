#ifndef ENEMYZOMBLEWIND_H
#define ENEMYZOMBLEWIND_H

#include"enemyBase.h"

class EnemyZombleWind:public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyZombleWind(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

    enum speedState
    {
        HighSpeed,
        LowSpeed,
    };
protected:
    QMovie* m_movie;
    speedState currentSpeed;
    bool isHighSpeed;

    void load() ;
    void Pathfinding ();

    void run();
    void walk();

};



#endif // ENEMYZOMBLEWIND_H
