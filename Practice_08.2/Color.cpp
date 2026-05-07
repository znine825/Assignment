/*
Color.cpp
Date : 2026-05-08
Author : Lee Jong Kwang
- Print color information in a visually appealing way
*/

#include <iostream>
#include <Windows.h>
#include "Color.h"

/* 보기 좋게 출력 */
ostream& fprintRGB(ostream& cout, const COLORREF color) {
    int r = color & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = (color >> 16) & 0xFF;

    cout << uppercase << hex << setfill('0')
        << "color("
        << setw(2) << r
        << setw(2) << g
        << setw(2) << b
        << ")";

    cout << dec;
    return cout;
}