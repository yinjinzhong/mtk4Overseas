//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
//-----------------------------------------------------------------------------


#include <windows.h>
#include"platform.h"
#include "resource.h"
#include "tvd_drv_if.h"
#include "backcar_msg.h"

BOOL NotifyVideoRenderReleaseVDPFin();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	

	switch (message) 
	{
	case WM_CREATE:
		
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, 
					SWP_NOMOVE | SWP_NOSIZE);        
		break;
	case WM_VIDEORENDER_MSG:
		#if 0
		if(VIDEORENDER_MSG_RELEASE_VDP_FIN == wParam)
		{
			RETAILMSG(TRUE, (TEXT("[fastcamera]videorender release VDP Finished\r\n")));
			NotifyVideoRenderReleaseVDPFin();
			   
		}
		#endif
		break;
	case  WM_FSC_BACKCAR_ACK_MSG:

		if(FSC_BACKCAR_ACK_RELEASE_RES_FIN == wParam)
		{
			RETAILMSG(TRUE, (TEXT("[fastcamera]Release Resouce  Finished\r\n")));
			NotifyVideoRenderReleaseVDPFin();
		}
	case WM_PAINT: 
		hdc = BeginPaint(hWnd, &ps);
		RECT rt;
		GetClientRect(hWnd, &rt);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




#if 0
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR     lpCmdLine,
                   int       nCmdShow)
{

	MSG msg;
	WNDCLASS					wc;
	HRESULT 					hRet;
	HWND hWnd = NULL;
   	HANDLE hBackCar = NULL;

	RETAILMSG(TRUE, (TEXT("[fastcamera]fastcameraui is running\r\n")));

	WaitForAPIReady(SH_GDI, INFINITE) ;
	//WaitForAPIReady(SH_SHELL, INFINITE);
	WaitForAPIReady(SH_COMM, INFINITE);
	WaitForAPIReady(SH_DDRAW, INFINITE);
       hBackCar = CreateEvent(0, FALSE, FALSE, BACKCAR_START_EVENT);

	// Set up and register window class
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NAME;
	hRet  = RegisterClass(&wc);
	if (!hRet)
	{

		RETAILMSG(TRUE, (TEXT("[fastcamera]RegisterClass FAILED[%d]\r\n"),GetLastError()));
		//return -1;
	}

	// Create a window
	hWnd = CreateWindow(
		NAME,
		TITLE,
		WS_VISIBLE,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
	   RETAILMSG(TRUE, (TEXT("[fastcamera]Create Window FAILED[%d]\r\n"),GetLastError()));
	   CloseHandle(hBackCar);
		return -1;
	}


	
	RETAILMSG(TRUE, (TEXT("Show Windows\r\n")));
	ShowWindow(hWnd, FALSE);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	Sleep(10000);	
	CreateThread(NULL, 0, BackCarListenThread, (LPVOID)hWnd, 0, NULL);
	Sleep(10);
	CreateThread(NULL, 0, BackCarThread, (LPVOID)hWnd, 0, NULL);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
#endif

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR     lpCmdLine,
                   int       nCmdShow)
{

	MSG msg;
	WNDCLASS					wc;
	HRESULT 					hRet;
	HWND hWnd = NULL;
   	HANDLE hBackCar = NULL;

	RETAILMSG(TRUE, (TEXT("[fastcamera]fastcameraui is running\r\n")));

	WaitForAPIReady(SH_GDI, INFINITE) ;
	//WaitForAPIReady(SH_SHELL, INFINITE);
	WaitForAPIReady(SH_COMM, INFINITE);
	WaitForAPIReady(SH_DDRAW, INFINITE);
       hBackCar = CreateEvent(0, FALSE, FALSE, BACKCAR_START_EVENT);

	/*		//modify owl 2012-11-14(del)
	// Set up and register window class
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NAME;
	hRet  = RegisterClass(&wc);
	if (!hRet)
	{

		RETAILMSG(TRUE, (TEXT("[fastcamera]RegisterClass FAILED[%d]\r\n"),GetLastError()));
		//return -1;
	}

	// Create a window
	hWnd = CreateWindow(
		NAME,
		TITLE,
		WS_VISIBLE,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
	   RETAILMSG(TRUE, (TEXT("[fastcamera]Create Window FAILED[%d]\r\n"),GetLastError()));
	   CloseHandle(hBackCar);
		return -1;
	}

	RETAILMSG(TRUE, (TEXT("Show Windows\r\n")));
	ShowWindow(hWnd, FALSE);
	UpdateWindow(hWnd);
	SetFocus(hWnd);
	*/			//modify owl 2012-11-14(del)
	//Sleep(10000);
	CreateThread(NULL, 0, BackCarListenThread, (LPVOID)hWnd, 0, NULL);
	Sleep(10);
			
	CreateThread(NULL, 0, BackCarThread, (LPVOID)hWnd, 0, NULL);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}