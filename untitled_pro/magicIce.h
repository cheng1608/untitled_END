#ifndef MAGICICE_H
#define MAGICICE_H


#include "magicBase.h"

class MagicIce : public MagicBase
{
    Q_OBJECT
public:
    explicit MagicIce(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
    void cast() override;
};

#endif // MAGICICE_H
