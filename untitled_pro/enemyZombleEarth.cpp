#include "enemyZombleEarth.h"

EnemyZombleEarth::EnemyZombleEarth(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{pl, scene, parent}{
    // 加载动画
    m_movie = new QMovie(":/images/pic/ZombleEarth.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);


    connect(enemyTimer, &QTimer::timeout, this, &EnemyZombleEarth::earthSkill);
    timeBuffer=0;
    // 基本数据
    maxHP=21;
    nowHP = 21;
    speed = 3;
}

void EnemyZombleEarth::Pathfinding (){

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
    timeBuffer++;

}

void EnemyZombleEarth::earthSkill(){
    switch (nowState) {
    case isEarth:
        timeBuffer++;
        if(timeBuffer>1000){
            timeBuffer=0;
            nowState=notEarth;
        }
        break;
    case notEarth:
        timeBuffer++;
        if(timeBuffer>1000){
            timeBuffer=0;
            nowState=isEarth;
        }
        break;
    default:
        break;
    }
}

void EnemyZombleEarth::load(){
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

    if (nowState==isEarth) {
        QPainter painter(&newPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        qreal opacity = 0.4;
        painter.setOpacity(opacity);

        QColor brownColor(139, 69, 19);
        painter.setBrush(brownColor);

        QRectF boundingRect = newPixmap.rect();
        painter.drawEllipse(boundingRect.center(), 100, 100);
    }
    setPixmap(newPixmap);
}

void EnemyZombleEarth::hurt(qreal damage){
    if(nowState==isEarth){
        nowHP-=(damage/3);
    }else{
        nowHP -= damage;
    }
    isHurt = true;
    hurtTimer.start(50);
    if (nowHP <= 0) {
        emit enemyDeath();
    }
}
