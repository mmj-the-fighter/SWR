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
#include "Pixel.h"

ARGBCOLOR MakeARGBCOLOR(int a, int r, int g, int b)
{
     ARGBCOLOR c;
     c.r = r; 
     c.g = g; 
     c.b = b; 
     c.a = a;
     return c;
}

void ColorCopy(ARGBCOLOR* dst, const ARGBCOLOR *src)
{
	dst->a = src->a;
	dst->r = src->r;
	dst->g = src->g;
	dst->b = src->b;
}
 
void ColorLerp(ARGBCOLOR* res, const ARGBCOLOR* c1, const ARGBCOLOR *c2,float t)
{
	res->r  =  (uchar8)(c1->r + (c2->r - c1->r) * t);
    res->g  =  (uchar8)(c1->g + (c2->g - c1->g) * t);
	res->b  =  (uchar8)(c1->b + (c2->b - c2->b) * t);
}

uint32 NextPowerOfTwo(uint32 x) 
{ 
  x = x - 1; 
  x = x | (x >> 1); 
  x = x | (x >> 2); 
  x = x | (x >> 4); 
  x = x | (x >> 8); 
  x = x | (x >>16); 
 return x + 1; 
} 


