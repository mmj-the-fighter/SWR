/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
