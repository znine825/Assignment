/*
Win32GDIFrame.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Function file for implementing classes and structures for drawing shapes
*/

#include "Win32GDIFrame.h"
#include "Shape.h"

/* 생성자 */
Win32GDIFrame::Win32GDIFrame()
	: paint_dc(nullptr), cpfr_px(0), cpfr_py(0) {
}

/* 매게변수 생성자 */
Win32GDIFrame::Win32GDIFrame(int x, int y)
	: paint_dc(nullptr), cpfr_px(x), cpfr_py(y) {
}

/* 지금 사용할 DC 저장 */
void Win32GDIFrame::setPaintDC(HDC hdc) {
	paint_dc = hdc;
}

HDC Win32GDIFrame::getConsole_DC() const {
	return paint_dc;
}

int Win32GDIFrame::get_cpfr_px() const {
	return cpfr_px;
}

int Win32GDIFrame::get_cpfr_py() const {
	return cpfr_py;
}

/* 도형 추가 */
void Win32GDIFrame::addShape(Shape* new_shape) {
	if (new_shape != nullptr)
		shapes.push_back(new_shape);
}

/* 도형 그리기 */
void Win32GDIFrame::drawShapes() {
	if (paint_dc == nullptr)
		return;
	for (Shape* shape : shapes)
	{
		if (shape != nullptr)
			shape->draw(*this);
	}
}