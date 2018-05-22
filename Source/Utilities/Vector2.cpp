#include "Vector2.h"



Vector2::Vector2()
{
	X = 0.0f;
	Y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}


Vector2::~Vector2()
{
}

Vector2 & Vector2::Add(const Vector2 & vec)
{
	X += vec.X;
	Y += vec.Y;
	return *this;
}

Vector2 & Vector2::Subtract(const Vector2 & vec)
{
	X -= vec.X;
	Y -= vec.Y;
	return *this;
}

Vector2 & Vector2::Multiply(const Vector2 & vec)
{
	X *= vec.X;
	Y *= vec.Y;
	return *this;
}

Vector2 & Vector2::Multiply(const float & value)
{
	X *= value;
	Y *= value;
	return *this;
}

Vector2 & Vector2::Divide(const Vector2 & vec)
{
	X /= vec.X;
	Y /= vec.Y;
	return *this;
}

Vector2 & operator+(Vector2 & v1, const Vector2 & v2)
{
	return v1.Add(v2);
}

Vector2 & operator-(Vector2 & v1, const Vector2 & v2)
{
	return v1.Subtract(v2);
}

Vector2 & operator*(Vector2 & v1, const Vector2 & v2)
{
	return v1.Multiply(v2);
}

Vector2 & operator*(Vector2 & v1, const float & value)
{
	return v1.Multiply(value);
}

Vector2 & operator/(Vector2 & v1, const Vector2 & v2)
{
	return v1.Divide(v2);
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	return this->Add(vec);
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	return this->Subtract(vec);
}

Vector2 & Vector2::operator*=(const Vector2 & vec)
{
	return this->Multiply(vec);
}

Vector2 & Vector2::operator*=(const float & value)
{
	this->X *= value;
	this->Y *= value;
	return *this;
}

Vector2 & Vector2::operator/=(const Vector2 & vec)
{
	return this->Divide(vec);
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
	stream << "(" << vec.X << "," << vec.Y << ")";
	return stream;
}
