#ifndef INFORMATION_H
#define INFORMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include "uicomponent.h"
#include "resourcemanager.h"

class Information : public sf::Drawable
{
    public:
        Information(const std::string& text,const Boundary& b)
            : infoText(text,ResourceManager<sf::Font>::getInstance().get("arial.ttf"),12), infoBoundary(b)
        {
            infoText.setPosition(b.topleft);
        }
        Information(const Boundary& b)
            : infoText("",ResourceManager<sf::Font>::getInstance().get("arial.ttf"),12), infoBoundary(b)
        {
            infoText.setPosition(b.topleft);
        }

        Information(const std::string& text)
            : infoText(text,ResourceManager<sf::Font>::getInstance().get("arial.ttf"),12)
        {

        }

        Information()
         : infoText("",ResourceManager<sf::Font>::getInstance().get("arial.ttf"),12)
        {

        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(infoText);
        }

        void setText(const std::string& text)
        {
            infoText.setString(text);
        }

        void setPosition(const sf::Vector2f& pos)
        {
            infoText.setPosition(pos);
        }

        void appendText(const std::string& text)
        {
            setText(infoText.getString() + text);
        }
        const std::string getText() const
        {
            return infoText.getString();
        }
        sf::Vector2f getPositionUnderThis()
        {
            sf::Vector2f pos = infoText.getPosition();
            pos.y += infoText.getCharacterSize();
            return pos;
        }

        const Boundary& getInfoBoundary()
        {
            return infoBoundary;
        }

        void setInfoBoundary(const Boundary& newBoundary)
        {
            infoText.setPosition(newBoundary.topleft);
            infoBoundary = newBoundary;
        }
    private:
        sf::Text infoText;
        Boundary infoBoundary;
};

#endif // INFORMATION_H
