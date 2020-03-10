#ifndef D3DOBJECT_HPP
#define D3DOBJECT_HPP

#include "D3DCoordTransformer.hpp"
#include "D3DFace.hpp"
#include <SFML/Graphics.hpp>
#include "../../Math/vector3.hpp"
#include "../../Math/matrix3.hpp"

enum D3DRenderType {Wireframe, Triangles, NoCulling};

class D3DObject : public sf::Drawable
{
public:
    D3DObject();
    ~D3DObject();
    void draw(sf::RenderTarget &target, sf::RenderStates s) const;
    void pushVertex(float,float,float);
    void pushFace(std::vector<unsigned int> arg);
    void pushFace(unsigned int a, unsigned int b);
    void updateMesh();
    void update();
    void rotate(float rx, float ry, float rz);
    void move(float rx, float ry, float rz);
    void move(Vec3& arg);
    Vec3 setPosition(Vec3& arg);
    Vec3 setPosition(Vec3&& arg);
    Vec3 setPosition(float rx,float ry, float rz);
    Vec3 getPosition();
    void setRenderType(D3DRenderType arg);
protected:
    D3DRenderType renderType;
    bool toUpdate;
    Vec3 position;
    std::vector<Vec3> vertices;
    std::vector<sf::Vector2f> vertices2d;
    std::vector<D3DFace> faces;
private:
    sf::Color applyColor();

};


#endif // D3DOBJECT_HPP
