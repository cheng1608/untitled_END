#ifndef MAGICBASE_H
#define MAGICBASE_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>
#include <QtMath>

#include "player.h"

class MagicBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MagicBase(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

    void updatePos();
    void rotateToCursor(const QPointF &target);
    void setFireRateBoost(qreal fr);
    void setDamageBoost(qreal dmg);
    void setSpeedBoost(qreal sp);

    virtual void cast()=0 ;
    void startCasting();
    void stopCasting();

    static QTimer *magicTimer;

signals:

protected:
    QGraphicsScene *magicScene;
    Player *magicPlayer;

    QPixmap pix;
    int fireCount;
    bool isCasting;
    qreal penetration;
    // 音效
    QSoundEffect *sfx_fire;
};

#endif // MAGICBASE_H
