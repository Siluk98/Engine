#ifndef VECTOR3_HPP
#define VECTOR3_HPP

//#include <algorithm>
#include "helpers.hpp"
//#include "vector2.hpp"

template <typename T>
class Vector3
{
public:
	Vector3() {}
	Vector3( T x,T y,T z )
		:x(x)
		,y(y)
		,z(z){}

	Vector3( const Vector3& vect )
		:Vector3( vect.x,vect.y,vect.z ){}

	template <typename T2>
	explicit operator Vector3<T2>() const
	{
		return{ (T2)x,(T2)y,(T2)z };
	}

	T LenSq() const
	{
		return sq( *this );
	}

	T Len() const
	{
		return sqrt( LenSq() );
	}

	Vector3&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vector3 GetNormalized() const
	{
		Vector3 norm = *this;
		norm.Normalize();
		return norm;
	}

	Vector3 operator-() const
	{
		return Vector3( -x,-y,-z );
	}

	Vector3& operator=( const Vector3 &arg )
	{
		x = arg.x;
		y = arg.y;
		z = arg.z;
		return *this;
	}

	Vector3& operator+=( const Vector3 &arg )
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}

	Vector3& operator-=( const Vector3 &arg )
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;
	}

	T operator*( const Vector3 &arg ) const
	{
		return x * arg.x + y * arg.y + z * arg.z;
	}

	Vector3 operator+( const Vector3 &arg ) const
	{
		return Vector3( *this ) += arg;
	}

	Vector3 operator-( const Vector3 &arg ) const
	{
		return Vector3( *this ) -= arg;
	}

	Vector3&	operator*=( const T &arg )
	{
		x *= arg;
		y *= arg;
		z *= arg;
		return *this;
	}

	Vector3	operator*( const T &arg ) const
	{
		return Vector3( *this ) *= arg;
	}
	Vector3&	operator/=( const T &arg )
	{
		x /= arg;
		y /= arg;
		z /= arg;
		return *this;
	}
	Vector3	operator/( const T &arg ) const
	{
		return Vector3(*this)/=arg;
	}
	bool operator==( const Vector3 &arg ) const
	{
		return x==arg.x && y==arg.y && arg.z==z;
	}
	bool operator!=( const Vector3 &arg ) const
	{
		return !(*this==arg);
	}
	Vector3 cross(const Vector3& arg)
	{
	    return Vector3(
			y*arg.z-z*arg.y,
			z*arg.x-x*arg.z,
			x*arg.y-y*arg.x );
	}

	T x;
	T y;
	T z;
};

typedef Vector3<float> Vec3;
typedef Vector3<double> Ved3;
typedef Vector3<int> Vei3;
#endif // VECTOR3_HPP
