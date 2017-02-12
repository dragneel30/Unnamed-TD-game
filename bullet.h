#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include <memory>
#include "enemy.h"


class Stats
{

public:
    Stats(double d, double s)
        : damage(d), speed(s) {}
    Stats(const Stats& s)
        : damage(s.damage), speed(s.speed) {}
    Stats& operator=(const Stats& s)
    {
        damage = s.damage;
        speed = s.speed;
        return *this;
    }

    void setDamage(double d) { damage = d; }
    void setSpeed(double s) { speed = s; }

    double getOffset(double delta) const { return speed * delta; }
    double getSpeed() { return speed; }

    Stats& operator*=(const Stats& multiplier)
    {
        damage *= multiplier.damage;
        speed *= multiplier.speed;
        return *this;
    }
    double damage;
    double speed;
private:

};


class Bullet : public Entity
{
public:
    Bullet(const std::string& filename,const sf::Vector2f& pos, std::shared_ptr<Enemy> target,const Stats& s,const Boundary& b)
        : Entity(filename,pos,sf::IntRect(0,0,8,8),b), sharedTarget(target), stat(s)
    {
        targetPosition = sharedTarget->getPosition();
        targetGlobalBounds = sharedTarget->getGlobalBounds();
    }

    void move(double delta)
    {
        if ( !isHit() )
        {
            targetGlobalBounds = sharedTarget->getGlobalBounds();
            targetPosition = sharedTarget->getPosition();
            double offset = stat.getOffset(delta);
            sf::Vector2f pos = sprite.getPosition();
            double angle = atan2(targetPosition.y-pos.y,targetPosition.x-pos.x);
            double x = offset * cos(angle);
            double y = offset * sin(angle);
            sprite.move(x,y);
        }
    }

    Stats stat;

    bool isHit() const
    {

        return sprite.getGlobalBounds().intersects(targetGlobalBounds);
    }

    bool killEnemy()
    {
        if ( sharedTarget )
        {
            if ( sharedTarget->isAlive() )
            {
                targetGlobalBounds = sharedTarget->getGlobalBounds();
                sharedTarget->hit(stat.damage);
            }
        }
    }

    sf::Vector2f targetPosition;
    sf::FloatRect targetGlobalBounds;

    std::shared_ptr<Enemy> sharedTarget;
};
#endif // BULLET_H
