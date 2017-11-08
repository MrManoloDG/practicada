#ifndef _Vector3_
#define _Vector3_

#include <math.h>

namespace Asedio
{
    class Vector3
    {
    public:
	    float x, y, z;

    public:
	    //default constructor
	    Vector3(float X = 0, float Y = 0, float Z = 0)
	    {
		    x = X;
		    y = Y;
		    z = Z;
	    }
	    ~Vector3(){};

	    //calculate and return the magnitude of this vector
	    float length()
	    {
		    return sqrtf(x * x + y * y + z * z);
	    }

        //calculate and return the squared magnitude of this vector
	    float slength()
	    {
		    return x * x + y * y + z * z;
	    }

        //multiply this vector by a scalar
	    Vector3 multiply(float num) const
	    {
		    return Vector3(x * num, y * num, z * num);
	    }

	    //multiply this vector by a scalar
	    Vector3 operator*(float num) const
	    {
		    //return Vector3(x * num, y * num, z * num);
            return this->multiply(num);
	    }

	    //pass in a vector, pass in a scalar, return the product
	    friend Vector3 multiply(float num, Vector3 const &vec)
	    {
		    return Vector3(vec.x * num, vec.y * num, vec.z * num);
	    }

        //pass in a vector, pass in a scalar, return the product
	    friend Vector3 operator*(float num, Vector3 const &vec)
	    {
		    //return Vector3(vec.x * num, vec.y * num, vec.z * num);
            return vec.multiply(num);
	    }

	    //add two vectors
	    Vector3 add(const Vector3 &vec) const
	    {
		    return Vector3(x + vec.x, y + vec.y, z + vec.z);
	    }

        //add two vectors
	    Vector3 operator+(const Vector3 &vec) const
	    {
		    return this->add(vec);
	    }

        //subtract two vectors
	    Vector3 subtract(const Vector3 &vec) const
	    {
		    return Vector3(x - vec.x, y - vec.y, z - vec.z);
	    }

	    //subtract two vectors
	    Vector3 operator-(const Vector3 &vec) const
	    {
		    //return Vector3(x - vec.x, y - vec.y, z - vec.z);
            return this->subtract(vec);
	    }

	    //normalize this vector
	    void normalize()
	    {
		    float magnitude = sqrtf(x * x + y * y + z * z);
		    x /= magnitude;
		    y /= magnitude;
		    z /= magnitude;
	    }
    	
	    //calculate and return dot product
	    float dotVector3(const Vector3 &vec) const
	    {
		    return x * vec.x + y * vec.y + z * vec.z;
	    }

	    //calculate and return cross product
	    Vector3 cross(const Vector3 &vec) const
	    {
		    return Vector3(y * vec.z - z * vec.y,
				    z * vec.x - x * vec.z,
				    x * vec.y - y * vec.x);
	    }
    };
}

#endif