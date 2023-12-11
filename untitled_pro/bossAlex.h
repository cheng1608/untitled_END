#ifndef BOSSALEX_H
#define BOSSALEX_H


// BossBase.h


#include <QObject>
#include <QGraphicsScene>
#include "Player.h"
#include "enemyBase.h"
#include"enemyFire.h"

class BossAlex : public EnemyBase
{
    Q_OBJECT
public:
    explicit BossAlex(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

    enum BossState
    {
        Standing,
        Walking,
    };


protected:

    void Stand();
    void Walk();
    void Attack();
    void NormalAttack();
    void SpecialAttack();
    void NearDeathAttack();
    void recover();

    void Pathfinding()override;
    void load()override ;
    void hurt(qreal damage)override;
    void frozen()override;
    void death()override;
private:
    QMovie* m_movie;
    qreal bossHealthPercentage;
    bool isWalking;
    bool isAttacking;

    int attack_count;
    bool isBusy;



    BossState currentState;
};

// 省略其余部分


#endif // BOSSALEX_H
