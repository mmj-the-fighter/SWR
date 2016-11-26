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
