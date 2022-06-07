#pragma once

const int Width = 600;
const int Height = 600;

template <typename _A> void Swap(_A&, _A&);
void glText(const char*, int = 0, int = 0, int = 0);
char* Char(int);
void glBar(float left, float up, float right, float down);