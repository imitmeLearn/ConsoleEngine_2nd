#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "Level/RBTLevel.h"

#include "Algorithm\AStar.h"

int main()
{
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine engine;
	engine.LoadLevel(new DemoLevel());
	engine.LoadLevel(new RBTLevel());
	engine.Run();

	/*
	//우클릭 또는 좌클릭 했을때, SE의 좌표를 확인하고, AStar알고리즘에 따라 지도를 그리는 기능.
	0. 레벨 에서 SE 생성할때, 저장하고,
	1. 입력을 확인하고
	2. s e 객체 위치를 받고
	3. s e 객체 Astar 알고리즘에 따라 경로를 그리기
	*/
}