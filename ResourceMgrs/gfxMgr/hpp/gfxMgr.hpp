#ifndef GFXMGR_H
#define GFXMGR_H

#include <SFML/Graphics.hpp>

//change to singleton
class GfxMgr
{
public:
    GfxMgr();
    ~GfxMgr();

    static sf::Texture* loadTexture(std::string);
    static int getMapSize();
private:
    static std::map<std::string,sf::Texture> textures;
};

#endif // GFXMGR_H
