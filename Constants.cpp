#pragma once
#pragma warning(disable : 4996)
#include "stdafx.h"
#include "Constants.h"

template <typename _A> void Swap(_A& _Left, _A& _Right)
{
	_A _Temp = _Right;
	_Right = _Left;
	_Left = _Temp;
}

char* Char(int _Value)
{
	char* Buf = new char[10];
	itoa(_Value, Buf, 10);
	return Buf;
}

void glText(const char* _Text, int x, int y, int z)
{
	glRasterPos3f(x, y, z);
	for (int i = 0; i < strlen(_Text); i++)
		glutBitmapCharacter((void*)8, _Text[i]);
}

void glBar(float left, float up, float right, float down)
{
	glBegin(GL_QUADS);
	glVertex2f(left, down);
	glVertex2f(right, down);
	glVertex2f(right, up);
	glVertex2f(left, up);
	glEnd();
}