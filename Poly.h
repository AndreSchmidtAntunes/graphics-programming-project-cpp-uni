#pragma once

#include "Vector3.h"
#include "Colour.h"

#define self (*this)

struct Mesh;

struct Vector2 {
public:
	union {
		struct { double x, y; };
		std::array<double, 2> data;
	};

	Vector2(double x, double y) : x(x), y(y) { };

	Vector2(const Vector2& other) : x(other.x), y(other.y) { };

	Vector2(double value = 0) : x(value), y(value) { };

	~Vector2() { };

	double& operator[](const uint idx) {
		return data[idx];
	}

	Vector2 operator + (const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
	Vector2 operator - (const Vector2& other) const { return Vector2(x - other.x, y - other.y); }
	Vector2 operator * (const Vector2& other) const { return Vector2(x * other.x, y * other.y); }
	Vector2 operator / (const Vector2& other) const { return Vector2(x / other.x, y / other.y); }

	Vector2 operator * (const double& value) const { return Vector2(x * value, y * value); }
	Vector2 operator / (const double& value) const { return Vector2(x / value, y / value); }

	Vector2& operator += (const Vector2& other) { x += other.x; y += other.y; return self; }
	Vector2& operator -= (const Vector2& other) { x -= other.x; y -= other.y; return self; }
	Vector2& operator *= (const Vector2& other) { x *= other.x; y *= other.y; return self; }
	Vector2& operator /= (const Vector2& other) { x /= other.x; y /= other.y; return self; }

	Vector2& operator *= (const double& value) { x *= value; y *= value; return self; }
	Vector2& operator /= (const double& value) { x /= value; y /= value; return self; }

};

#include <cstdarg>

struct Poly {
public:

	uint* indices;
	Colour* colours = NULL;
	Vector2* texture_coordinates = NULL;
	Vector3* normals = NULL;
	uint vert_count;

	/// <summary> Pointer to the mesh this polygon is holding indices for. </summary>
	//Mesh* owner;

	Poly() : indices(NULL), colours(NULL), texture_coordinates(NULL), vert_count(0) { };

	Poly(const uint* indices, const uint vert_count);

	Poly(const uint* indices, const Vector2* uvs, const uint vert_count) : Poly(indices, vert_count) { this->texture_coordinates = Init(uvs); };

	Poly(const uint* indices, const Vector3* normals, const uint vert_count) : Poly(indices, vert_count) { this->normals = Init(normals); };

	Poly(const uint* indices, const Colour* colours, const uint vert_count) : Poly(indices, vert_count) { this->colours = Init(colours); };

	Poly(const uint* indices, const Vector2* uvs, const Colour* colours, const uint vert_count) : 
		Poly(indices, uvs, vert_count) { 
			this->colours = Init(colours);
		};

	Poly(const uint* indices, const Vector2* uvs, const Vector3* normals, const uint vert_count) :
		Poly(indices, uvs, vert_count) {
			this->normals = Init(normals);
		};

	Poly(const uint* indices, const Vector3* normals, const Colour* colours, const uint vert_count) :
		Poly(indices, normals, vert_count) {
			this->colours = Init(colours);
		};

	Poly(const uint* indices, const Vector2* uvs, const Vector3* normals, const Colour* colours, const uint vert_count) : 
		Poly(indices, uvs, normals, vert_count) { 
			this->colours = Init(colours); 
		}

	~Poly();

private:

	Vector2*& Init(const Vector2* uvs);
	Vector3*& Init(const Vector3* normals);
	Colour*& Init(const Colour* colours);
};