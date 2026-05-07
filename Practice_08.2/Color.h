/*
Color.h
Date : 2026-05-08
Author : Lee Jong Kwang
- Define and output color information
*/

#ifndef COLOR_H
#define COLOR_H
#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/* 색을 hex로 정의 */
const COLORREF RGB_RED = 0x000000FF;
const COLORREF RGB_GREEN = 0x0000FF00;
const COLORREF RGB_BLUE = 0x00FF0000;
const COLORREF RGB_BLACK = 0x00000000;
const COLORREF RGB_ORANGE = 0x0000A5FF;
const COLORREF RGB_YELLOW = 0x0000FFFF;
const COLORREF RGB_MAGENTA = 0x00FF00FF;
const COLORREF RGB_WHITE = 0x00FFFFFF;
/* 보기 좋게 출력 */
ostream& fprintRGB(ostream& ostr, const COLORREF color);

#endif