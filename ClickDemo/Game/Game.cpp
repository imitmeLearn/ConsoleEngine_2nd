#include "Game.h"

Game* Game::instance = nullptr;

Game::Game():Engine()
{
	instance = this;
}

void Game::SetCursorPosition(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {static_cast<short>(x),static_cast<short>(y)};
	SetConsoleCursorPosition(handle,coord);
}

Game::~Game()
{
	//startNode->~Node();
	//goalNode->~Node();
	//aStar.~AStar();
}