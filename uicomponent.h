#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include <array>



enum Location { NONE = -1, MAP, SHOP, INFORMATION, LAST };

class Boundary : public sf::Drawable
//boundaries
{

    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(border); }
        Boundary(Location l) : loc(l), border(sf::LineStrip) {}

        Location loc;

        Boundary() : border(sf::LineStrip) {}
        void calculateBoundaries()
        {
                        //test
            topleft = operator[](0).position;
            rightbot = operator[](2).position;
        }

        bool isLocatedHere(Location l)
        {
            return loc == l;
        }
        void append(const sf::Vertex& v)
        {
            border.append(v);
        }
        const sf::Vertex& operator[](std::size_t index) { return border[index]; }

        sf::VertexArray border;
        sf::Vector2f topleft;
        sf::Vector2f rightbot;

        bool isMouseInside(const sf::Vector2i& mpos) const
        {
            return ( mpos.x > topleft.x && mpos.y > topleft.y && mpos.x < rightbot.x && mpos.y < rightbot.y );
        }

};

#endif // UICOMPONENT_H
