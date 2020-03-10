#include "../hpp/D3DCoordTransformer.hpp"

//sf::Vector2f D3DCoordTransformer::to2D(sf::Vector3f& arg)
sf::Vector2f D3DCoordTransformer::to2D(Vec3& arg)
{
    sf::Vector2f ret;
    sf::Vector2u s = Engine::getWindow().getSize();
    float invz = 1.0f/arg.z;
    //float invz = 1.0f;
    ret.x = (1+arg.x*invz)*s.x*0.5;
    ret.y = (1-arg.y*invz)*s.y*0.5;
    return ret;
}
