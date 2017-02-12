#include "enemy.h"

Enemy::Enemy(const std::string& filename, const sf::Vector2f& pos, const sf::Vector2f& gp,const Boundary& b)
    : Entity(filename,pos,sf::IntRect(0,0,32,32),b), goalPoint(gp), goalIndex(0), alive(true), speed(250),
    hp(10000), bounty(200)
{
    info.setText("testststet");
}

Enemy::~Enemy()
{

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}

bool Enemy::hasReachedGoal()
{
    //std::cout << sprite.getPosition().x << "," << sprite.getPosition().y << " " << goalPoint.x << "," << goalPoint.y << std::endl;
    return sprite.getPosition() == goalPoint;
}
void Enemy::run(double delta)
{
    double offset = speed * delta;
   // std::cout << calculateDir() << std::endl;
    int dir = calculateDir();
    //std::cout << calculateDir() << std::endl;
    //std::cout << direction.x << " " << direction.y << std::endl;
    sf::Vector2f vOffset = sf::Vector2f(vDir[dir].x * offset, vDir[dir].y * offset);
    sf::Vector2f pos = sprite.getPosition();

   // sf::Vector2f possibleNewOffset = sf::Vector2f((double),((double)));
   // std::cout << pos.x << "-" << goalPoint.x << " " << pos.y << "-" << goalPoint.y << std::endl;
  //std::cout <<  abs(pos.x - goalPoint.x) << " < " << vOffset.x << " ==== " << abs(pos.y - goalPoint.y) << " < " << vOffset.y << std::endl;
    if ( abs(pos.x - goalPoint.x) < vOffset.x || abs(pos.y - goalPoint.y) < vOffset.y )
    {
        sprite.setPosition(goalPoint);
    }
    else
    {
        sprite.move(vOffset);
    }
   // std::cout << "Sprite pos: " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
  // std::cout << "voffset: " << vOffset.x << " " << vOffset.y << std::endl;
   // std::cout << "possible new offset: " << abs(pos.x - goalPoint.x) << " " << abs(pos.y - goalPoint.y) << std::endl;
}

int Enemy::getGoalIndex()
{
    return goalIndex;
}

void Enemy::incrementGoalIndex()
{
    goalIndex++;
}

void Enemy::setGoalPoint(const sf::Vector2f& newGoalPoint)
{
    goalPoint = newGoalPoint;
}

int Enemy::calculateDir()
{
    sf::Vector2f pos = sprite.getPosition();
    if ( pos.x > goalPoint.x )
    {
        return static_cast<int>(LEFT);
    }
    else if ( pos.x < goalPoint.x )
    {
        return static_cast<int>(RIGHT);
    }
    else if ( pos.y > goalPoint.y )
    {
        return static_cast<int>(UP);
    }
    else // ( pos.y < goalPoint.y )
    {
        return static_cast<int>(DOWN);
    }
}
