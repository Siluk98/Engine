#ifndef D3D_COORD_TRANSFORMER_HPP
#define D3D_COORD_TRANSFORMER_HPP

#include "../../Core/hpp/engine.hpp"
#include "../../Math/vector3.hpp"

class D3DCoordTransformer
{
public:
//    static sf::Vector2f to2D(sf::Vector3f&);
    static sf::Vector2f to2D(Vec3&);
protected:
private:
    D3DCoordTransformer();
    ~D3DCoordTransformer();
};


#endif // D3D_COORD_TRANSFORMER_HPP

