#include "../hpp/gfxMgr.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

GfxMgr::GfxMgr(){};
GfxMgr::~GfxMgr(){};

std::map<std::string,sf::Texture> GfxMgr::textures;

sf::Texture* GfxMgr::loadTexture(std::string name)
{
    if(textures.find(name) == textures.end())
    {
        sf::Texture * t = new sf::Texture;
        if(!t->loadFromFile(name))
        {
            std::cout << "Texture " << name << " failed to load" << std::endl;
            delete t;
            t = GfxMgr::loadTexture("gfx/placeholder.png");
        }
        GfxMgr::textures[name] = *t;
        return &GfxMgr::textures[name];
    }
    else
    {
        return &textures[name];
    }

}

int GfxMgr::getMapSize()
{
    return GfxMgr::textures.size();
}


