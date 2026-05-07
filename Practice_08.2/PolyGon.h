/*
PolyGon.h
Date : 2026-05-08
Author : Lee Jong Kwang
- A class that inherits from the shape class
- Header file for implementing a class for PolyGon information
*/

#ifndef PolyGon_H
#define PolyGon_H
#include <string>
#include "Shape.h"

/* 클래스 PolyGon */
class PolyGon : public Shape {
public:
	/* 매게변수 생성자 */
	PolyGon(int px, int py, int r, int n, double ang, string name, int pen_thick, COLORREF ln_clr, COLORREF br_clr);
	/* 대입을 위한 = 연산자 오버로딩 */
	PolyGon& operator=(const PolyGon& pol);
	/* 소멸자 */
	~PolyGon() override = default;

	/* 도형 그리기 */
	virtual void draw(Win32GDIFrame& cp_frame) override;
	virtual void draw() override;

protected:
	int radius;
	int num_poly;
};
#endif