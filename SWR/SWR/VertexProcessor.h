/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _VERTEXPROCESSOR_H_
#define _VERTEXPROCESSOR_H_

#include <vector>
#include "Vector.hpp"
#include "ScanConvertor.h"
#include "Matrix.h"
#include "Mesh.h"

using namespace std;

typedef enum _DrawMode{ SWRPOINTS, SWRWIREFRAME }DrawMode;

struct Viewport
{
	float x,y,width,height;
	float sx,sy,sz;
	float tx,ty,tz;
};


class VertexProcessor
{
private:
	vector<Vector4> vertices;
	vector<IntVector3> triangles;
	DrawMode drawMode;
	Viewport viewport;
	Matrix4x4 matModel, matView, matProjection;
public:
	ScanConvertor *scr;
	VertexProcessor();
	~VertexProcessor();
	void Init(int w, int h);
	int LoadObj(char* filename);
	void DrawMesh(Mesh& mesh);
	void SetTarget(ScanConvertor *scr);
	void SetModelMatrix(Matrix4x4& m);
	void SetViewMatrix(Matrix4x4& v);
	void SetProjectionMatrix(Matrix4x4& p);
	void SetViewPort(int x, int y, int w, int h);
	void SetDepthRange(float n, float f);
	void SetDrawMode(DrawMode dm);
};

#endif
