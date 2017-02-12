#ifndef TOWER_H
#define TOWER_H
#include <memory>
#include "entity.h"
#include "enemy.h"
#include "bullet.h"
#include <SFML/System.hpp>
class Tower : public Entity
{
private:
    sf::CircleShape radius;
    bool radiusVisibility;
    Stats upgradeMultiplier;
    Stats stat;
    sf::Clock attackTime;
    double bps;
public:
    void flipVisibility()
    {
        radiusVisibility = !radiusVisibility;
    }
        int index; // index to get its price
        Tower(const std::string& filename,const sf::Vector2f& pos, bool rVisibility,const Boundary& b, int i)
        : Entity(filename,pos,sf::IntRect(0,0,32,32),b), indexCurrentTarget(-1), radius(100), radiusVisibility(rVisibility),
        upgradeMultiplier(10,10), stat(1,100),  bps(10), index(i)
        {
            radius.setOrigin(radius.getRadius(),radius.getRadius());
            syncRadius();
            radius.setFillColor(sf::Color(32,113,17,128));
            info.setText("this is the stats\n");

        }
        Tower(const Tower& e, bool rVisibility)
        : Entity(e), index(e.index), indexCurrentTarget(-1), radius(100), radiusVisibility(true),upgradeMultiplier(10,10), stat(1,500),bps(10)
        {
           // std::cout << "Tower(const Tower& e, bool rVisibility)" << std::endl;
            radius.setOrigin(radius.getRadius(),radius.getRadius());
            radius.setPosition(getPosition() + sf::Vector2f(16,16));
            radius.setFillColor(sf::Color(32,113,17,128));
        }

        void appendInformation(const Information& i)
        {
            info.appendText(i.getText());
        }

        void syncRadius()
        {
            radius.setPosition(getPosition() + sf::Vector2f(16,16));
        }

        void setPosition(const sf::Vector2f& newPos)
        {
            Entity::setPosition(newPos);
            syncRadius();
        }
        void upgrade()
        {
            stat *= upgradeMultiplier;
        }
        virtual void print() { std::cout << "tower"  << std::endl; }
    void changeRadiusColor(const std::vector<std::shared_ptr<Enemy>>& e)
    {
        bool isThereInRadius = false;
        for ( int a = 0; a < e.size(); a++ )
        {
            if ( isInsideTheRadius(e[a]->getPosition(), e[a]->getGlobalBounds()))
            {
                //std::cout << "test";
                isThereInRadius = true;
                break;
            }
        }
        if (isThereInRadius)
        {
            radius.setFillColor(sf::Color(245,10,16,128));
        }
        else
            radius.setFillColor(sf::Color(32,113,17,128));
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
        if ( radiusVisibility )
            target.draw(radius);
        for ( std::size_t a = 0; a < b.size(); a++ )
        {
            target.draw(b[a]);
        }
    }
    double getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
    {
        return sqrt(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)));
    }
    bool isInsideTheRadius(const sf::Vector2f& pos, const sf::FloatRect& globalBounds)
    {
        double vRadius = radius.getRadius();
        double enemyDistanceVertexToMiddle = getDistance(pos, pos + sf::Vector2f(16,16));
        double enemyMiddleToCircleDistance = getDistance(pos + sf::Vector2f(16,16),radius.getPosition());
        return ( enemyMiddleToCircleDistance <= enemyDistanceVertexToMiddle + vRadius &&
                radius.getGlobalBounds().intersects(globalBounds)
                );
    }
    void findTarget(std::vector<std::shared_ptr<Enemy>>& e)
    {
        if ( indexCurrentTarget >= 0 && indexCurrentTarget < e.size() )
        {
                if ( e[indexCurrentTarget]->isAlive() && isInsideTheRadius(e[indexCurrentTarget]->getPosition(), e[indexCurrentTarget]->getGlobalBounds() ) )
                {
                    if ( isTimeTOFire() )
                    {
                        fire(e[indexCurrentTarget]);
                    }
                    return;
                }
                else
                {
                    indexCurrentTarget = -1;
                }
        }

        std::size_t nearestIndex = 0;
        int nearestDistance = 999999;

        if ( e[nearestIndex]->isAlive() )
        {
            nearestDistance = getDistance(getPosition(),e[nearestIndex]->getPosition());
        }

        for ( std::size_t a = 1; a < e.size(); a++ )
        {
            if ( e[a]->isAlive() && isInsideTheRadius(e[a]->getPosition(), e[a]->getGlobalBounds()))
            {
                int nextDistance = getDistance(getPosition(),e[a]->getPosition());
                if ( nearestDistance > nextDistance )
                {
                    nearestDistance = nextDistance;
                    nearestIndex = a;
                }
            }
        }

        if ( e[nearestIndex]->isAlive() && isInsideTheRadius(e[nearestIndex]->getPosition(), e[nearestIndex]->getGlobalBounds()) )
        {
            indexCurrentTarget = nearestIndex;
            if ( indexCurrentTarget >= 0 )
            {
                if ( isTimeTOFire() )
                {
                    fire(e[indexCurrentTarget]);
                }
            }
        }
    }
    bool isTimeTOFire()
    {
        double mPerSec = 1000;
        if ( attackTime.getElapsedTime().asMilliseconds() >= mPerSec/bps )
        {
            attackTime.restart();
            return true;
        }
        return false;
    }
    void fire(std::shared_ptr<Enemy> e)
    {
        b.emplace_back("bullet.png",sf::Vector2f(getPosition() + sf::Vector2f(16,16)),e,stat,info.getInfoBoundary());
    }
    void updateBullet(double delta)
    {
        for ( std::size_t a = 0; a < b.size(); a++ )
        {
            if ( b[a].isHit() )
            {
                b[a].killEnemy();
                b.erase(b.begin()+a);
                a--;
                continue;
            }
            b[a].move(delta);
        }
    }
    const std::vector<Bullet>& getBullets()
    {
        return b;
    }
    std::vector<Bullet> b;
    int indexCurrentTarget;
};
#endif // TOWER_H
