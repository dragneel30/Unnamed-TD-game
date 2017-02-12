#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include <array>
class Enemy : public Entity
{
    public:
        Enemy(const std::string& filename, const sf::Vector2f& pos,const sf::Vector2f& gp,const Boundary& b);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void run(double delta);

        void setGoalPoint(const sf::Vector2f& newGoalPoint);
        int getGoalIndex();
        int getGoalIndexQuad() { return goalIndex * 4; }
        void incrementGoalIndex();
        bool hasReachedGoal();
        sf::Vector2f getOrigin() const { return sf::Vector2f(getPosition().x+16,getPosition().y+16); }
        virtual ~Enemy();
        bool isAlive() { return alive; }
        void setAlive(bool life ){ alive = life; }
        void hit(double damage)
        {
            hp -= damage;
            setAlive(false);
        }
        double bounty;
    private:
        double hp;
        double speed;
        enum edir { NONE = -1, DOWN, LEFT, RIGHT, UP };
        std::array<sf::Vector2f,4> vDir
        {
            {
                sf::Vector2f(0,1),
                sf::Vector2f(-1,0),
                sf::Vector2f(1,0),
                sf::Vector2f(0,-1)
            }
        };
        sf::Vector2f goalPoint;

        int calculateDir();

        int goalIndex;

        bool alive;
};

#endif // ENEMY_H
