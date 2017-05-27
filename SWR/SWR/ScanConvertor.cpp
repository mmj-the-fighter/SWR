/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <math.h>
#include <string.h>
#include "ScanConvertor.h"
#define MAXDEPTH ((float)(0x00ffffff))

ScanConvertor::ScanConvertor(int pixelsWide, int pixelsHigh)
{
	curColor = c_white;
	clrColor = c_black;
	bytesPerPixel = 32 / 8;
	width = pixelsWide;
	height = pixelsHigh;
	bytesPerRow = pixelsWide*bytesPerPixel;
	bufferSize = pixelsHigh * bytesPerRow;
	buffer = new uchar8[bufferSize];
	depthbuffer = new float[pixelsWide*pixelsHigh];
	isDepthCheckEnabled = true;
	frontFace = CCW;
}

void ScanConvertor::EnableDepthCheck(bool f){
	isDepthCheckEnabled = f;
}

ScanConvertor::~ScanConvertor()
{
	if(buffer != 0) {
       delete[] buffer;
       buffer = 0;
	}
	if(depthbuffer !=0) {
		delete[] depthbuffer;
		depthbuffer = 0;
	}
}

void ScanConvertor::PutPixel(uint32 x , uint32 y)
{
	if(( x < 0 || x >= width ) ||( y < 0 || y >= height) ) {
		return;
	}
	uchar8* loc = buffer + ( y*bytesPerRow + x*bytesPerPixel );
	*loc++ = curColor.b;
	*loc++ = curColor.g;
	*loc++ = curColor.r;
	*loc = curColor.a;
}

void ScanConvertor::PutPixel(uint32 x , uint32 y, ARGBCOLOR* color)
{
	if(( x < 0 || x >= width ) ||( y < 0 || y >= height) ) {
		return;
	}
	uchar8* loc = buffer + ( y*bytesPerRow + x*bytesPerPixel );
	*loc++ = color->b;
	*loc++ = color->g;
	*loc++ = color->r;
	*loc = color->a;
}

void ScanConvertor::DrawLine(float x1, float y1, float x2, float y2)
{
	//dda line algorithm
	float x, y, incrx, incry;
	int len;
	float adx = fabs(x1-x2);
	float ady = fabs(y1-y2);

	if(adx==0.0f && ady==0.0f) {
		PutPixel((uint32)x1, (uint32)y1);
	}

	if(adx >= ady)
	{
		len = (int)adx;
		incrx = (x2-x1)/adx;
		incry = (y2-y1)/adx;  
	}
	else
	{
		len = (int)ady;
		incrx = (x2-x1)/ady;
		incry = (y2-y1)/ady;  
	}
	x = x1;
	y = y1;
	for(int i=0; i<len; i++)
	{
		PutPixel((uint32)x, (uint32)y);
		x += incrx;
		y += incry;
	}
}

void ScanConvertor::DrawLineDepthInterpolated(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//dda line algorithm
	float x, y, incrx, incry;
	int len;
	float cd,nd;
	int j;
	float adx=fabs(x1-x2);
	float ady=fabs(y1-y2);
	int cx,cy;
	int wt=width;
	int ht=height;
	
	if( adx == 0.0f &&  ady== 0.0f) {
		cx = (int)x1;
		cy = (int)y1;
		if(cx<0 || cx>=wt || cy<0 || cy>ht) { return; }
		nd = z1;
		j = cy*width + cx;
		cd = depthbuffer[j];
		if(nd > cd) {
			depthbuffer[j] = nd;
			PutPixel((uint32)cx, (uint32)cy);
		}
		return;
	}
	if(adx >= ady)
	{
		len = (int)adx;
		incrx = (x2-x1)/adx;
		incry = (y2-y1)/adx;  
		x = x1;
		y = y1;
		for(int i=0; i<len; i++)
		{
			cx = (int)x;
			cy = (int)y;
			if(cx<0 || cx>=wt || cy<0 || cy>ht) { return; }
			nd = z1 + ( (z2 - z1) * ((x - x1)/(x2-x1)) );
			j = cy*width + cx;
			cd = depthbuffer[j];
			if(nd < cd) {
				depthbuffer[j] = nd;
				PutPixel((uint32)cx, (uint32)cy);
			}
			x += incrx;
			y += incry;
		}
	}
	else
	{
		len = (int)ady;
		incrx = (x2-x1)/ady;
		incry = (y2-y1)/ady;  
		x = x1;
		y = y1;
		for(int i=0; i<len; i++)
		{
			cx = (int)x;
			cy = (int)y;
			if(cx<0 || cx>=wt || cy<0 || cy>ht) { return; }
			nd = z1 + ( (z2 - z1) * ((y - y1)/(y2-y1)) );
			j = cy*width + cx;
			cd = depthbuffer[j];
			if(nd < cd) {
				depthbuffer[j] = nd;
				PutPixel((uint32)cx, (uint32)cy);
			}
			x += incrx;
			y += incry;
		}
	}
}

void ScanConvertor::SetFrontFace(FaceType f)
{
	frontFace=f;
}
//A clockwise triangle will return a negative area.
//A counter-clockwise triangle will return a positive area.
float ScanConvertor::ComputeTraingleArea(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2)
{
	float area = 0.5f*((p0.x*p1.y - p1.x*p0.y) +
		(p1.x*p2.y - p2.x*p1.y) +
		(p2.x*p0.y - p0.x*p2.y));
	return area;
}
		
void ScanConvertor::DrawTriangle(const Vector3& a, const Vector3& b, const Vector3& c)
{
	float area = ComputeTraingleArea(a,b,c);
	if( ((frontFace == CCW)&&(area <= 0.0f)) || ((frontFace == CW)&&(area > 0.0f)) ) {
		return;
	}
	if(isDepthCheckEnabled) {
		DrawLineDepthInterpolated(a.x, a.y,a.z, b.x, b.y,b.z);
		DrawLineDepthInterpolated(b.x, b.y,b.z, c.x, c.y, c.z);
		DrawLineDepthInterpolated(c.x, c.y,c.z, a.x, a.y, a.z);
	} else {
		DrawLine(a.x, a.y, b.x, b.y);
		DrawLine(b.x, b.y, c.x, c.y);
		DrawLine(c.x, c.y, a.x, a.y);
	}
}

void ScanConvertor::Clear()
{
	uchar8 ac=clrColor.a;
	uchar8 rc=clrColor.r;
	uchar8 gc=clrColor.g;
	uchar8 bc=clrColor.b;
	uchar8* loc = buffer;
	unsigned int i=0;
	while(i<bufferSize) {
		*loc++ = bc; 
		*loc++ = gc; 
		*loc++ = rc; 
		*loc++ = ac;
		i+=4;
	}
}


void ScanConvertor::ClearDepth()
{
	unsigned int size = width*height;
	for(unsigned int i=0;i<size;i++){
		depthbuffer[i]=MAXDEPTH;
	}
}

void ScanConvertor::SetClearColor(ARGBCOLOR& c)
{
	clrColor=c;
}

void ScanConvertor::SetColor(ARGBCOLOR& c)
{
	curColor=c;
}

