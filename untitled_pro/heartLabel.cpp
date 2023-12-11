
#include "heartLabel.h"

HeartLabel::HeartLabel(QWidget *parent)
    : QLabel{parent}
{
    heartFull = QPixmap(":/images/hearts/hearts_full_small.png");
    heartPlus = QPixmap(":/images/hearts/heart_plus_small.png");
    heartMinus =QPixmap(":/images/hearts/heart_minus_small.png");
    heartEmpty = QPixmap(":/images/hearts/heart_empty_small.png");
    setPixmap(heartFull);
    setGeometry(1220, 44, 32, 32);
    show();
}

void HeartLabel::setEmptyHeart(){
    setPixmap(heartEmpty);
}

void HeartLabel::setFullHeart(){
    setPixmap(heartFull);
}

void HeartLabel::setMinusHeart(){
    setPixmap(heartMinus);
}

void HeartLabel::setPlusHeart(){
    setPixmap(heartPlus);
}
