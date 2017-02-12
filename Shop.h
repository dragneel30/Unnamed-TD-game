#ifndef SHOP_H
#define SHOP_H

#include "Tower.h"
#include <vector>
#include "Assets.h"
#include "uicomponent.h"
#include <SFML/Graphics.hpp>
class Shop : public sf::Drawable
{
    public:
        Shop();
        ~Shop();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for ( int a = 0; a < products.size(); a++ )
                target.draw(products[a]);
        }
        void setBoundary(const Boundary& b)
        {
            shopBoundary = b;
        }

        void event_handler(sf::Event e,const sf::Vector2i& mpos)
        {
            if ( e.type == sf::Event::MouseButtonPressed )
            {
                if ( e.mouseButton.button == sf::Mouse::Left )
                {
                    for ( int a = 0; a < products.size(); a++ )
                    {
                        if ( products[a].getProduct().isMouseInside(mpos) )
                        {
                            selectedProduct = a;
                            std::cout << selectedProduct << std::endl;
                            return;
                        }
                    }
                }
            }
        }
        void returnProduct()
        {
            selectedProduct = -1;
        }
        bool buySelectedTower(double& d) { return products[selectedProduct].buyTower(d); }
        bool hasSelectedProduct() { return selectedProduct >= 0; }
        const Tower& getSelectedTower() { return products[selectedProduct].getProduct(); }
        void arrangeProducts(const Boundary& b)
        {
            std::size_t ctr = 0;
            std::size_t arrsize = getArrayLength(towers);
            for ( std::size_t x = shopBoundary.topleft.x; x < shopBoundary.rightbot.x && ctr < arrsize; x+=32 )
            {
                for ( std::size_t y = shopBoundary.topleft.y; y < shopBoundary.rightbot.y && ctr < arrsize; y+=32 )
                {
                    products.emplace_back(500,0.5,100,Tower(towers[ctr],sf::Vector2f(x,y),false,b,ctr));
                    ctr++;
                }
            }
        }
    private:
        struct pack : sf::Drawable
        {
            double price;
            double upgradePriceMultiplier;
            double decreasedPrice;
            Tower product;
            Information info;
            const Tower& getProduct() { return product; }
            pack(double p, double um, double dp, const Tower& t)
                : price(p), upgradePriceMultiplier(um), decreasedPrice(dp), product(t)
            {
                info.setText("this is the price\n");
                product.appendInformation(info);
            }
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
            {
                target.draw(product);
            }
            double getNextPrice()
            {
                price * upgradePriceMultiplier;
            }
            bool buyTower(double& yourMoney)
            {
                if ( yourMoney < price )
                {
                    return false;
                }
                yourMoney -= price;
                return true;
            }
            bool sellTower(double& yourMoney)
            {
                yourMoney += decreasedPrice; // test
            }
        };
        std::vector<pack> products;
        Boundary shopBoundary;
        int selectedProduct;

};

#endif // SHOP_H
