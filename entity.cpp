#include "entity.h"

Entity::Entity(const std::string& filename,const sf::Vector2f& pos,sf::IntRect rect,const Boundary& b)
    : info(b)
{
    sprite.setPosition(pos);
    sprite.setTexture(ResourceManager<sf::Texture>::getInstance().get(filename));
    sprite.setTextureRect(rect); //test
}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}

bool Entity::isMouseInside(const sf::Vector2i& mpos) const
{
    sf::Vector2f pos = getPosition();
    return ( mpos.x > pos.x && mpos.y > pos.y && mpos.x < pos.x + 32 && mpos.y < pos.y + 32);
}

void Entity::setTexture(const std::string filename)
{
    sprite.setTexture(ResourceManager<sf::Texture>::getInstance().get(filename));
}


sf::FloatRect Entity::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}
