#ifndef UI_PROGRESS_BAR_HPP
#define UI_PROGRESS_BAR_HPP

#include "ui.hpp"
#include <algorithm>

namespace UI
{
    namespace Style
    {
        enum class PBDisplayStyle{Normal,Factor,Percentage,None};
    }

    class ProgressBar :public Component
    {
    public:
        ProgressBar(std::string id, cssHandler& css);
        ProgressBar(std::string id, cssHandler* css);
        ~ProgressBar();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void update();
        void collide(Object*){};
        void changeStyle(std::string atr,std::string val);
        std::string create(std::string obj, std::string params);
        int getMaxVal();
        int getVal();
        int setMaxVal(int);
        int setVal(int);
        int addVal(int);

        sf::Vector2f moveTo(int x, int y);
    private:
        void reinterpretSize();
        sf::Font* font; //observer_ptr
        sf::Color outerColor;
        sf::Color innerColor;
        sf::Color borderColor;
        sf::Color textColor;
        std::string id;
        std::string fontName;
        sf::RectangleShape outer;
        sf::RectangleShape inner;
        sf::RectangleShape border;
        sf::Text text;
        int borderThickness;
        int width;
        int height;
        int maxVal;
        int currentVal;
        Style::PBDisplayStyle displayStyle;
        Style::BoxSizing boxSizing;
    };
}

#endif // UI_PROGRESS_BAR_HPP
