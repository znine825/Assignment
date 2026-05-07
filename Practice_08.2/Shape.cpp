/*
shape.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Header file for implementing a class for shape information
*/

#include "Shape.h"

/* 매게변수 생성자 */
Shape::Shape(int px, int py, double angle, string name, int pen_thickness, COLORREF line_color, COLORREF brush_color) {
	this->pos_x = px;
	this->pos_y = py;
	this->angle = angle;
	this->name = name;
	this->pen_thickness = pen_thickness;
	this->line_color = line_color;
	this->brush_color = brush_color;
}

/* 대입을 위한 = 연산자 오버로딩 */
Shape& Shape::operator=(const Shape& s) {
	if (this != &s) {
		this->pos_x = s.pos_x;
		this->pos_y = s.pos_y;
		this->angle = s.angle;
		this->name = s.name;
		this->pen_thickness = s.pen_thickness;
		this->line_color = s.line_color;
		this->brush_color = s.brush_color;
	}
	return *this;
}


