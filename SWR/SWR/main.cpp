/*
Copyright 2016 Manoj M J

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "Pixel.h"
#include "Matrix.h"
#include "ScanConvertor.h"
#include "Mesh.h"
#include "VertexProcessor.h"

#define MOVESPEED 1.0f

void DisplayPixels( HWND hwnd, ScanConvertor* scr);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MoveCamera(float dx, float dz);

Matrix4x4 mMat,mMat2,vMat,pMat;

float angle = 0.0f;
float angleIncr = 20.0f;

Vector3 eye={0, 0, 5},at={0,0,0},up={0,1,0};
//Vector3 eye={0, 0, -5},at={0,0,-10},up={0,1,0};
VertexProcessor vp;

bool reDisplay = TRUE;

float cubeverts[] = 
{
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f
};

int cubeindices[] =
{
    1, 2, 3,
    1, 3, 4,
    2, 7, 3,
    2, 6, 7,
    6, 5, 8,
    6, 8, 7,
    5, 1, 4,
    5, 4, 8,
    4, 3, 7,
    4, 7, 8,
    5, 6, 2,
    5, 2, 1
};


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR lpszArgs, int nShowCmd)
{
    HWND hwnd;               
    MSG messages;
    BOOL bQuit = FALSE;
    WNDCLASSEX wincl;        
    
    wincl.hInstance = hInst;
    wincl.lpfnWndProc = WndProc;
    wincl.style         = CS_HREDRAW | CS_VREDRAW ;
    wincl.cbClsExtra    = 0 ;
    wincl.cbWndExtra    = 0 ;
    wincl.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
    wincl.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wincl.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wincl.lpszMenuName  = NULL ;
    wincl.lpszClassName = L"SWR";
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx(0, L"SWR", L"SWRWindow", 
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          640,480,HWND_DESKTOP, NULL, hInst, NULL);

    ShowWindow (hwnd, nShowCmd);
	reDisplay = TRUE;
	vp.Init(640, 480);
	vp.scr->EnableDepthCheck(false);
	//vp.SetDrawMode(SWRPOINTS);
	Mesh mesh;
	mesh.LoadObj(".\\Models\\Ninja.obj");
	Mesh mesh2;
	mesh2.AddVertexArray(cubeverts, 24);
	mesh2.AddIndicesArray(cubeindices, 36);
	//mesh2.LoadObj(".\\Models\\micronapalmv2.obj");

	while(!bQuit) {
		if( PeekMessage(&messages, NULL, 0, 0, PM_REMOVE) ) {
			if( messages.message == WM_QUIT ) {
				bQuit = TRUE;
			} else  {
                TranslateMessage(&messages);
                DispatchMessage(&messages);
            }
		} else {
			if( reDisplay == TRUE ) {
				ARGBCOLOR c = c_blue;
				vp.scr->SetClearColor(c);
				vp.scr->Clear();
				vp.scr->ClearDepth();

				mMat.SetRotationY(angle);

				angle += angleIncr; if(angle >359.0) angle = 0.0f;

				//vMat.SetIdentity();
				//pMat.SetOrtho(-2.0f,2.0f,-2.0f,2.0f,-1.0f,1.0f);

				vMat.SetLookAt(eye,at,up);
				pMat.SetPerspective(60.0,1.0,1.0,20);

				vp.SetModelMatrix(mMat);
				vp.SetViewMatrix(vMat);
				vp.SetProjectionMatrix(pMat);
				vp.SetViewPort(0,0, 640, 480);

				//vp.SetDrawMode(SWRWIREFRAME);
				//vp.SetDrawMode(SWRPOINTS);
				vp.DrawMesh(mesh);

				mMat.SetTranslation(0,0,1);
				Matrix4x4 scaleMat, rotMat, temp;
				scaleMat.SetScale(0.5,0.5,0.5);
				rotMat.SetRotationX(angle);

				Matrix4x4::Multiply(temp,rotMat,scaleMat);
				Matrix4x4::Multiply(mMat,mMat,temp);
				vp.SetModelMatrix(mMat);
				vp.DrawMesh(mesh2);

				DisplayPixels(hwnd,vp.scr);
				reDisplay = FALSE;
			}
		}
    }
    return messages.wParam;
}

void MoveCamera(float dx, float dz) {
	Vector3 u,n,tu,tn;
	vMat.GetViewUAxis(u);
	vMat.GetViewNAxis(n);
	
    //eye = eye + dx * u 
	Vec3Norm(tu, u);
	Vec3Scale(tu, tu, dx);
	Vec3Add(eye, eye, tu);
	Vec3Add(at, at, tu);

    //eye = eye + dz * n
	Vec3Norm(tn, n);
	Vec3Scale(tn, tn, dz);
	Vec3Add(eye, eye, tn);
	Vec3Add(at, at, tn);

	vMat.SetLookAt(eye,at,up);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     switch (message)
     {     
	 case WM_CREATE:
          SetTimer (hwnd, 1, 33, NULL) ;
          return 0 ;

	 case WM_TIMER:
          reDisplay = TRUE;
          return 0 ;

	 case WM_KEYDOWN:
		 switch(wParam)
		 {
		 case VK_ESCAPE:
			 KillTimer(hwnd, 1);
			 PostQuitMessage (0);
			 return 0 ;
		 case VK_UP:
			 MoveCamera(0,-MOVESPEED);
			 return 0;
		 case VK_DOWN:
			 MoveCamera(0,MOVESPEED);
			 return 0;
		 case VK_LEFT:
			 MoveCamera(-MOVESPEED,0);
			 return 0;
		 case VK_RIGHT:
			 MoveCamera(MOVESPEED,0);
			 return 0;
		 }
		 return 0;
     case WM_DESTROY:
		  KillTimer (hwnd, 1) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

void DisplayPixels( HWND hwnd, ScanConvertor* scr)
{
	 HDC hdc;
     LPVOID pvBits;
     BITMAPINFO bmi;
     ZeroMemory(&bmi, sizeof(BITMAPINFO));
	 bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);// size of the structure
     bmi.bmiHeader.biWidth = scr->width;// width of the image in pixels
     bmi.bmiHeader.biHeight = scr->height;// height of the image in pixels
	 bmi.bmiHeader.biHeight = -bmi.bmiHeader.biHeight;//flip y axis
     bmi.bmiHeader.biPlanes = 1;
     bmi.bmiHeader.biBitCount = scr->bytesPerPixel*8; // bits per pixel (1, 4, 8, 16, 24, or 32)
     bmi.bmiHeader.biCompression = BI_RGB;
     bmi.bmiHeader.biSizeImage = scr->bufferSize;// number of bytes in image

     hdc = GetDC(hwnd);
	 
	 HBITMAP hbitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0x0);
	 memcpy(pvBits, scr->buffer, scr->bufferSize);

	 StretchDIBits(
		 hdc, //destination device context
		 0, 0, scr->width, scr->height, //destination coordinates 
		 0, 0, scr->width, scr->height, //source coordinates
		 pvBits, //dib bits
		 &bmi, //dib info
		 DIB_RGB_COLORS, 
		 SRCCOPY//raster operation
		 );
	 DeleteObject(hbitmap);
	
	 ReleaseDC(hwnd,hdc);
}
