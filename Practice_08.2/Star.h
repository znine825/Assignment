/*
Star.h
Date : 2026-05-08
Author : Lee Jong Kwang
- A class that inherits from the shape class
- Header file for implementing a class for Star information
*/

#ifndef Star_H
#define Star_H
#include <string>
#include "Shape.h"

/* 클래스 Star */
class Star : public Shape {
public:
	/* 매게변수 생성자 */
	Star(int px, int py, int r, int n, double ang, string name, int pen_thick, COLORREF ln_clr, COLORREF br_clr);
	/* 대입을 위한 = 연산자 오버로딩 */
	Star& operator=(const Star& st);
	/* 소멸자 */
	~Star() override = default;

	/* 도형 그리기 */
	virtual void draw(Win32GDIFrame& cp_frame) override;
	virtual void draw() override;

private:
	int radius;
	int poly_num;
};
#endif