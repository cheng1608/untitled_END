
#include "enemyExplosiveSkeleton.h"

EnemyExplosiveSkeleton::EnemyExplosiveSkeleton(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyExplosiveBase{pl, scene, parent}
{

    m_movie = new QMovie(":/images/pic/skeleton.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    // 基本数据
    explosion_range = 32;
    explosion_damage = 50;
    speed = 3;
    maxHP=10;
    nowHP = 10;

    canFrozen=0;

    setTransformOriginPoint(boundingRect().center());
    fx_explosion = new QMovie(":/images/fx/BOOM_small.gif");
    fx_explosion->setParent(this);
}

void EnemyExplosiveSkeleton::load(){
    QImage img(m_movie->currentImage());

    if (isHurt) {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y) {
            uchar *line = pixels + y * bytesPerLine;
            for (int x = 0; x < width; ++x) {
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0) {
                    line[x * 4] = 255;
                    line[x * 4 + 1] = 255;
                    line[x * 4 + 2] = 255;
                }
            }
        }
    }

    if (isFrozen) {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y) {
            uchar *line = pixels + y * bytesPerLine;
            for (int x = 0; x < width; ++x) {
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0) {
                    //  变蓝
                    line[x * 4] = qMin<uchar>(line[x * 4], 255);
                    line[x * 4 + 1] = qMin<uchar>(line[x * 4 + 1], 255);
                    line[x * 4 + 2] = qMin<uchar>(line[x * 4 + 2] + 100, 255);
                    line[x * 4 + 3] = qMin<uchar>(alpha + 64, 255);
                }
            }
        }
    }
    // 确定角度
    qreal angle = QLineF(pos(), enemyPlayer->pos()).angle();



    QPixmap pixmap = QPixmap::fromImage(img);
    // 镜像处理
    if ((angle > 90 && angle < 270) || (angle < -90 && angle > -270)) {
        //水平镜像
        pixmap = pixmap.transformed(QTransform().scale(-1, 1));
    }
    QPixmap newPixmap(pixmap);

    QTransform transform;
    transform.scale(2, 2);
    // 设置显示图像
    setPixmap(newPixmap);
}

void EnemyExplosiveSkeleton::Pathfinding (){
    if(isFrozen)return;
    if (!enemyPlayer)return;

    // 计算出 Enemy 到 Player 的方向
    QLineF line(pos(), enemyPlayer->pos());
    // 计算出移动的距离和方向
    qreal dx = cos(line.angle() * M_PI / 180) * speed;
    qreal dy = -sin(line.angle() * M_PI / 180) * speed;
    QPointF newPos = pos() + QPointF(dx, dy);

    if (mapbounds.contains(newPos)) {
        if (dx > 0) {
            newPos = pos() + QPointF(speed, 0);
        }
        else {
            newPos = pos() + QPointF(-speed, 0);
        }
    }
    if (mapbounds.contains(newPos)) {
        if (dy > 0) {
            newPos = pos() + QPointF(0, speed);
        }else {
            newPos = pos() + QPointF(0, -speed);
        }
    }
    if (mapbounds.contains(newPos)){
        newPos = pos() + QPointF(0, 0);
    }
    // 移动 Enemy
    setPos(newPos);
}

void EnemyExplosiveSkeleton::explode()
{
    disconnect(enemyTimer, &QTimer::timeout, this, &EnemyExplosiveSkeleton::updateHealthBar);
    delete healthBar;
    delete healthBarBackground;
    disconnect(enemyTimer, &QTimer::timeout, this, &EnemyExplosiveSkeleton::load);
    disconnect(enemyTimer, &QTimer::timeout, this, &EnemyExplosiveSkeleton::Pathfinding);
    connect(enemyTimer, &QTimer::timeout, this, &EnemyExplosiveSkeleton::enemyHitCheck);//爆炸伤害绑定
    disconnect(this, &EnemyBase::enemyDeath, this, &EnemyExplosiveSkeleton::death);

    fx_explosion->start();

    moveBy(30, 30);//移动爆炸位置

    setPixmap(fx_explosion->currentPixmap());
    setTransformOriginPoint(boundingRect().center());
    connect(enemyTimer, &QTimer::timeout, this, [=]{
        disconnect(enemyTimer, &QTimer::timeout, this, &EnemyExplosiveSkeleton::hitBoxCheck);
        disconnect(enemyTimer, &QTimer::timeout, this, &EnemyExplosiveSkeleton::enemyHitCheck);
    });
    connect(fx_explosion, &QMovie::frameChanged, this, [=](){
        setPixmap(fx_explosion->currentPixmap());
    });
    connect(fx_explosion, &QMovie::finished, this, [=](){
        enemyScene->removeItem(this);
        deleteLater();
    });
}

