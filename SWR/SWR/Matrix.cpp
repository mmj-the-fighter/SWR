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

#include "Matrix.h"

void Matrix4x4::SetZero() 
{
	for(int i=0;i < 4;i++) {
		for(int j=0; j < 4;j++) {
			mat[i][j] = 0.0f;
		}
	}
}

void Matrix4x4::SetIdentity() 
{
	for(int i=0;i < 4;i++) {
		for(int j=0; j < 4;j++) {
			mat[i][j] = (i==j) ? 1.0f : 0.0f;
		}
	}
}

void Matrix4x4::SetTranslation(float tx, float ty, float tz) 
{
	SetIdentity();
	mat[0][3] = tx;
	mat[1][3] = ty;
	mat[2][3] = tz;
}

void Matrix4x4::SetRotationX(float ang)
{
	float rad = TORADIANS(ang);
	float sinAng =  sin(rad);
	float cosAng =  cos(rad);
	SetIdentity();
	mat[1][1] = cosAng;
    mat[1][2] = sinAng;
    mat[2][1] = -sinAng;
    mat[2][2] = cosAng;
}

void Matrix4x4::SetRotationY(float ang)
{
	float rad = TORADIANS(ang);
    float sinAng =  sin(rad);
    float cosAng =  cos(rad);
	SetIdentity();
    mat[0][0] = cosAng;
    mat[0][2] = -sinAng;
    mat[2][0] = sinAng;
    mat[2][2] = cosAng;
}

void Matrix4x4::SetRotationZ(float ang)
{
	float rad = TORADIANS(ang);
    float sinAng =  sin(rad);
    float cosAng =  cos(rad);
	SetIdentity();
    mat[0][0] = cosAng;
    mat[0][1] = sinAng;
    mat[1][0] = -sinAng;
    mat[1][1] = cosAng;
}
    
void Matrix4x4::SetScale(float sx, float sy, float sz) 
{
	SetIdentity();
    mat[0][0] = sx;
    mat[1][1] = sy;
    mat[2][2] = sz;
}
    
void Matrix4x4::SetOrtho(float l,float r, float b, float t,float n, float f)
{
	SetZero();
	mat[0][0] = 2/(r-l);
	mat[0][3] = -((r+l)/(r-l));
	mat[1][1] = 2/(t-b);
	mat[1][3] = -((t+b)/(t-b));
	mat[2][2] = -2/(f-n);
	mat[2][3] = -((f+n)/(f-n));
	mat[3][3] = 1;
}

void Matrix4x4::SetFrustum(float l,float r, float b, float t,float n, float f)
{
	SetZero();
	mat[0][0] = 2*n/(r-l);
	mat[0][2] = (r+l)/(r-l);
	mat[1][1] = 2*n/(t-b);
	mat[1][2] = (t+b)/(t-b);
	mat[2][2] = -((f+n)/(f-n));
	mat[2][3] = -2*f*n/(f-n);
	mat[3][2] = -1;
}

void Matrix4x4::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	float xmin, xmax, ymin, ymax;
	ymax = zNear * tan( fovy * 0.00872664626f ); //0.00872664626f = PI / 360.0
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;
	SetFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}

void Matrix4x4::SetLookAt(Vector3 &eye, Vector3& at, Vector3& up)
{
	Vector3 u,v,n;

	//n = eye - at
	n.x = eye.x - at.x;
	n.y = eye.y - at.y;
	n.z = eye.z - at.z;

	//n = |n|
	Vec3Norm(n,n);
	
	//up = |up|
	Vec3Norm(up,up);

	//u = up X n
	Vec3Cross(u, up, n);

	//u = |u|
	Vec3Norm(u,u);

	//v = n X u
	Vec3Cross(v, n, u);

	//fill in view matrix 
	mat[0][0] = u.x;	mat[0][1] = u.y;	mat[0][2] = u.z;	mat[0][3] = -Vec3Dot(eye, u);
	mat[1][0] = v.x;	mat[1][1] = v.y;	mat[1][2] = v.z;	mat[1][3] = -Vec3Dot(eye, v);
	mat[2][0] = n.x;	mat[2][1] = n.y;	mat[2][2] = n.z;	mat[2][3] = -Vec3Dot(eye, n);
	mat[3][0] = 0;		mat[3][1] = 0;		mat[3][2] = 0;		mat[3][3] = 1;
}

void Matrix4x4::GetViewUAxis(Vector3& res) 
{
	res.x=mat[0][0]; res.y=mat[0][1]; res.z=mat[0][2];
}
void Matrix4x4::GetViewVAxis(Vector3& res) 
{
	res.x=mat[1][0]; res.y=mat[1][1]; res.z=mat[1][2];
}
void Matrix4x4::GetViewNAxis(Vector3& res) 
{
	res.x=mat[2][0]; res.y=mat[2][1]; res.z=mat[2][2];
}


void Matrix4x4::Transform(Vector4& pt)
{
	float x = mat[0][0] * pt.x + mat[0][1] * pt.y +  mat[0][2] * pt.z + mat[0][3] * pt.w;
    float y = mat[1][0] * pt.x + mat[1][1] * pt.y +  mat[1][2] * pt.z + mat[1][3] * pt.w;
    float z = mat[2][0] * pt.x + mat[2][1] * pt.y +  mat[2][2] * pt.z + mat[2][3] * pt.w;
    float w = mat[3][0] * pt.x + mat[3][1] * pt.y +  mat[3][2] * pt.z + mat[3][3] * pt.w;
    pt.x = x; pt.y = y; pt.z = z; pt.w = w;
}
