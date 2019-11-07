#ifndef UI_RANGE_HPP
#define UI_RANGE_HPP

#include "ui.hpp"

namespace UI
{
    class Range :public Component
    {
    public:
        Range(std::string id, cssHandler& css);
        Range(std::string id, cssHandler* css);
        ~Range();
        std::string getValue();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*){};
        void changeStyle(std::string atr,std::string val);
        std::string create(std::string obj, std::string params);
    private:
        sf::Color* SliderColor;
        sf::Color* FieldColor;
        std::string id;
        sf::RectangleShape* field;
        sf::RectangleShape* slider;
        bool focus;
        bool horizontal;
        int min;
        int max;
        int value;
    };
}

#endif
