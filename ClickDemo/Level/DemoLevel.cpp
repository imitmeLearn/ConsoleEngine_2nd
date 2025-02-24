#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include <Actor/AStarMap/Wall.h>
#include "Actor/AStarMap/Path.h"
#include "Actor/AStarMap/Ground.h"

#include "Engine/Engine.h"
#include "Algorithm\AStar.h"
#include "Algorithm\Node.h"

#include "Game/Game.h"

void DemoLevel::SetActor(NodeType type,Actor* actor)
{
	switch(type)
	{
	case DemoLevel::START:
	start = actor->As<DrawableActor>();

	break;
	case DemoLevel::GOAL:
	goal = actor->As<DrawableActor>();

	break;
	case DemoLevel::count:
	break;
	default:
	break;
	}
}

std::vector<std::vector<int>> grid =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void DemoLevel::DrawPath()
{
	AStar aStar;	//Astar 객체

	grid = origin_grid; //grid 초기화
	std::vector<Node*> path_node;

	Node* startNode = nullptr;
	Node* goalNode = nullptr;

	grid[start->Position().y][start->Position().x] = 2;
	grid[goal->Position().y][goal->Position().x] = 3;

	for(int y = 0; y < (int)grid.size(); y++)
	{
		for(int x = 0; x < (int)grid[0].size(); x++)
		{
			//시작지점
			if(grid[y][x] ==2)
			{
				startNode = new Node(start->Position());
				grid[y][x] = 0;
				continue;
			}

			if(grid[y][x] ==3)
			{
				goalNode = new Node(goal->Position());
				grid[y][x] = 0;
				continue;
			}
		}
	}
	path_node = aStar.FindPath(startNode,goalNode,grid);	//경로탐색

	if(path_node.empty())
	{
		std::cout<<" 경로 못 찾음. \n";
	}

	std::cout << "경로 찾음.  탐색 경로:"<<'\n';

	// 액터 순회 후 삭제 요청된 액터를 처리. //초기화
	for(auto* actor : actors)
	{
		if(actor)
		{
			if(actor->As<Player>()
			|| actor->As<Start>()
			|| actor->As<Wall>())
			{
				continue;
			}
			delete actor;
			actor = nullptr;
			continue;
		}
	}

	for(Node* node : path_node)
	{
		// 경로는 '2'로 표시.
		grid[node->Position().y][node->Position().x] = 2;
	}

	//엑터 생성
	for(int y = 0; y < grid.size(); ++y)
	{
		for(int x = 0; x < grid[0].size(); ++x)
		{
			// 벽
			if(grid[y][x] == 1)
			{
				Wall* wall = new Wall(Vector2(x,y));
				AddActor(wall);
			}
			// 빈 공간.
			else if(grid[y][x] == 0)
			{
				Ground* gound = new Ground(Vector2(x,y));
				AddActor(gound);
			}
			// 경로.
			else if(grid[y][x] == 2)
			{
				Path* path = new Path(Vector2(x,y));
				AddActor(path);
			}
		}
	}
	aStar.~AStar();

	startNode->~Node();
	goalNode->~Node();
	//SafeDelete(goalNode);	//목표 노드만 제거
}

void DemoLevel::DrawMaps()
{
	//엑터 생성
	for(int y = 0; y < grid.size(); ++y)
	{
		for(int x = 0; x < grid[0].size(); ++x)
		{
			// 벽
			if(grid[y][x] == 1)
			{
				Wall* wall = new Wall(Vector2(x,y));
				AddActor(wall);
			}
			// 빈 공간.
			else if(grid[y][x] == 0)
			{
				Ground* gound = new Ground(Vector2(x,y));
				AddActor(gound);
			}
			// 경로.
			else if(grid[y][x] == 2)
			{
				Path* path = new Path(Vector2(x,y));
				AddActor(path);
			}
		}
	}
}

//void DemoLevel::SetActors()
//void DemoLevel::SetActors(std::vector<std::vector<int>>& grid,const std::vector<Node*>& path_node)
//void DemoLevel::SetActors(std::vector<std::vector<int>>& grid)
//{
//	// 액터 순회 후 삭제 요청된 액터를 처리.
//	for(auto* actor : actors)
//	{
//		if(actor)
//		{
//			if(actor->As<Player>()
//			|| actor->As<Start>()
//			|| actor->As<Wall>())
//			{
//				continue;
//			}
//			delete actor;
//			actor = nullptr;
//			continue;
//		}
//	}
//
//	//엑터 생성
//	for(int y = 0; y < grid.size(); ++y)
//	{
//		for(int x = 0; x < grid[0].size(); ++x)
//		{
//			// 벽
//			if(grid[y][x] == 1)
//			{
//				Wall* wall = new Wall(Vector2(x,y));
//				AddActor(wall);
//			}
//			// 빈 공간.
//			else if(grid[y][x] == 0)
//			{
//				Ground* gound = new Ground(Vector2(x,y));
//				AddActor(gound);
//			}
//			// 경로.
//			else if(grid[y][x] == 2)
//			{
//				Path* path = new Path(Vector2(x,y));
//				AddActor(path);
//			}
//		}
//	}
//
//	SafeDelete(goaltNode);	//목표 노드만 제거
//}

DemoLevel::DemoLevel()
{
	SetActor(NodeType::START,AddActor(new Start(this),0));
	SetActor(NodeType::GOAL,AddActor(new Player(this),1));

	//startNode = new Node(start->Position());
	//goalNode = new Node(goal->Position());

	DrawMaps();
	origin_grid = grid;
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void DemoLevel::Draw()
{
	//	Game::Get().SetCursorPosition(0,0);			//1단계 : 콘솔 좌표 옮기기'
	List<Wall*> walls;
	List <Ground*> grounds;
	List <Path*> paths;

	for(auto* actor : actors)
	{
		Ground* ground = actor->As<Ground>();
		if(ground)
		{
			grounds.PushBack(ground);
		}
		Wall* wall = actor->As<Wall>();
		if(wall)
		{
			walls.PushBack(wall);
		}

		Path* path = actor->As<Path>();
		if(path)
		{
			paths.PushBack(path);
		}
	}

	for(auto* actor:grounds)
	{
		actor -> Draw();	//맵 액터 그리기
	}
	for(auto* actor:walls)
	{
		actor -> Draw();
	}

	for(auto* actor:paths)
	{
		actor -> Draw();	//맵 액터 그리기
	}

	if(start)
	{
		start->Draw();
	}
	if(goal)
	{
		goal->Draw();
	}
}