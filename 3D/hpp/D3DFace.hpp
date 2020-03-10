#ifndef D3DFACE_HPP
#define D3DFACE_HPP

#include <SFML/Graphics.hpp>

class D3DFace
{
public:
    D3DFace(){};
    D3DFace(std::vector<unsigned int>&& arg):points(arg){};
    D3DFace(std::vector<unsigned int>& arg):points(arg){};
    bool culling;
    std::vector<unsigned int> points;
    unsigned int size(){return points.size();};
    unsigned int& operator[](unsigned int arg){
        if(arg>=points.size()) return points.front();
        return points[arg];
    }
    sf::Color color;
    std::vector<sf::VertexArray> vas;
};


#endif // D3DFACE_HPP

