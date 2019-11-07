#include "../hpp/fontMgr.hpp"
#include <iostream>

FontMgr* FontMgr::instance = nullptr;

FontMgr::FontMgr(){
    instance = this;
};

FontMgr::~FontMgr(){};

sf::Font* FontMgr::loadFont(std::string name)
{
    sf::Font* font = new sf::Font;

    if(!font->loadFromFile(name))
    {
        std::cout << "Font " << name << " failed to load" << std::endl;
        font = this->loadFont("fonts/arial.ttf");
    }

    fonts.push_back(font);
    return font;
}

FontMgr* FontMgr::create()
{
    if(instance == nullptr)
        return new FontMgr;
    return instance;
}

FontMgr* FontMgr::getInstance()
{
    return instance;
}
