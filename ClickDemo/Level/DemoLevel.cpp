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
//std::vector<std::vector<int>> grid =
//{
//};
//std::vector<std::vector<int>> grid =
//{
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1},
//	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
//	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1},
//	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
//	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
//	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1},
//	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//};
std::vector<std::vector<int>> grid =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1},
	{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,1,0,0,1,0,0,0,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1},
	{1,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,1},
	{1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1},
	{1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1},
	{1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1},
	{1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1},
	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void DemoLevel::DrawPath()
{
	AStar aStar;	//Astar 객체

	grid = origin_grid; //grid 초기화//선택한 영역이 벽인 경우에 사용

	// @Test.
	Node* startNode = new Node(start->Position());
	Node* goalNode = new Node(goal->Position());
	grid[startNode->Position().y][startNode->Position().x] = 0;
	grid[goalNode->Position().y][goalNode->Position().x] = 0;

	//grid[start->Position().y][start->Position().x] = 2;
	//grid[goal->Position().y][goal->Position().x] = 3;

	//for(int y = 0; y < (int)grid.size(); y++) //클릭해서, s e 설정하니, 없어도 됨! 이전엔 맵에서 읽었어야 했기에 사용.
	//{
	//	for(int x = 0; x < (int)grid[0].size(); x++)
	//	{
	//		//시작지점
	//		if(grid[y][x] ==2)
	//		{
	//			//startNode = new Node(start->Position());
	//			startNode.SetPosition(start->Position());
	//			grid[y][x] = 0;
	//			continue;
	//		}

	//		if(grid[y][x] ==3)
	//		{
	//			//goalNode = new Node(goal->Position());
	//			goalNode.SetPosition(goal->Position());
	//			grid[y][x] = 0;
	//			continue;
	//		}
	//	}
	//}

	std::vector<Node*> path_node =aStar.FindPath(startNode,goalNode,grid);	//경로탐색

	if(path_node.empty())
	{
		//	SafeDelete(goalNode);
		//	return;
			//std::cout<<" 경로 못 찾음. \n";
	}

	//std::cout << "경로 찾음.  탐색 경로:"<<'\n';

	for(Node* node : path_node)
	{
		// 경로는 '2'로 표시.
		grid[node->Position().y][node->Position().x] = 2;
	}
	// 액터 순회 후 삭제 요청된 액터를 처리. //초기화
	for(auto* actor : actors)
	{
		if(actor)
		{
			/*if(actor->As<Player>()
			|| actor->As<Start>()
				|| actor->As<Ground>()
				|| actor->As<Wall>()
			)
			{
				continue;
			}*/

			Path* path = actor->As<Path>();
			if(path)
			{
				Engine::Get().DestroyActor(actor);
				//delete actor;
				//actor = nullptr;
				continue;
			}
		}
	}
	//엑터 생성
	for(int y = 0; y < grid.size(); ++y)
	{
		for(int x = 0; x < grid[0].size(); ++x)
		{
			// 경로.
			if(grid[y][x] == 2)
				//else if(grid[y][x] == 2)
			{
				Path* path = new Path(Vector2(x,y));
				AddActor(path);
			}
		}
	}

	//SafeDelete(startNode);	//startNode는 openList 들어가기에, 해당부에서 지워짐. //또지우면 오류남.
	SafeDelete(goalNode);	//startNode는 openList 들어가기에, 해당부에서 지워짐. // 목표 노드만 제거 /목표노드는 안지우기에, 안지우면, 메모리릭 남.

	//isDraw = true;
}

bool DemoLevel::IsClickedOutofMap()
{
	//SE 를 클릭한 경우
	if(goal->Position() ==  Engine::Get().MousePosition()
||start->Position() ==  Engine::Get().MousePosition())
	{
		return true;
	}

	//맵 밖을 클릭한 경우
	if(this->origin_grid.size() -1<  Engine::Get().MousePosition().y
			|| this->origin_grid[0].size()-1 <  Engine::Get().MousePosition().x
			)
	{
		auto checkc = this->origin_grid.size() <  Engine::Get().MousePosition().y
			|| this->origin_grid[0].size()-1 <  Engine::Get().MousePosition().x
			;
		return true;
	}
	/*if(Engine::Get().ScreenSize().x > Engine::Get().MousePosition().x
		||Engine::Get().ScreenSize().y > Engine::Get().MousePosition().y
		)
	{
		return false;
	}*/

	//벽 클릭한 경우
	for(auto* actor : maps)
	{
		if(actor->As<Wall>())
		{
			if(actor->Position() == Engine::Get().MousePosition())
			{
				return true;
			}
		}
	}

	return false;
}

void DemoLevel::InitSetMapActors()
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
				maps.PushBack(wall->As<DrawableActor>());
			}
			// 빈 공간.
			else if(grid[y][x] == 0)
			{
				Ground* gound = new Ground(Vector2(x,y));
				AddActor(gound);
				maps.PushBack(gound->As<DrawableActor>());
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

	InitSetMapActors();
	origin_grid = grid;
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void DemoLevel::Draw()
{
	if(maps.Size() >0)
	{
		for(auto* actor : maps)
		{
			if(actor)
			{
				actor -> Draw();	//맵 액터 그리기
				continue;
			}
		}
	}
	//	Game::Get().SetCursorPosition(0,0);			//1단계 : 콘솔 좌표 옮기기'
	List <Path*> paths;

	for(auto* actor : actors)
	{
		Path* path = actor->As<Path>();
		if(path)
		{
			paths.PushBack(path);
		}
	}

	for(auto* actor:paths)
	{
		actor -> Draw();
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