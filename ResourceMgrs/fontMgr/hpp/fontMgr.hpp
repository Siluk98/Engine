#ifndef FONTMGR_HPP
#define FONTMGR_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class FontMgr
{
public:
    ~FontMgr();
    sf::Font* loadFont(std::string name);
    static FontMgr* getInstance();
    //static FontMgr* create();
private:
    FontMgr();
    std::map<std::string,sf::Font*> fonts;
    static FontMgr* instance;
};

#endif
