/*
Win32GDIFrame.h
Date : 2026-05-08
Author : Lee Jong Kwang
- Header file for implementing classes and structures for drawing shapes
*/

#ifndef WIN32_GDI_FRAME_H
#define WIN32_GDI_FRAME_H
#include <Windows.h>
#include <vector>
class Shape;

/* Win32GDIFrame 클래스 */
class Win32GDIFrame {
public:
	/* 생성자 */
	Win32GDIFrame();
	/* 매게변수 생성자 */
	Win32GDIFrame(int x, int y);
	/* 지금 사용할 DC 저장 */
	void setPaintDC(HDC hdc);
	HDC getConsole_DC() const;
	int get_cpfr_px() const;
	int get_cpfr_py() const;
	/* 도형 추가 */
	void addShape(Shape* new_shape);
	/* 도형 그리기 */
	void drawShapes();
private:
	/* 템플릿 클래스 이용 */
	std::vector<Shape*> shapes;
	HDC paint_dc = nullptr;
	int cpfr_px = 0;
	int cpfr_py = 0;
};

/* 브러시 관리 구조체 */
struct GDIPenBrush {
	HDC hdc;
	HPEN new_pen;
	HPEN old_pen;
	HBRUSH new_brush;
	HBRUSH old_brush;

	GDIPenBrush(HDC hdc, int thickness, COLORREF line_color, COLORREF brush_color) : hdc(hdc) {
		new_pen = CreatePen(PS_SOLID, thickness, line_color);
		new_brush = CreateSolidBrush(brush_color);
		old_pen = static_cast<HPEN>(SelectObject(hdc, new_pen));
		old_brush = static_cast<HBRUSH>(SelectObject(hdc, new_brush));
	}

	~GDIPenBrush() {
		SelectObject(hdc, old_pen);
		SelectObject(hdc, old_brush);
		DeleteObject(new_pen);
		DeleteObject(new_brush);
	}
};
#endif