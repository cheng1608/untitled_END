#include "magicWater.h"

#include "magicWaterBall.h"
#include <QRandomGenerator>

MagicWater::MagicWater(Player *pl, QGraphicsScene *scene, QObject *parent)
    : MagicBase{pl, scene, parent}
{
    pix = QPixmap("you know what hahaha");//找不到坐标对齐的方法所以我就不加法杖图片了
    setPixmap(pix);//jajaja
    setTransformOriginPoint(boundingRect().center());
    setScale(3);

    penetration=1;//穿透
}

void MagicWater::cast(){
    if (!isCasting && fireCount >= 40.0 ) return;
    fireCount++;
    if (!isCasting) return;
    if (fireCount < 40.0 ) return;
    fireCount = 0;
    for (int i = 0; i < 1 ; ++i) {
        QPointF center_pos = pos() + QPointF(100,100);
        magicWaterBall* bullet = new magicWaterBall(center_pos, rotation(), 3, 2.5, penetration, magicScene, parent());
        bullet->setRotation(bullet->rotation());
        bullet->setParentItem(parentItem());
        bullet->setScale(3);
        magicScene->addItem(bullet);
    }
}
