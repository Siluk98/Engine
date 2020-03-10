#include "../hpp/D3DCoordTransformer.hpp"

sf::Vector2f D3DCoordTransformer::to2D(sf::Vector3f arg)
{
    sf::Vector2f ret;
    sf::Vector2u s = Engine::getWindow()::getSize();
    ret.x = (1+arg.x)*s.x*0.5;
    ret.y = (1-arg.x)*s.x*0.5;
    return ret;
}
