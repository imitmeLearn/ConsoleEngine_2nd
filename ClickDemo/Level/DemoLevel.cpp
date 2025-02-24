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
	if(!startNode && !goalNode)
	{
		std::cout<<"Node null";
		return;
	}

	if(!path_node.empty())
	{
		std::cout<<"path not null";

		path_node.clear();
	}

	startNode = new Node(start->Position());
	goalNode = new Node(goal->Position());
	grid[start->Position().y][start->Position().x] = 2;
	grid[goal->Position().y][goal->Position().x] = 3;

	for(int y = 0; y < (int)grid.size(); y++)
	{
		for(int x = 0; x < (int)grid[0].size(); x++)
		{
			//시작지점
			if(grid[y][x] ==2)
			{
				//startNode = new Node(x,y);
				grid[y][x] = 0;
				continue;
			}

			if(grid[y][x] ==3)
			{
				//goalNode = new Node(x,y);
				grid[y][x] = 0;
				continue;
			}
		}
	}
	path_node = aStar->FindPath(startNode,goalNode,grid);	//경로탐색

	if(path_node.empty())
	{
		std::cout<<" 경로 못 찾음. \n";
	}

	std::cout << "경로 찾음.  탐색 경로:"<<'\n';

	for(Node* node : path_node)
	{
		// 경로는 '2'로 표시.
		grid[node->Position().y][node->Position().x] = 2;
	}
	DrawMap();
}

void DemoLevel::DrawMap()
{
	for(int y = 0; y < grid.size(); ++y)
	{
		for(int x = 0; x < grid[0].size(); ++x)
		{
			// 벽
			if(grid[y][x] == 1)
			{
				//Wall* wall = new Wall(Vector2(x,y));
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

		std::cout << "\n";
	}
}

DemoLevel::DemoLevel()
{
	SetActor(NodeType::START,AddActor(new Start(this),0));
	SetActor(NodeType::GOAL,AddActor(new Player(this),1));

	aStar =new AStar();	//Astar 객체

	//startNode = new Node();
	//goalNode = new Node();

	startNode = new Node(start->Position());
	goalNode = new Node(goal->Position());

	DrawMap();
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
		Wall* wall = actor->As<Wall>();
		if(wall)
		{
			walls.PushBack(wall);
		}

		Ground* ground = actor->As<Ground>();
		if(ground)
		{
			grounds.PushBack(ground);
		}

		Path* path = actor->As<Path>();
		if(path)
		{
			paths.PushBack(path);
		}
	}

	for(auto* actor:walls)
	{
		actor -> Draw();
	}

	for(auto* actor:grounds)
	{
		bool shouldDraw = true;
		for(auto* path : paths)
		{
			if(actor->Position() == path->Position())
			{
				shouldDraw = false;
				break;
			}
		}
		if(shouldDraw)
		{
			actor -> Draw();	//맵 액터 그리기
		}
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