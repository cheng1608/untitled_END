#ifndef SKILLBASE_H
#define SKILLBASE_H

#include <QString>

class SkillBase {
public:
    SkillBase(const QString &name, const QString &description, int cooldown);
    QString getName() const ;
    QString getDescription() const;
    int getCooldown() const ;

    // 技能效果的实现，由具体的子类实现
    virtual void effect() = 0;

private:
    QString name_;
    QString description_;
    int cooldown_;
};

#endif // SKILLBASE_H
