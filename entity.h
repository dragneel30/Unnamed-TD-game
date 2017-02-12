#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "resourcemanager.h"
#include "information.h"
#include "uicomponent.h"
#include <iostream>
class Entity : public sf::Drawable
{
    public:
        Entity(const std::string& filename, const sf::Vector2f& pos,sf::IntRect rect,const Boundary& b);
        Entity(const Entity& e)
            : sprite(e.sprite), info(e.info)
        {
            std::cout << "Entity(const Entity& e)" << std::endl;
        }
        virtual void setPosition(const sf::Vector2f& newPos) { sprite.setPosition(newPos); }
        const sf::Vector2f getPosition() const { return sprite.getPosition(); }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual ~Entity();
        sf::FloatRect getGlobalBounds() const;
        const sf::Sprite& getSprite() const { return sprite; }
        void setTexture(const std::string filename);
        bool isMouseInside(const sf::Vector2i& mpos) const;

        const Information& getInformation() { return info; }
        virtual void print() {
           // std::cout << "entity"  << std::endl;
            }
    protected:
        sf::Sprite sprite;
        Information info;

};

#endif // ENTITY_H
