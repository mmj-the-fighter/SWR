/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _PIXEL_H_
#define _PIXEL_H_

typedef unsigned char uchar8;
typedef unsigned int uint32;

struct ARGBCOLOR
{
    uchar8 a;
	uchar8 r;
	uchar8 g;
	uchar8 b;
};

struct RGBCOLOR
{
 	uchar8 r;
	uchar8 g;
	uchar8 b;
};


static const ARGBCOLOR c_blue = { 0,0,0,255 };
static const ARGBCOLOR c_black = { 0,0,0,0 };
static const ARGBCOLOR c_green = { 0,0,255,0 };
static const ARGBCOLOR c_red = { 0,255,0,0 };
static const ARGBCOLOR c_white = { 0,255,255,255 };

ARGBCOLOR MakeARGBCOLOR(int a, int r, int g, int b);
uint32 NextPowerOfTwo(uint32 x);
void ColorCopy(ARGBCOLOR* dst, const ARGBCOLOR *src);
void ColorLerp(ARGBCOLOR* res, ARGBCOLOR* c1, ARGBCOLOR *c2,float t);

#endif
