#ifndef MAGICWATER_H
#define MAGICWATER_H


#include "magicBase.h"

class MagicWater : public MagicBase
{
    Q_OBJECT
public:
    explicit MagicWater(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
    void cast() override;
};

#endif // MAGICWATER_H
