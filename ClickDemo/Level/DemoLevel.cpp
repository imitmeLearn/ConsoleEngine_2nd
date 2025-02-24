#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"

#include "Engine/Engine.h"
#include "Algorithm\AStar.h"
#include "Algorithm\Node.h"

void DemoLevel::SetActor(NodeType type,Actor* actor)
{
	switch(type)
	{
	case DemoLevel::START:
	start = actor;

	break;
	case DemoLevel::GOAL:
	goal = actor;

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
		std::cout<<"aa";
		return;
	}

	startNode = new Node(start->Position());
	goalNode = new Node(goal->Position());
	grid[start->Position().y][start->Position().x] = 2;
	grid[goal->Position().y][goal->Position().x] = 3;

	for(int y = 0; y < (int)grid.size(); y++)
	{
		//if(startNode && goalNode)	//이미 찾았다면, 종료
		//{
		//	break;
		//}

		for(int x = 0; x < (int)grid[0].size(); x++)
		{
			if(startNode && goalNode)	//이미 찾았다면, 종료
			{
				break;
			}
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

	std::vector<Node*> path = aStar->FindPath(startNode,goalNode,grid);	//경로탐색

	if(!path.empty())
	{
		std::cout << "경로 찾음.  탐색 경로:"<<'\n';
		//for(Node* node : path)
		//{
		//	std::cout
		//		<<"(" << node->position.x
		//		<<","
		//		<< node->position.y <<") ->"
		//		;//	<<"\n";
		//}

		//std::cout<<" 도착 \n";
		////맵출력
		//std::cout<<" 경로 맵 표시 결과 : \n";
		aStar->DisplayGridWithPath(grid,path);
	}

	else
	{
		std::cout<<" 경로 못 찾음. \n";
	}
}

DemoLevel::DemoLevel()
{
	SetActor(NodeType::START,AddActor(new Start(this),0));
	SetActor(NodeType::GOAL,AddActor(new Player(this),1));

	aStar =new AStar;	//Astar 객체

	//startNode = new Node();
	//goalNode = new Node();

	startNode = new Node(start->Position());
	goalNode = new Node(goal->Position());
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
}