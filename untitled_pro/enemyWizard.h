#ifndef ENEMYWIZARD_H
#define ENEMYWIZARD_H


#include "enemyBase.h"
#include"enemyFire.h"
#include"enemyFireBubble.h"

class EnemyWizard : public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyWizard(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

private:
    QMovie *m_movie;
    int timeBuffer;

    void load();
    void Pathfinding();
    void FireSkill();
    int attackCount;
    const int attackCeil;
};

#endif // ENEMYWIZARD_H
