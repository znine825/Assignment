/*
Shape.h
Date : 2026-05-08
Author : Lee Jong Kwang
- Header file for implementing a class for shape information
*/

#ifndef SHAPE_H
#define SHAPE_H
#include "Color.h"
#include "Win32GDIFrame.h"

#define PI 3.14159

using namespace std;

class Shape {
public:
	/* 매게변수 생성자 */
	Shape(int px, int py, double angle, string name, int pen_thickness, COLORREF line_color, COLORREF brush_color);
	/* 대입을 위한 = 연산자 오버로딩 */
	Shape& operator=(const Shape& s);
	/* 소멸자 */
	virtual ~Shape() {}
	/* 가상함수 | 그리기 */
	virtual void draw(Win32GDIFrame& cp_frame) = 0;
	virtual void draw() = 0;

protected:
	int pos_x;
	int pos_y;
	double angle;
	string name;
	int pen_thickness = 1;
	COLORREF line_color = RGB_BLACK;
	COLORREF brush_color = RGB_WHITE;
};
#endif