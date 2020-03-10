#ifndef MATH_HELPERS_HPP
#define MATH_HELPERS_HPP
//#include <Vector2.hpp>
#include <cmath>

/*
float dot(sf::Vector2f& a, sf::Vector2f& b)
{
    return a.x*b.x+a.y*b.y;
}

sf::Vector2f normalized(sf::Vector2f& v)
{
    float c = length(v);
    sf::Vector2f ret;
    ret.x = v.x/c;
    ret.y = v.y/c;
    return ret;
}

float length(sf::Vector2f&)
{
    return sqrt(v.x*v.x + v.y*v.y);
}
*/
constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template <typename T>
constexpr auto sq( const T& x )
{
    return x * x;
}

template<typename T>
T wrap_angle( T theta )
{
    const T modded = fmod( theta,(T)2.0 * (T)PI_D );
    return (modded > (T)PI_D) ?
        (modded - (T)2.0 * (T)PI_D) :
        modded;
}

template<typename T>
constexpr T interpolate( const T& src,const T& dst,float alpha )
{
    return src + (dst - src) * alpha;
}

template<typename T>
constexpr T to_rad( T deg )
{
    return deg * PI / (T)180.0;
}

#endif
