#pragma once
#include <iostream>


#ifndef Vector2_h
#define Vector2_h

/// <summary>
/// Represents a mathmatical vector. Can be used to represent an object in the game world.
/// </summary>
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	
	Vector2 & Add(const Vector2 &vec);
	Vector2 & Subtract(const Vector2 &vec);
	Vector2 & Multiply(const Vector2 &vec);
	Vector2 & Multiply(const float &value);
	Vector2 & Divide(const Vector2 &vec);

	//Operators override used to make calculations between the vectors
	friend Vector2& operator+(Vector2& v1, const Vector2& v2);
	friend Vector2& operator-(Vector2& v1, const Vector2& v2);
	friend Vector2& operator*(Vector2& v1, const Vector2& v2);
	friend Vector2& operator*(Vector2& v1, const float& value);
	friend Vector2& operator/(Vector2& v1, const Vector2& v2);

	Vector2& operator+= (const Vector2 & vec);
	Vector2& operator-= (const Vector2 & vec);
	Vector2& operator*= (const Vector2 & vec);
	Vector2& operator*= (const float & value);
	Vector2& operator/= (const Vector2 & vec);
	//Used to print out the vector x and y values if needed
	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);

	float X;
	float Y;

};

#endif // !Vector2_h




