/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "Pixel.h"
#include "Vector.hpp"

enum FaceType{ CCW, CW };

class ScanConvertor
{
public:
	bool isDepthCheckEnabled;
	FaceType frontFace;
	float *depthbuffer;
	uchar8 *buffer;
	uint32 width, height;
    uint32 bytesPerPixel, bytesPerRow;
	uint32 bufferSize;
	ARGBCOLOR pixelColor;
	ARGBCOLOR curColor;
	ARGBCOLOR clrColor;

	ScanConvertor(int pixelsWide, int pixelsHigh);
	~ScanConvertor(void);
	void PutPixel(uint32 x , uint32 y);
	void PutPixel(uint32 x , uint32 y, ARGBCOLOR* color);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLineDepthInterpolated(float x1, float y1, float z1, float x2, float y2, float z2);
	void DrawTriangle(const Vector3& a, const Vector3& b, const Vector3& c);
	void Clear();
	void ClearDepth();
	void SetClearColor(ARGBCOLOR& c);
	void SetColor(ARGBCOLOR& c);
	void EnableDepthCheck(bool f);
	void SetFrontFace(FaceType f);
	float ComputeTraingleArea(const Vector3& a, const Vector3& b, const Vector3& c);
};
