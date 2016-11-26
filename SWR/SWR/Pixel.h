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
