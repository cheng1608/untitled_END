#include "enemyZombleEarthGiant.h"

EnemyZombleEarthGiant::EnemyZombleEarthGiant(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyZombleEarth(pl, scene, parent)
{
    // 加载动画
    m_movie = new QMovie(":/images/pic/ZombleEarth.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    timeBuffer = 0;
    // 基本数据
    maxHP=41;
    nowHP = 41;
    speed = 3;
}

void EnemyZombleEarthGiant::load(){
    QImage img(m_movie->currentImage());

    if (isHurt) {//变白
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
    if ((angle > 90 && angle < 270) || (angle < -90 && angle > -270)) {
        pixmap = pixmap.transformed(QTransform().scale(-1, 1));
    }

    QPixmap newPixmap(pixmap);
    QTransform transform;
    transform.scale(2, 2); // 扩大一倍

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
