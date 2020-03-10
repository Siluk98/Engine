#include "../hpp/fontMgr.hpp"
#include <iostream>

FontMgr* FontMgr::instance = nullptr;

FontMgr::FontMgr(){
    instance = this;
};

FontMgr::~FontMgr(){
    instance = nullptr;
};

sf::Font* FontMgr::loadFont(std::string name)
{
    std::cout << __FILE__   << ":" << __LINE__ << "d0" << std::endl;
    if(fonts.find(name) != fonts.end())
    {
        std::cout << __FILE__   << ":" << __LINE__ << "fontsssss" << std::endl;
        return fonts[name];
    }
    std::cout << __FILE__   << ":" << __LINE__ << "d1" << std::endl;
    sf::Font* font = new sf::Font;
    std::cout << __FILE__   << ":" << __LINE__ << "d2" << std::endl;
    if(!font->loadFromFile(name))
    {
        std::cout << "Font " << name << " failed to load" << std::endl;
        delete font;
        font = this->loadFont("fonts/arial.ttf");
    }
    std::cout << __FILE__   << ":" << __LINE__ << "font loaded" << std::endl;
    fonts[name] = font;
    std::cout << __FILE__   << ":" << __LINE__ << "PYTA" << std::endl;
    return font;
}

FontMgr* FontMgr::getInstance()
{
    if(instance == nullptr) instance = new FontMgr;
    return instance;
}
