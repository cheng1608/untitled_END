
#include "magicBall.h"

QTimer *MagicBall::attackTimer = nullptr;

MagicBall::MagicBall(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, m_scene(scene), m_speed(speed_), m_damage(damage_), m_penetration(penetration_)
{
    // 设置初始位置和角度
    setPos(pos_);
    setRotation(angle_);

    // 计时器绑定
    connect(attackTimer, &QTimer::timeout, this, &MagicBall::enemyHitCheck);
    connect(attackTimer, &QTimer::timeout, this, &MagicBall::move);

    m_scene->addItem(this);

    hurtCount = 0;
}


void MagicBall::enemyHitCheck(){
    QList<QGraphicsItem*> coItems = this->collidingItems();
    for (QGraphicsItem* item : coItems) {
        EnemyBase* enemy = dynamic_cast<EnemyBase*>(item);
        if (enemy) {
            bool flag = false;
            for (auto p : hurtEnemyList) {
                if (p == enemy) flag = true;
            }
            if (flag) return;
            enemy->hurt(m_damage);
            hurtEnemyList.append(enemy);
            hurtCount++;
            if (hurtCount > m_penetration){
                m_scene->removeItem(this);
                deleteLater();
            }
            return;
        }
    }
    if (x() < 0 || x() > 4000 || y() < 0 || y() > 2400) deleteLater();
}

void MagicBall::move()
{
    // 获取当前朝向角度
    qreal angle = rotation();

    // 将角度转换为弧度
    qreal radian = qDegreesToRadians(angle);

    // 计算出当前移动的距离
    qreal distance = m_speed;
    // 计算出下一个位置
    qreal dy = distance * qSin(radian);
    qreal dx = distance * qCos(radian);

    // 移动到下一个位置
    moveBy(dx, dy);
}

