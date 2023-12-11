#include "enemyBase.h"


QRectF mapbounds = QRectF(0, 0, 3800, 2200);

QTimer* EnemyBase::enemyTimer=nullptr;


EnemyBase::EnemyBase(Player *pl, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, enemyPlayer(pl), enemyScene(scene)
{
    connect(this, &EnemyBase::enemyDeath, this, &EnemyBase::death);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::Pathfinding);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::load);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::hitBoxCheck);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::updateHealthBar);


    connect(&hurtTimer, &QTimer::timeout, this, &EnemyBase::hurtReload);
    connect(&frozenTimer, &QTimer::timeout, this, &EnemyBase::frozenReload);
    connect(this, &EnemyBase::enemyDeath, this, &EnemyBase::death);


    // 创建血条框框
    healthBarBackground = new QGraphicsRectItem(this);
    healthBarBackground->setPen(Qt::NoPen);
    healthBarBackground->setBrush(Qt::black);
    healthBarBackground->setRect(0, 0,104,14); // 框框初始长度,宽度
    healthBarBackground->setPos(51, 18); // 框框位置在血条后面
    // 创建血条
    healthBar = new QGraphicsRectItem(this);
    healthBar->setPen(Qt::NoPen);
    healthBar->setBrush(Qt::green);
    healthBar->setRect(0, 0,100,10); // 血条初始长度,宽度
    healthBar->setPos(53, 20); // 血条位置
}

void EnemyBase::hurt(qreal damage){
    nowHP -= damage;
    isHurt = true;
    hurtTimer.start(50);
    if (nowHP <= 0) {
        emit enemyDeath();
    }
}

void EnemyBase::frozen(){
    if(!canFrozen){
        return;
    }
    isFrozen=true;
    frozenTimer.start(800);//冰冻的时间
}

void EnemyBase::hitBoxCheck(){
    if (collidesWithItem(enemyPlayer)){
        enemyPlayer->hurt();
    }
}

void EnemyBase::death(){
    enemyScene->removeItem(this);
    deleteLater();
}

void EnemyBase::hurtReload(){
    isHurt = false;
    hurtTimer.stop();
}

void EnemyBase::frozenReload(){//冰冻QTimer到了解除冰冻状态
    isFrozen = false;
    hurtTimer.stop();
}

void EnemyBase::updateHealthBar(){
    // 新长度
    qreal newWidth = (nowHP / maxHP) * 100;
    if(newWidth<70)healthBar->setBrush(Qt::yellow);
    if(newWidth<35)healthBar->setBrush(Qt::red);
    // 更新长度
    healthBar->setRect(0, 0, newWidth, 10);
}




