#include "enemyZombleWind.h"

EnemyZombleWind::EnemyZombleWind(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{pl, scene, parent}{
    // 加载动画
    m_movie = new QMovie(":/images/pic/ZombleWind.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    timeBuffer=0;
    // 基本数据
    maxHP=11;
    nowHP = 11;
    xp = 1;
    speed = 4;
    isHighSpeed=0;
    currentSpeed=LowSpeed;
}

void EnemyZombleWind::Pathfinding (){//写不一样的
    if(isFrozen)return;
    switch (currentSpeed){
    case HighSpeed:
        run();
        break;
    case LowSpeed:
        walk();
        break;
    }
}

void EnemyZombleWind::run(){
    if (!enemyPlayer)return;

    // 计算到Player的方向
    QLineF line(pos(), enemyPlayer->pos());
    // 计算出移动的距离和方向
    qreal newspeed=7;//加速

    qreal dx = cos(line.angle() * M_PI / 180) * newspeed;
    qreal dy = -sin(line.angle() * M_PI / 180) * newspeed;
    QPointF newPos = pos() + QPointF(dx, dy);

    if (mapbounds.contains(newPos)) {
        if (dx > 0) {
            newPos = pos() + QPointF(newspeed, 0);
        }
        else {
            newPos = pos() + QPointF(-newspeed, 0);
        }
    }
    if (mapbounds.contains(newPos)) {
        if (dy > 0) {
            newPos = pos() + QPointF(0, newspeed);
        }else {
            newPos = pos() + QPointF(0, -newspeed);
        }
    }
    if (mapbounds.contains(newPos)){
        newPos = pos() + QPointF(0, 0);
    }

    setPos(newPos);

    timeBuffer++;
    if(timeBuffer>300){
        currentSpeed=LowSpeed;
        timeBuffer=0;
    }
}

void EnemyZombleWind::walk(){
    if (!enemyPlayer)return;

    // 到Player的方向
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

    setPos(newPos);

    timeBuffer++;
    if(timeBuffer>400){
        currentSpeed=HighSpeed;
        timeBuffer=0;
    }
}

void EnemyZombleWind::load(){
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

    if (currentSpeed==HighSpeed&&isFrozen==false) {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y) {
            uchar *line = pixels + y * bytesPerLine;
            for (int x = 0; x < width; ++x) {
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0) {
                    line[x * 4] = (line[x * 4] + 224) / 2;  // R通道
                    line[x * 4 + 1] = (line[x * 4 + 1] + 240) / 2;  // G通道
                    line[x * 4 + 2] = (line[x * 4 + 2] + 255) / 2;  // B通道
                    line[x * 4 + 3] = qMin(alpha + 64, 255);  // 透明度设置为稍稍半透明
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
    // 设置显示图像
    setPixmap(pixmap);
}
