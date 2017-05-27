/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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


