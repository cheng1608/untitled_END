
#ifndef HEARTLABEL_H
#define HEARTLABEL_H

#include <QLabel>


class HeartLabel : public QLabel
{
public:
    HeartLabel(QWidget *parent = nullptr);
    void setEmptyHeart();
    void setMinusHeart();
    void setPlusHeart();
    void setFullHeart();
private:
    QPixmap heartFull;
    QPixmap heartMinus;
    QPixmap heartPlus;
    QPixmap heartEmpty;
};

#endif // HEARTLABEL_H
