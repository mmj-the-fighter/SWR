/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <math.h>

struct Vector4
{
 	float x;
	float y;
	float z;
	float w;
};

struct Vector3
{
 	float x;
	float y;
	float z;
};

struct Vector2
{
 	float x;
	float y;
};

struct IntVector3
{
 	int i;
	int j;
	int k;
};

static Vector3 Vec3Make(float x, float y, float z)
{
	Vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

static void Vec3Set(Vector3& v, float x, float y, float z)
{
	v.x = x;
	v.y = y;
	v.z = z;
}

static void Vec3Diff(Vector3& res, Vector3& a, Vector3& b)
{
	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
}

static float Vec3Dot(Vector3& a, Vector3& b)
{
	return (a.x*b.x +a.y*b.y +a.z*b.z);
}


static void Vec3Cross(Vector3& res, Vector3& a, Vector3& b)
{
    Vector3 t;
    t.x = a.y * b.z - a.z * b.y;
    t.y = a.z * b.x - a.x * b.z;
    t.z = a.x * b.y - a.y * b.x;
	res = t;	
}

static void Vec3Norm(Vector3& res, Vector3& v)
{
	float	f;
	double t;
	t = (double)(v.x * v.x + v.y * v.y + v.z * v.z);
	t = 1.0 / sqrt(t);
	f = (float)t;
	res.x = v.x * f;
	res.y = v.y * f;
	res.z = v.z * f;
}

static void Vec3Scale(Vector3& res, const Vector3& a, const float& s)
{
	res.x = a.x * s; 
	res.y = a.y * s;  
	res.z = a.z * s;
}

static void Vec3Add(Vector3& res, const Vector3& a, const Vector3& b)
{
	res.x = a.x + b.x; 
	res.y = a.y + b.y;  
	res.z = a.z + b.z;
}

#endif
