/*
    Description: A simple wireframe renderer
	Author: Manoj M J
    Copyright (C) 2016 Manoj M J

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
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
