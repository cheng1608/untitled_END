
#include "magicBase.h"


QTimer *m_timer = nullptr;

MagicBase::MagicBase(Player *pl, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, magicScene(scene), magicPlayer(pl)
{

    fireCount = 0;
    isCasting = 0;
    penetration = 0;

}


void MagicBase::updatePos(){
    setPos(magicPlayer->pos());
}

void MagicBase::rotateToCursor(const QPointF &target){
    QPointF weaponPos = mapToScene(transformOriginPoint());
    double dx = target.x() - weaponPos.x() - 100;
    double dy = target.y() - weaponPos.y() - 100;//100是实际位置和图片对象的偏移量，这个比较麻烦很难搞啊啊
    setRotation(-qRadiansToDegrees(qAtan2(dx, dy))+90);
}

void MagicBase::startCasting(){
    isCasting = true;
}

void MagicBase::stopCasting(){
    isCasting = false;
}



