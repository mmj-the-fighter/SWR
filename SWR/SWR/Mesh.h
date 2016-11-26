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

#ifndef _MESH_H_
#define _MESH_H_
#include <vector>
#include "Vector.hpp"

using namespace std;

class Mesh
{
public:
	vector<Vector4> vertices;
	vector<IntVector3> triangles;
	void AddVertexArray(float *varray, int varraysize);
	void AddIndicesArray(int *iarray, int iarraysize);
	void AddVertex(float x, float y, float z);
	void AddTriangle(int index1, int index2, int index3);
	int LoadObj(char* filename);
};

#endif