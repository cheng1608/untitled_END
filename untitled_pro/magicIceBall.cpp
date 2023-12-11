#include "magicIceBall.h"

magicIceBall::magicIceBall
    (QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, QObject *parent)
    : MagicBall{pos_, angle_, speed_, damage_, penetration_, scene, parent}
{
    setPixmap(QPixmap(":/images/ice.png"));
}

void magicIceBall::enemyHitCheck(){
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
            enemy->frozen();
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
