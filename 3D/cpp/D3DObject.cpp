#include "../hpp/D3DObject.hpp"

D3DObject::D3DObject()
{
    toUpdate = false;
    position = {0,0,0};
    renderType = D3DRenderType::NoCulling;
}

D3DObject::~D3DObject()
{}

void D3DObject::draw(sf::RenderTarget &target, sf::RenderStates s) const
{
    for(unsigned int f=0;f<faces.size();f++)
    {
        for(unsigned int i=0;i<faces[f].vas.size();i++)
        {
            if(renderType==D3DRenderType::NoCulling || !faces[f].culling)
                target.draw(faces[f].vas[i]);
        }
    }

}

void D3DObject::update()
{

    updateMesh();
}

void D3DObject::pushVertex(float x,float y, float z)
{
    vertices.push_back(Vec3(x,y,z));
    toUpdate = true;
}

void D3DObject::pushFace(unsigned int a, unsigned int b)
{
    D3DFace f({a,b});
    f.color = applyColor();
    faces.push_back(f);
    toUpdate = true;
}

void D3DObject::pushFace(std::vector<unsigned int> arg)
{
    faces.push_back(arg);
    faces.back().color = applyColor();
    toUpdate = true;
}

static bool checkCulling(Vec3& a,Vec3& b,Vec3& c)
{
    Vec3 cross = (a-b).cross(a-c);
    //Vec3 ray = a-Vec3{0,0,0};
    //std::cout << cross*a;
    return cross*a >= 0.0f;
}

void D3DObject::updateMesh()
{
    if(!toUpdate) return;
    //std::cout << "Update Mesh" << std::endl;
    vertices2d.clear();
    vertices2d.shrink_to_fit();

    for(unsigned int i=0;i<vertices.size();i++)
    {
        vertices2d.push_back(D3DCoordTransformer::to2D(vertices[i]));
    }
    /*
    std::cout << vertices.size() << std::endl;
    std::cout << faces.size() << std::endl;
    std::cout << vertices2d.size() << std::endl;
    */

    for(auto& face:faces)
            {
                face.vas.clear();
                face.vas.shrink_to_fit();

                bool flag = true;
                for(unsigned int i=0;i<face.size();i++)
                    if(face[i]>=vertices2d.size()) flag = false;
                if(!flag) continue;
                if(face.size()==2)
                {

                    sf::VertexArray va;
                    va.setPrimitiveType(sf::Lines);
                    va.resize(2);
                    va[0].position = vertices2d[face[0]];
                    va[1].position = vertices2d[face[1]];
                    va[0].color = face.color;
                    va[1].color = face.color;
                    /*
                    std::cout << va[0].position.x << " " << va[0].position.y << std::endl;
                    std::cout << va[1].position.x << " " << va[1].position.y << std::endl;
                    std::cout << "--------------" << std::endl;
                    */
                    face.vas.push_back(va);
                }
                else if(face.size()>2)
                {
                    for(unsigned int i=0;i<face.size()-2;i++)
                    {


                        //if(renderType == D3DRenderType::Triangles)
                            face.culling = checkCulling(
                                    vertices[face[0]],
                                    vertices[face[i+1]],
                                    vertices[face[i+2]]
                                    );
                        if(face.culling && renderType != D3DRenderType::NoCulling) continue;
                        sf::VertexArray va;
                        va.setPrimitiveType(sf::Triangles);
                        va.resize(3);
                        va[0] = vertices2d[face[0]];
                        va[1] = vertices2d[face[i+1]];
                        va[2] = vertices2d[face[i+2]];
                        /*
                        std::cout << va[0].position.x << " " << va[0].position.y << std::endl;
                        std::cout << va[1].position.x << " " << va[1].position.y << std::endl;
                        std::cout << va[2].position.x << " " << va[2].position.y << std::endl;
                        std::cout << "--------------" << std::endl;
                        */

                        for(int j=0;j<3;j++)
                        {
                            va[j].color = face.color;
                        }
                        face.vas.push_back(va);
                    }

                }
                else continue;
            }
    //std::cout << vas.size() << std::endl;

    toUpdate = false;
}



void D3DObject::move(Vec3& arg)
{
    move(arg.x,arg.y,arg.z);
}

void D3DObject::move(float rx, float ry, float rz)
{
    for(auto& v:vertices)
    {
        v+={rx,ry,rz};
    }
    toUpdate = true;
}

Vec3 D3DObject::getPosition()
{
    return position;
}

Vec3 D3DObject::setPosition(Vec3&& v)
{
    Vec3 delta = v-getPosition();
    position = v;
    move(delta);
    toUpdate = true;
    return delta;
}

Vec3 D3DObject::setPosition(Vec3& v)
{
    Vec3 delta = v-getPosition();
    position = v;
    move(delta);
    toUpdate = true;
    return delta;
}

Vec3 D3DObject::setPosition(float rx, float ry, float rz)
{
    Vec3 v = {rx,ry,rz};
    return setPosition(v);
}

void D3DObject::rotate(float rx, float ry, float rz)
{
    //std::cout <<"rotation"<<std::endl;
    Mat3 a = Mat3::RotationZ(wrap_angle(rz));
    Mat3 b = Mat3::RotationY(wrap_angle(ry));
    Mat3 c = Mat3::RotationX(wrap_angle(rx));
    Mat3 rot = a*b*c;
    //Mat3 rot = Mat3::Identity();
    Vec3 org = getPosition();
    setPosition({0,0,0});
    for(auto& v:vertices)
    {
        v*=rot;
    }
    setPosition(org);
    toUpdate = true;
}

void D3DObject::setRenderType(D3DRenderType arg)
{
    renderType = arg;
}

sf::Color D3DObject::applyColor()
{
    static std::vector<sf::Color> colors = {
        sf::Color::Red
        ,sf::Color::Green
        ,sf::Color::Blue
        ,sf::Color::Cyan
        ,sf::Color::Magenta
        ,sf::Color::Yellow
        ,sf::Color::White
        };
    static unsigned int color = 0;
    color++;
    if(color>=colors.size()) color = 0;
    return colors[color];
}
