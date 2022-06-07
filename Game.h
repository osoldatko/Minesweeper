#pragma once

#include "Constants.h"

class _Game
{
private:

	static const int MAP_SIZE = 20;
	static const int MAX_BOMBS = MAP_SIZE * 2;

	int Map[MAP_SIZE][MAP_SIZE];
	enum { EMPTY = 0, BOMB = 9 };
	enum _Visible { NO, YES, FLAG } Visible[MAP_SIZE][MAP_SIZE];

	bool Bombed;
	bool Win;

	bool Set(int, int);
	void Init();
	void Open(int, int);
	bool Get(int, int);
	void End();

public:

	_Game() { Init(); }
	void Draw();
	void Check(int, int);
	void Flag(int, int);
};