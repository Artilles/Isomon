#pragma once

#include <iostream>


class Vector
{

public:

	Vector()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector(const float x, const float y, const float z)
	{
		Vector::x = x;
		Vector::y = y;
		Vector::z = z;
	}

	~Vector();


	void Add(const Vector v)
	{
		Vector::x += v.x;
		Vector::y += v.y;
		Vector::z += v.z;
	}

	void Multiply(const Vector v) 
	{
		Vector::x *= v.x;
		Vector::y *= v.y;
		Vector::z *= v.z;
	}

	void Divide(const Vector v) 
	{
		Vector::x /= v.x;
		Vector::y /= v.y;
		Vector::z /= v.z;
	}

	static Vector Add(const Vector a, const Vector b)
	{
		static Vector result;
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		result.z = a.z + b.z;

		return result;
	}

	static Vector Multiply(const Vector a, const Vector b)
	{
		static Vector result;
		result.x = a.x * b.x;
		result.y = a.y * b.y;
		result.z = a.z * b.z;

		return result;
	}

	void ToString() const
	{
		std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
	}
	
	float x;
	float y;
	float z;

private:


};

