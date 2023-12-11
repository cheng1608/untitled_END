#include "enemyZombleWindGiant.h"

EnemyZombleWindGiant::EnemyZombleWindGiant(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyZombleWind(pl, scene, parent)
{
    // 加载动画
    m_movie = new QMovie(":/images/pic/ZombleWind.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    timeBuffer = 0;
    // 基本数据
    maxHP=20;
    nowHP = 20;
    speed = 3.5;
}

void EnemyZombleWindGiant::load(){
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
    QTransform transform;
    transform.scale(2, 2); // 将图像宽度和高度都扩大一倍

    // 镜像处理
    if ((angle > 90 && angle < 270) || (angle < -90 && angle > -270)) {
        //水平镜像
        pixmap = pixmap.transformed(QTransform().scale(-1, 1));
    }
    // 设置显示图像
    setPixmap(pixmap);
}
