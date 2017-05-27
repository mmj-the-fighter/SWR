/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <math.h>
#include "Vector.hpp"

#define TORADIANS(x)	((x)*0.0174532925f)
#define TODEGREES(x)	((x)*57.295779513f)

class Matrix4x4 
{
public:
	float mat[4][4];
	void SetZero();
    void SetIdentity();
    void SetTranslation(float tx, float ty, float tz);
	void SetRotationX(float ang);
	void SetRotationY(float ang);
	void SetRotationZ(float ang);
    void SetScale(float sx, float sy, float sz);
    void SetOrtho(float l,float r, float b, float t,float n, float f);
	void SetFrustum(float l,float r, float b, float t,float n, float f);
	void SetPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetLookAt(Vector3 &eye, Vector3& at, Vector3& up);
	void Transform(Vector4& pt);
	void GetViewUAxis(Vector3& res);
	void GetViewVAxis(Vector3& res);
	void GetViewNAxis(Vector3& res);

	//res = a*b
static void Multiply(Matrix4x4& res, Matrix4x4& a, Matrix4x4& b)
{
	int i,j,k;
	Matrix4x4 tmp;

	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			tmp.mat[i][j] = 0.0f;
		}
	}
	
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			for(k=0;k<4;k++) {
				tmp.mat[i][j] += a.mat[i][k] * b.mat[k][j];
			}
		}
	}

	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			res.mat[i][j] = tmp.mat[i][j];
		}
	}

}

static void CopyMat(Matrix4x4& dest, Matrix4x4& src)
{
	int i,j;

	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			dest.mat[i][j] = src.mat[i][j];
		}
	}
}
    
};


#endif
