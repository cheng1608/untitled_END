#include "skillBase.h"

SkillBase::SkillBase(const QString &name, const QString &description, int cooldown)
    : name_(name), description_(description), cooldown_(cooldown) {}

QString SkillBase::getName() const {
    return name_;
}

QString SkillBase::getDescription() const {
    return description_;
}

int SkillBase::getCooldown() const {
    return cooldown_;
}
