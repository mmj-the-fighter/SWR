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
