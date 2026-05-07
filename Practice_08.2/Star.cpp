/*
Star.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
-  Function file for implementing a class for Star information
*/

#include "Star.h"

/* 매게변수 생성자 */
Star::Star(int px, int py, int r, int n, double ang, string name, int pen_thick, COLORREF ln_clr, COLORREF br_clr)
	: Shape(px, py, ang, name, pen_thick, ln_clr, br_clr) {
	this->radius = r;
	this->poly_num = n;
}

/* 대입을 위한 = 연산자 오버로딩 */
Star& Star::operator=(const Star& st) {
	if (this != &st) {
		Shape::operator=(st);
		this->radius = st.radius;
		this->poly_num = st.poly_num;
	}
	return *this;
}

void Star::draw() {
	cout << "draw() function of " << this->name << endl;
}

/* 도형 그리기 */
void Star::draw(Win32GDIFrame& cp_frame)
{
	const int total_points = poly_num * 2;
	std::vector<POINT> points(total_points);
	int fr_px = cp_frame.get_cpfr_px() + pos_x;
	int fr_py = cp_frame.get_cpfr_py() + pos_y;
	double outer_r = radius;
	double inner_r = radius * 0.45;
	double delta = 2.0 * PI / total_points;
	double rad_angle = PI / 2.0;
	for (int i = 0; i < total_points; ++i)
	{
		double r = (i % 2 == 0) ? outer_r : inner_r;
		points[i].x = static_cast<LONG>(
			std::round(fr_px + r * std::cos(rad_angle))
			);
		points[i].y = static_cast<LONG>(
			std::round(fr_py - r * std::sin(rad_angle))
			);
		rad_angle += delta;
	}
	HDC hdc = cp_frame.getConsole_DC();
	if (hdc == nullptr)
		return;
	GDIPenBrush gdi(hdc, pen_thickness, line_color, brush_color);
	Polygon(hdc, points.data(), total_points);
}