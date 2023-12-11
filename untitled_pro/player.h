#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QSoundEffect>
#include <QUrl>

class Player :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QGraphicsView *view, QObject *parent = nullptr);
    void load(); // 加载贴图
    QRectF boundingRect() const override;// 碰撞箱

    void addVelocity(int dx, int dy);
    void setVelocityX(int dx);
    void setVelocityY(int dy);
    void updateCoordinate();
    QPointF getCoordinateBias();

    void regen();

    void hurt();
    void resetInvincible();

    int getNowHP();
    void setNowHP(int hp);
    int getMaxHP() const;

signals:
    void playerHurt();
    void playerDeath();
    void playerRegen();

private:
    int speed;
    QGraphicsView *mainView;
    QMovie *standingRole;
    QMovie *movingRole;
    QRectF mapbounds;
    QVector2D velocityVector;//当前速度向量

    bool isRegen = false;
    int regenCount = 0;

    bool isInvincible;//受伤后无敌帧防止短时间重复接触伤
    QTimer *invincibleTimer;
    qreal invincibleTime;

    int nowHP;
    int maxHP;
};

#endif // PLAYER_H
