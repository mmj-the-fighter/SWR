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

#include "VertexProcessor.h"
#define DEPTHSCALE ((float)(0x00ffffff))

VertexProcessor::VertexProcessor()
{
	drawMode = SWRWIREFRAME;
	SetDepthRange(0.0f, 1.0f);
}

void VertexProcessor::Init(int w, int h)
{
	scr = new ScanConvertor(w,h);
}
VertexProcessor::~VertexProcessor()
{
	delete scr;
}

void VertexProcessor::DrawMesh(Mesh& mesh)
{
	vector<Vector3> transformedVertices;
	Matrix4x4 vm,pvm;
	Matrix4x4::Multiply(vm,matView,matModel); 
	Matrix4x4::Multiply(pvm,matProjection, vm);

	for(vector<Vector4>::iterator it=mesh.vertices.begin();it!=mesh.vertices.end();it++) {
		Vector4 v = *it;

		//modelspace to	clip space
		pvm.Transform(v);
		
		//clip space to ndc
		v.x /= v.w;
		v.y /= v.w;
		v.z /= v.w;
		v.w = 1.0f;
		
		//ndc to dc
		v.x = viewport.sx * v.x + viewport.tx;
		v.y = viewport.sy * v.y + viewport.ty;
		v.z = viewport.sz * v.z + viewport.tz;
		v.y = viewport.y+viewport.height - v.y;

		if(drawMode == SWRWIREFRAME)
		{
			transformedVertices.push_back( Vec3Make(v.x,v.y,v.z) );
		} else if(drawMode == SWRPOINTS) {
			scr->PutPixel((int)v.x, (int)v.y);
		}
	}

	if(drawMode == SWRPOINTS)
		return;

	for(vector<IntVector3>::iterator it=mesh.triangles.begin();it!=mesh.triangles.end();it++) {
		IntVector3 t = *it;
		Vector3 a = transformedVertices[t.i];
		Vector3 b = transformedVertices[t.j];
		Vector3 c = transformedVertices[t.k];
		scr->DrawTriangle(a,b,c);
	}
}


void VertexProcessor::SetModelMatrix(Matrix4x4& m)
{
	Matrix4x4::CopyMat(matModel, m);
}

void VertexProcessor::SetViewMatrix(Matrix4x4& v)
{
	Matrix4x4::CopyMat(matView, v);
}

void VertexProcessor::SetProjectionMatrix(Matrix4x4& p)
{ 
	Matrix4x4::CopyMat(matProjection, p);
}

void VertexProcessor::SetViewPort(int x, int y, int w, int h)
{
	viewport.x = (float)x;
	viewport.y = (float)y;
	viewport.width = (float)w;
	viewport.height = (float)h;
	viewport.sx = viewport.width * 0.5f;
	viewport.tx = viewport.sx + viewport.x;
	viewport.sy = viewport.height * 0.5f;
	viewport.ty = viewport.sy - viewport.y;
}

void VertexProcessor::SetDepthRange(float n, float f)
{
	viewport.sz = DEPTHSCALE * ((f - n) / 2.0f);
	viewport.tz = DEPTHSCALE * ((f - n) / 2.0f + n);
}

void VertexProcessor::SetDrawMode(DrawMode dm)
{ 
	drawMode = dm; 
}


