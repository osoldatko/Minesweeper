#pragma once

#include "Scoretime.h"
#include "stdafx.h"
#include "Game.h"


bool _Game::Set(int xPos, int yPos)
{

	if (xPos >= 0 && xPos < MAP_SIZE && yPos >= 0 && yPos < MAP_SIZE && Map[xPos][yPos] != BOMB)
		return true;
	else
		return false;
}

void _Game::Init()
{
	Win = false;
	Bombed = false;
	srand(time(0));
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
		{
			Map[i][j] = EMPTY;
			Visible[i][j] = NO;
		}

	for (int i = 0; i < MAX_BOMBS; i++)
	{
		int xIndex = rand() % MAP_SIZE;
		int yIndex = rand() % MAP_SIZE;

		if (Map[xIndex][yIndex] == BOMB)
		{
			i--;
			continue;
		}

		Map[xIndex][yIndex] = BOMB;
	}

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			if (Map[i][j] == BOMB)
			{
				if (Set(i - 1, j - 1))
					Map[i - 1][j - 1]++;
				if (Set(i, j - 1))
					Map[i][j - 1]++;
				if (Set(i + 1, j - 1))
					Map[i + 1][j - 1]++;
				if (Set(i + 1, j))
					Map[i + 1][j]++;
				if (Set(i + 1, j + 1))
					Map[i + 1][j + 1]++;
				if (Set(i, j + 1))
					Map[i][j + 1]++;
				if (Set(i - 1, j + 1))
					Map[i - 1][j + 1]++;
				if (Set(i - 1, j))
					Map[i - 1][j]++;
			}

}

void _Game::Draw()
{
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	const int Len = Width / MAP_SIZE;
	for (int i = 0; i <= Width - Len; i += Len)
	{
		glVertex2f(0, i);
		glVertex2f(Width, i);
		glVertex2f(i, 0);
		glVertex2f(i, Height);
	}
	glEnd();

	if (Win)
	{
		for (int i = 0; i < MAP_SIZE; i++)
			for (int j = 0; j < MAP_SIZE; j++)
				if (Map[i][j] == BOMB)
				{
					glColor3f(3.0, 3.0, 3.0);
					glBar(j * Len + 1, i * Len + 2, j * Len + Len - 2, i * Len + Len - 1);
					glColor3f(0, 0, 0);
					glText("B", j * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, i * Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
				}
		time_t now2 = time(0);
		tm* ltm2 = localtime(&now2);
		int timegame2 = (ltm2->tm_sec + (ltm2->tm_min) * 60 + (ltm2->tm_hour) * 3600) - timegame1;
		
		glColor3f(0, 1, 0);
		glText("W", Width / 2 - 3 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("I", Width / 2 - 2 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("N", Width / 2 - 1 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("N", Width / 2 - 0 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("E", Width / 2 - -1 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("R", Width / 2 - -2 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("Score:", Width / 2 - -4 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - 10 * Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		std::ofstream fout;
		std::ifstream fin;
		fin.open("Score.txt");
		int timeg;
		fin >> timeg;
		if (timegame2 < timeg || timeg == 10000000)
		{
			fout.open("Score.txt");
			fout << timegame2;
			fout.close();
		}
		fin.close();
		fin.open("Score.txt");
		static char array[10];
		fin >> array;
		glText(array, Width / 2 - -6 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - 10 * Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		fin.close();
		return;
	}

	if (Bombed)
	{
		for (int i = 0; i < MAP_SIZE; i++)
			for (int j = 0; j < MAP_SIZE; j++)
				if (Map[i][j] == BOMB)
				{
					glColor3f(1, 1, 1);
					glBar(j * Len + 1, i * Len + 2, j * Len + Len - 2, i * Len + Len - 1);
					glColor3f(0, 0, 0);
					glText("B", j * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, i * Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
				}
		glColor3f(1, 0, 0);
		glText("B", Width / 2 - 2 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("O", Width / 2 - 1 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("M", Width / 2 - 0 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		glText("B", Width / 2 - -1 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		//glText("Score:", Width / 2 - -4 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - 10 * Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		//glText("fail", Width / 2 - -6 * Len + Len / 2 - Len / 10 - MAP_SIZE / 3, Height / 2 - 10 * Len + Len / 2 + Len / 10 + MAP_SIZE / 3);
		return;
	}

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (Visible[i][j] == YES)
			{
				if (Map[i][j] == EMPTY)
					glColor3f(0.7, 0.7, 0.7);
				else
					glColor3f(1.0, 1.0, 1.0);
				glBar(j * Len + 1, i * Len + 2, j * Len + Len - 2, i * Len + Len - 1);

				if (Map[i][j] == EMPTY)
					glColor3f(0.7, 0.7, 0.7);
				else
					glColor3f(0, 0, 0);
				glText(Char(Map[i][j]), j * Len + Len / 2 - Len / 10 - 2, i * Len + Len / 2 + Len / 10 + 2);
			}
			else if (Visible[i][j] == FLAG)
			{
				glColor3f(0.5, 0.0, 0.0);
				glBar(j * Len + 1, i * Len + 2, j * Len + Len - 2, i * Len + Len - 1);
			}
		}
}

void _Game::Check(int yPos, int xPos)
{
	xPos /= Width / MAP_SIZE;
	yPos /= Width / MAP_SIZE;

	if (Visible[xPos][yPos] == FLAG)
		return;

	if (Map[xPos][yPos] == BOMB)
	{
		Bombed = true;
		return;
	}

	Visible[xPos][yPos] = YES;

	if (Map[xPos][yPos] == EMPTY)
		Open(xPos, yPos);

	End();

	if (Bombed || Win)
		Init();
}

void _Game::Flag(int yPos, int xPos)
{
	xPos /= Width / MAP_SIZE;
	yPos /= Width / MAP_SIZE;

	if (Visible[xPos][yPos] == FLAG)
		Visible[xPos][yPos] = NO;
	else if (Visible[xPos][yPos] == NO)
		Visible[xPos][yPos] = FLAG;

	End();
}

void _Game::Open(int xPos, int yPos)
{
	if (Get(xPos - 1, yPos - 1))
		Open(xPos - 1, yPos - 1);

	if (Get(xPos, yPos - 1))
		Open(xPos, yPos - 1);

	if (Get(xPos + 1, yPos - 1))
		Open(xPos + 1, yPos - 1);

	if (Get(xPos + 1, yPos))
		Open(xPos + 1, yPos);

	if (Get(xPos + 1, yPos + 1))
		Open(xPos + 1, yPos + 1);

	if (Get(xPos, yPos + 1))
		Open(xPos, yPos + 1);

	if (Get(xPos - 1, yPos + 1))
		Open(xPos - 1, yPos + 1);

	if (Get(xPos - 1, yPos))
		Open(xPos - 1, yPos);
}

bool _Game::Get(int xPos, int yPos)
{
	if (xPos == -1 || xPos == MAP_SIZE)
		return false;
	if (yPos == -1 || yPos == MAP_SIZE)
		return false;
	if (Map[xPos][yPos] == BOMB)
		return false;
	if (Visible[xPos][yPos] == FLAG)
		return false;
	if (Visible[xPos][yPos] == YES)
		return false;

	Visible[xPos][yPos] = YES;

	if (Map[xPos][yPos] != EMPTY)
		return false;
	return true;
}

void _Game::End()
{
	int k = 0;
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			if (Visible[i][j] == FLAG && Map[i][j] == BOMB)
				k++;

	if (k == MAX_BOMBS)
		Win = true;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int timegame1 = ltm->tm_sec + (ltm->tm_min) * 60 + (ltm->tm_hour) * 3600;
}