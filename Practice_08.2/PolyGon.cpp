/*
PolyGon.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
-  Function file for implementing a class for PolyGon information
*/

#include "PolyGon.h"

/* 매게변수 생성자 */
PolyGon::PolyGon(int px, int py, int r, int n, double ang, string name, int pen_thick, COLORREF ln_clr, COLORREF br_clr)
	: Shape(px, py, ang, name, pen_thick, ln_clr, br_clr) {
	this->radius = r;
	this->num_poly = n;
}

/* 대입을 위한 = 연산자 오버로딩 */
PolyGon& PolyGon::operator=(const PolyGon& pol) {
	if (this != &pol) {
		Shape::operator=(pol);
		this->radius = pol.radius;
		this->num_poly = pol.num_poly;
	}
	return *this;
}

void PolyGon::draw() {
	cout << "draw() function of " << this->name << endl;
}
/* 도형 그리기 */
void PolyGon::draw(Win32GDIFrame& cp_frame) {
	std::vector<POINT> points(num_poly);
	int fr_px = cp_frame.get_cpfr_px() + pos_x;
	int fr_py = cp_frame.get_cpfr_py() + pos_y;
	double delta_angle = 2.0 * PI / num_poly;
	double rad_angle = PI / 2.0;
	for (int i = 0; i < num_poly; ++i, rad_angle += delta_angle)
	{
		points[i].x = static_cast<LONG>(
			std::round(fr_px + radius * std::cos(rad_angle))
			);
		points[i].y = static_cast<LONG>(
			std::round(fr_py - radius * std::sin(rad_angle))
			);
	}
	HDC hdc = cp_frame.getConsole_DC();
	if (hdc == nullptr)
		return;
	GDIPenBrush gdi(hdc, pen_thickness, line_color, brush_color);
	Polygon(hdc, points.data(), num_poly);
}