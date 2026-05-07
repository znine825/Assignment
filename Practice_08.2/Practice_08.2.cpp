/*
Practice_08.2.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Save shape information to a class
- Draw on the screen in pixel units using the class function Draw
*/

#include <windows.h>
#include <tchar.h>
#include "Win32GDIFrame.h"
#include "Shape.h"
#include "PolyGon.h"
#include "Star.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
/* 그릴 도형들 클래스로 정의 */
static PolyGon g_poly5(100, 100, 80, 5, 0.0, "Polygon_5", 4, RGB_BLACK, RGB_GREEN);
static PolyGon g_poly6(300, 100, 80, 6, 0.0, "Polygon_6", 4, RGB_BLACK, RGB_BLUE);
static PolyGon g_poly7(500, 100, 80, 7, 0.0, "Polygon_7", 4, RGB_BLACK, RGB_MAGENTA);
static Star g_star5(100, 300, 80, 5, 0.0, "Star_5", 4, RGB_BLACK, RGB_RED);
static Star g_star6(300, 300, 80, 6, 0.0, "Star_6", 4, RGB_BLACK, RGB_GREEN);
static Star g_star7(500, 300, 80, 7, 0.0, "Star_7", 4, RGB_BLACK, RGB_YELLOW);
static Win32GDIFrame g_frame(50, 50);
static bool g_initialized = false;

static void InitializeShapesOnce()
{
	if (g_initialized)
		return;
	g_frame.addShape(&g_poly5);
	g_frame.addShape(&g_poly6);
	g_frame.addShape(&g_poly7);
	g_frame.addShape(&g_star5);
	g_frame.addShape(&g_star6);
	g_frame.addShape(&g_star7);
	g_initialized = true;
}

/* 메인 함수 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
	const TCHAR CLASS_NAME[] = TEXT("PixelDrawingPolymorphismWindow");
	WNDCLASS wc = { };
	/* Window 기본 정의 */
	wc.lpfnWndProc = WndProc; /* 이벤트 함수 정의 */
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME; /* 이름 정의 */
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); /* 커서 모양 정의 */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); /* 배경 색 정의 */
	if (!RegisterClass(&wc)) {
		MessageBox(NULL, TEXT("RegisterClass failed."), TEXT("Error"), MB_ICONERROR);
		return 0;
	}
	/* 창 생성 */
	HWND hwnd = CreateWindowEx(
		0, CLASS_NAME, TEXT("Pixel Drawing Polymorphism - GUI Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		900, 750, NULL, NULL, hInstance, NULL);

	/* 화면으로 표시 */
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	/* 이벤트 확인 후 전달 */
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

/* 모든 이벤트 처리 함수 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		/* 처음 실행시, 한번만 실행*/
	case WM_CREATE:
		InitializeShapesOnce();
		return 0;
		/* 화면 그리기 */
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		g_frame.setPaintDC(hdc);
		g_frame.drawShapes();
		SetBkMode(hdc, TRANSPARENT);
		const wchar_t title[] = L"WM_PAINT based drawing using inheritance and polymorphism";
		TextOutW(hdc, 40, 20, title, static_cast<int>(wcslen(title)));
		EndPaint(hwnd, &ps);
		return 0;
	}
	/* 화면 끌때*/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}