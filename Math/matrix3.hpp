#ifndef MATRIX3_HPP
#define MATRIX3_HPP

#include "vector3.hpp"

template <typename T>
class Matrix3
{
public:
	Matrix3& operator=( const Matrix3& arg )
	{
		memcpy( elements,arg.elements,sizeof( elements ) );
		return *this;
	}
	Matrix3& operator*=( T arg )
	{
		for( auto& row : elements )
		{
			for( T& e : row )
			{
				e *= arg;
			}
		}
		return *this;
	}
	Matrix3 operator*( T arg ) const
	{
		Matrix3 result = *this;
		return result *= arg;
	}
	Matrix3 operator*( const Matrix3& arg ) const
	{
		Matrix3 result;
		for( size_t j = 0; j < 3; j++ )
		{
			for( size_t k = 0; k < 3; k++ )
			{
				T sum = (T)0.0;
				for( size_t i = 0; i < 3; i++ )
				{
					sum += elements[j][i] * arg.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}
	static Matrix3 Identity()
	{
		return {
			(T)1.0,(T)0.0,(T)0.0,
			(T)0.0,(T)1.0,(T)0.0,
			(T)0.0,(T)0.0,(T)1.0
		};
	}
	static Matrix3 Scaling( T factor )
	{
		return{
			factor,(T)0.0,(T)0.0,
			(T)0.0,factor,(T)0.0,
			(T)0.0,(T)0.0,factor
		};
	}
	static Matrix3 RotationX( T theta )
	{
		const T sinTheta = sin( theta );
		const T cosTheta = cos( theta );
		return{
			(T)1.0, (T)0.0,   (T)0.0,
			(T)0.0, cosTheta, -sinTheta,
			(T)0.0, sinTheta, cosTheta,
		};
	}
	static Matrix3 RotationY( T theta )
	{
		const T sinTheta = sin( theta );
		const T cosTheta = cos( theta );
		return{
			 cosTheta, (T)0.0, sinTheta,
			 (T)0.0,   (T)1.0, (T)0.0,
			 -sinTheta, (T)0.0, cosTheta
		};
	}
	static Matrix3 RotationZ( T theta )
	{
		const T sinTheta = sin( theta );
		const T cosTheta = cos( theta );
		return{
			 cosTheta, -sinTheta, (T)0.0,
			sinTheta, cosTheta, (T)0.0,
			(T)0.0,    (T)0.0,   (T)1.0
		};
	}
public:
	// [ row ][ col ]
	T elements[3][3];
};

template<typename T>
Vector3<T>& operator*=( Vector3<T>& left,const Matrix3<T>& arg )
{
	return left = left * arg;
}

template<typename T>
Vector3<T> operator*( const Vector3<T>& left,const Matrix3<T>& arg )
{
	return{
		left.x * arg.elements[0][0] + left.y * arg.elements[1][0] + left.z * arg.elements[2][0],
		left.x * arg.elements[0][1] + left.y * arg.elements[1][1] + left.z * arg.elements[2][1],
		left.x * arg.elements[0][2] + left.y * arg.elements[1][2] + left.z * arg.elements[2][2]
	};
}

typedef Matrix3<float> Mat3;
typedef Matrix3<double> Mad3;

#endif // MATRIX3_HPP
