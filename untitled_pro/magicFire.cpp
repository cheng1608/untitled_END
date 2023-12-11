#include "magicFire.h"
#include "magicFireBallNomal.h"
#include <QRandomGenerator>

MagicFire::MagicFire(Player *pl, QGraphicsScene *scene, QObject *parent)
    : MagicBase{pl, scene, parent}
{
    pix = QPixmap("you know what hahaha");//找不到坐标对齐的方法所以我就不加法杖图片了
    setPixmap(pix);//jajaja
    setTransformOriginPoint(boundingRect().center());
    setScale(3);
}

void MagicFire::cast(){
    if (!isCasting && fireCount >= 50.0 ) return;
    fireCount++;
    if (!isCasting) return;
    if (fireCount < 50.0) return;
    fireCount = 0;
    for (int i = 0; i < 1 ; ++i) {
        QPointF center_pos = pos() + QPointF(100,100);
        magicFireBallNomal* bullet = new magicFireBallNomal(center_pos, rotation(), 15, 8, penetration, magicScene, parent());
        bullet->setRotation(bullet->rotation() );
        bullet->setParentItem(parentItem());
        bullet->setScale(3);
        magicScene->addItem(bullet);
    }
}
