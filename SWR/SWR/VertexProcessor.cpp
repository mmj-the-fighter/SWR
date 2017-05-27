/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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


