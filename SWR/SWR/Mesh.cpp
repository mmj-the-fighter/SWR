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

#include <fstream>
#include "Mesh.h"

void Mesh::AddVertex(float x, float y, float z)
{
	Vector4 v;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1;
	vertices.push_back(v);
}

void Mesh::AddTriangle(int index1, int index2, int index3)
{
	IntVector3 iv;
	iv.i = index1;
	iv.j = index2;
	iv.k = index3;
	triangles.push_back(iv);
}

void Mesh::AddVertexArray(float *varray, int varraysize)
{
	for(int i=0;i<varraysize;i+=3)
		AddVertex(varray[i],varray[i+1],varray[i+2]);
}

void Mesh::AddIndicesArray(int *iarray, int iarraysize)
{
	for(int i=0;i<iarraysize;i+=3) {
		int a = iarray[i] - 1;
		int b = iarray[i+1] - 1;
		int c = iarray[i+2] - 1;
		AddTriangle(a, b, c);
	}
}

int Mesh::LoadObj(char *filename)
{
	ifstream infile;
	char c;

	infile.open(filename, ios::in);
	while(!infile.fail()) {
		infile>>c;
		if(c=='v') {
			Vector4 v;
			infile>>v.x>>v.y>>v.z;
			v.w = 1;
			vertices.push_back(v);
		} else if(c=='f') {
			IntVector3 iv;
			infile>>iv.i>>iv.j>>iv.k;
			--iv.i;
			--iv.j;
			--iv.k;
			triangles.push_back(iv);
		}
	}
	infile.close();

	return 0;
}