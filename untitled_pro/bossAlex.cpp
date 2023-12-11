// BossBase.cpp

#include "bossAlex.h"

BossAlex::BossAlex(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{pl, scene, parent}
{
    // connect(this, &BossBase::enemyDeath, this, &BossBase::death);

    m_movie = new QMovie(":/images/pic/boss.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    maxHP=300;
    nowHP = 300;
    speed = 4.5;

    isBusy=0;
    timeBuffer=0;
    currentState=Standing;

    connect(enemyTimer, &QTimer::timeout, this, &BossAlex::Attack);
    attack_count=0;
}

void BossAlex::Pathfinding(){//寻路使用状态机实现
    switch (currentState){
    case Standing:
        Stand();
        break;
    case Walking:
        Walk();
        break;
    }
}

// You need to implement these functions:
void BossAlex::Stand(){
    if(timeBuffer%8==0)recover();
    timeBuffer++;
    if(timeBuffer>500){
        currentState=Walking;
        timeBuffer=0;
    }
}

void BossAlex::Walk(){
    if(isFrozen)return;
    if (!enemyPlayer)return;

    // 计算boss到Player的方向
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
    // 移动boss
    setPos(newPos);

    timeBuffer++;
    if(timeBuffer>1000){
        currentState=Standing;
        timeBuffer=0;
    }
}

void BossAlex::NormalAttack(){
    attack_count++;
    qreal dist = QLineF(pos(), enemyPlayer->pos()).length();
    if (dist > 650){
        return;
    }
    if (attack_count < 100) {
        return;
    }
    attack_count = 0;
    qreal angle = -QLineF(pos(), enemyPlayer->pos()).angle();
    angle -= 30;
    for (int i = 0; i < 3; ++i) {
        QPointF tmpBias(100, 100);
        QPointF realPos=tmpBias+pos();

        enemyFire *bullet = new enemyFire(realPos, angle + 30*i, 7, 3, 0, enemyScene, enemyPlayer, enemyScene);
        bullet->setScale(2);
        bullet->setParentItem(this->parentItem());
        enemyScene->addItem(bullet);
    }
}

void BossAlex::SpecialAttack(){
    attack_count++;
    qreal dist = QLineF(pos(), enemyPlayer->pos()).length();
    if (dist > 650){
        return;
    }
    if (attack_count < 200) {
        return;
    }
    attack_count = 0;
    qreal angle = -QLineF(pos(), enemyPlayer->pos()).angle();
    angle -= 30;
    for (int i = 0; i < 6; ++i) {

        QPointF tmpBias(100, 100);
        QPointF realPos=tmpBias+pos();

        enemyFire *bullet = new enemyFire(realPos, angle + 60*i, 7, 3, 0, enemyScene, enemyPlayer, enemyScene);
        bullet->setScale(2);
        bullet->setParentItem(this->parentItem());
        enemyScene->addItem(bullet);
    }
}

void BossAlex::NearDeathAttack(){
    attack_count++;
    qreal dist = QLineF(pos(), enemyPlayer->pos()).length();
    if (dist > 850){
        return;
    }
    if (attack_count < 50) {
        return;
    }
    attack_count = 0;
    qreal angle = -QLineF(pos(), enemyPlayer->pos()).angle();
    angle -= 60;
    for (int i = 0; i < 6; ++i) {

        QPointF tmpBias(100, 100);
        QPointF realPos=tmpBias+pos();

        enemyFire *bullet = new enemyFire(realPos, angle + 60*i, 10, 5, 0, enemyScene, enemyPlayer, enemyScene);
        bullet->setScale(2);
        bullet->setParentItem(this->parentItem());
        enemyScene->addItem(bullet);
    }
}

void BossAlex::recover(){
    if(nowHP<maxHP)nowHP++;
}

void BossAlex::Attack(){//guard code$$
    if(currentState==Standing){
        return;
    }
    bossHealthPercentage = nowHP / 300.0 * 100;

    if(bossHealthPercentage>75){
        NormalAttack();
        return;
    }

    if(bossHealthPercentage<=75&&bossHealthPercentage>20){
        SpecialAttack();
        return;
    }

    if(bossHealthPercentage<20){
        NearDeathAttack();
        return;
    }
}

void BossAlex::frozen(){
    if(!canFrozen){
        return;
    }
    isFrozen=true;
    frozenTimer.start(200);//削弱了冰冻强度
}

void BossAlex::load(){
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
    // 确定角度
    qreal angle = QLineF(pos(), enemyPlayer->pos()).angle();

    QPixmap pixmap = QPixmap::fromImage(img);
    // 镜像处理
    if ((angle > 90 && angle < 270) || (angle < -90 && angle > -270)) {
        //水平镜像
        pixmap = pixmap.transformed(QTransform().scale(-1, 1));
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
                    line[x * 4 + 2] = qMin<uchar>(line[x * 4 + 2] + 70, 255);
                    line[x * 4 + 3] = qMin<uchar>(alpha + 64, 255);
                }
            }
        }
    }

    //standing开护盾
    QPixmap newPixmap(pixmap);

    if (currentState==Standing) {
        QPainter painter(&newPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        qreal opacity = 0.4; // 设置透明度
        painter.setOpacity(opacity);

        painter.setBrush(Qt::red);
        QRectF boundingRect = newPixmap.rect();
        painter.drawEllipse(boundingRect.center(), 100, 100);
    }
    setPixmap(newPixmap);
}

void BossAlex::hurt(qreal damage){
    if(currentState==Standing){
        nowHP-=(damage/4);//有盾减伤
    }else{
        nowHP -= damage;
    }
    isHurt = true;
    hurtTimer.start(50);
    if (nowHP <= 0) {
        emit enemyDeath();
    }
}

void BossAlex::death(){
    enemyScene->removeItem(this);
    emit bossDeath();
    deleteLater();
}

