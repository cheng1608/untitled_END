#ifndef MAGICFIRE_H
#define MAGICFIRE_H

#include "magicBase.h"

class MagicFire : public MagicBase
{
    Q_OBJECT
public:
    explicit MagicFire(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
    void cast() override;
};

#endif // MAGICFIRE_H
