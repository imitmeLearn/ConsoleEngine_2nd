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
#include <string>

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
////std::vector<std::vector<int>> grid =
////{
////};
//std::vector<std::vector<int>> grid =
//{
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//	{1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,1},
//	{1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
//	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1},
//	{1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1},
//	{1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1},
//	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1},
//	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//};						//맵 끊은 경우
std::vector<std::vector<int>> grid =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1},
	{1,1,1,0,0,1,0,0,0,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
	{1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
	{1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
	//astar_path_node.clear();
	//astar_path_node =& aStar.FindPath(startNode,goalNode,grid);	//경로탐색

	//애니메이션을 위해, 현재 경로 저장
//	Set_curr_path_node(path_node);

	auto str = std::string(" test") + ": ";

	add_path_node_smart.clear();
	for(Node* node : path_node)
	{
		add_path_node_smart.push_back(std::make_shared<Node>(*node));

		str= str + ("(" + std::to_string(node->Position().x) + " - " + std::to_string(node->Position().y) + ") -> ");
	}
	auto t = str;

	//curr_path_node.clear();
	//curr_path_node = path_node ;
	//auto str = std::string(" test") + ": ";
	//str = str +std::to_string(startNode->Position().x)+ ",  "+ std::to_string(startNode->Position().y)+ " :::  ";
	//for(Node* node : curr_path_node)
	//{
	//	str= str + ("(" + std::to_string(node->Position().x) + " - " + std::to_string(node->Position().y) + ") -> ");
	//}
	//auto t = str;

	//add_path_node.clear();
	//for(const Node* node : path_node)
	//{
	//	add_path_node.push_back(new Node(*node));
	//} //메모리릭

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

				//애니메이션을 위해, 현재 액터 저장
				//curr_paths.push_back(path);
			}
		}
	}

	//SafeDelete(startNode);	//startNode는 openList 들어가기에, 해당부에서 지워짐. //또지우면 오류남.
	SafeDelete(goalNode);	//startNode는 openList 들어가기에, 해당부에서 지워짐. // 목표 노드만 제거 /목표노드는 안지우기에, 안지우면, 메모리릭 남.

	//isDraw = true;
}

void DemoLevel::RemoveCurrPathActor(Vector2 curr)
{
	if(!isRemovePath)
	{
		return;
	}
	for(auto* actor : actors)
	{
		auto path = actor->As<Path>();
		if(path)
		{
			if(path->Position() == curr)
			{
				Engine::Get().DestroyActor(actor);

				return;
			}
		}
	}
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

//void DemoLevel::PlayAnimation()
//{
//	animation = new Animation(curr_path_node);
//	/*if(start)
//	{
//		start->As<Player>()->PlayAnimation();
//	}*/
//}

void DemoLevel::StopAnimation()
{
	//초기화
	//curr_paths.clear();
	add_path_node_smart.clear();
	//curr_path_node.clear();
	nodePointer = -1;
	/*if(animation)
	{
		delete animation;
		animation = nullptr;
	} else{
		return;
	}*/
}

void DemoLevel::NextNode()
{
	++nodePointer;
}

//Vector2 DemoLevel::NextNodeDirection(const Vector2 start)
//{
//	auto next = GetGaolNodePosition(++nodePointer);
//	auto dir = GetDirection(start,next);
//	dir = Normalize(dir);
//	return	dir;
//}

//Vector2 DemoLevel:: Normalize(Vector2 vec)
//{
//	float length = sqrtf(powf(vec.x,2) + powf(vec.y,2));
//	Vector2 newVec = Vector2(vec.x/length,vec.y/length);
//	return newVec;
//}
//Vector2 DemoLevel::GetGaolNodePosition(int node)
//{
//	return 	curr_path_node[node]->Position();
//}
//Vector2 DemoLevel::GetGaolNodePosition()
//{
//	return 	curr_path_node[nodePointer]->Position();
//}
//Vector2 DemoLevel::GetNextPathDir(const Vector2& start)
//{
//	auto nextPos =	curr_paths[++nodePointer]->Position();
//	int x = 0;
//	int y = 0;
//
//	if(nextPos.x > start.x)
//	{
//		x = +1;
//	}
//
//	if(nextPos.x < start.x)
//	{
//		x = -1;
//	}
//
//	if(nextPos.y > start.y)
//	{
//		y = 1;
//	}
//
//	if(nextPos.y < start.y)
//	{
//		y = -1;
//	}
//
//	return Vector2(x,y);
//}
//Vector2 DemoLevel::GetNextPathDir(const Vector2& start)
//{
//	auto nextPos =	curr_path_node[++nodePointer]->Position();
//	int x = 0;
//	int y = 0;
//
//	if(nextPos.x > start.x)
//	{
//		x = +1;
//	}
//
//	if(nextPos.x < start.x)
//	{
//		x = -1;
//	}
//
//	if(nextPos.y > start.y)
//	{
//		y = 1;
//	}
//
//	if(nextPos.y < start.y)
//	{
//		y = -1;
//	}
//
//	return Vector2(x,y);
//}

bool DemoLevel::IsNextNodeGoal(Vector2 start)
{
	int nextNode = nodePointer+1;

	//다음노드가 목표노드 이거나
	if(add_path_node_smart[nextNode]->Position().x == goal->Position().x
		&& add_path_node_smart[nextNode]->Position().y == goal->Position().y)
	{
		return true;
	}
	return false;
}

Vector2 DemoLevel::CheckNextNode(Vector2 start)
{
	int nextNode = nodePointer+1;

	////다음노드가 목표노드 이거나
	//if(add_path_node_smart[nextNode]->Position().x == goal->Position().x
	//	&& add_path_node_smart[nextNode]->Position().y == goal->Position().y)
	//{
	//	return start;
	//}

	//다음노드가 있다면,
	if(add_path_node_smart.size() <= nextNode)
	{
		return start;
	}
	return add_path_node_smart[nextNode]->Position();
}

void  DemoLevel::SetNextPointer()
{
	nodePointer +=1;
}
Vector2 DemoLevel::GetNextNodeDir(const Vector2& start)
{
	//auto test_astar = astar_path_node; ***//요거 정리ㅜㅜㅜㅠㅜㅜㅜㅠㅜㅜㅠㅜㅜㅜ #1
	//auto _add_path_node = add_path_node; //가지고 있어
	//auto _add_path_node_smart = add_path_node_smart; //가지고 있어
	//auto test = curr_path_node; //없어

	////auto nextPos =	test[++nodePointer]->Position();
	//auto nextPos_r =	&test[++nodePointer]->Position();
	auto check_start = start;
	int x = 0;
	int y = 0;
	int nextNode = nodePointer + 1;
	//int nodeSize = add_path_node_smart.size();

	//다음노드가 없다면, 방형 변화 없음
	if(add_path_node_smart.size() <= nextNode)
	{
		return Vector2(0,0);
	}
	SetNextPointer();
	auto nextPos = add_path_node_smart[nodePointer]->Position(); //가지고 있어
	if(nextPos.x > start.x)
	{
		x = +1;
	}

	if(nextPos.x < start.x)
	{
		x = -1;
	}

	if(nextPos.y > start.y)
	{
		y = 1;
	}

	if(nextPos.y < start.y)
	{
		y = -1;
	}

	return Vector2(x,y);
}
Vector2 DemoLevel::GetDirection(Vector2 start,Vector2 end)
{
	auto dir =	end - start;
	return dir;
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

//"../Assets/Maps/MapABC.txt"

void DemoLevel::FileLoad(const char* str)
{
	FILE* file = nullptr;
	fopen_s(&file,str,"rb");		//원슬래시는 1개**

	if(file == nullptr)
	{
		std :: cout << "맵 파일 열기 실패. \n";

		__debugbreak();
		return;
	}

	fseek(file,0,SEEK_END);			//파일 읽기, 끝위치로 이동
	size_t readSize = ftell(file);	//이동한 위치의 FP 가져오기

	rewind(file);	//FP 원위치하는! 같은거// SET/ / fseek(file,0,SEEK_SET)//파일 읽기, 끝위치로 이동

	char* buffer = new char[readSize +1];	//파일 읽어서 버퍼에 담기
	size_t bytesRead =	fread(buffer,1,readSize,file);
	if(readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름 \n";
		__debugbreak();
		return ;
	}

	buffer[readSize] = '\0';

	int index=0;//파일 읽을 때 사용할 인덱스
	int xPosition = 0;
	int yPosition = 0;

	//맵 재생성을 위한 초기화 ->//@Test 오류있음. //todo: godi go
		//maps=nullptr;
	for(auto* map : maps)
	{
		map = nullptr;
	}

	for(auto* actor : actors)
	{
		if(actor)
		{
			if(/*actor->As<Player>()*/
				/*|| actor->As<Start>()*/
				actor->As<Path>()
				|| actor->As<Ground>()
				|| actor->As<Wall>()
			)
			{
				Engine::Get().DestroyActor(actor);
				continue;
			}
		}
	}

	while(index < (int)bytesRead)	//해석 파씽
	{
		char mapChar = buffer[index++];	//한 문자씩 읽기

		if(mapChar == '\n')
		{
			++yPosition;
			xPosition =0;
			continue;
		}

		if(mapChar == '1')
		{
			Wall * wall = new Wall(Vector2(xPosition,yPosition));
			AddActor(wall);
			maps.PushBack(wall);
		}

		else if(mapChar == '0')
		{
			Ground* ground =  new Ground(Vector2(xPosition,yPosition));
			AddActor(ground);
			maps.PushBack(ground);
		}

		++xPosition;
	}

	delete[] buffer;	//버퍼 삭제

	fclose(file);		//파일 닫기
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

	//aStar = new AStar();
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_SPACE))
	{
		isRemovePath = !isRemovePath;
	}

	/*if(Engine::Get().GetKeyDown(VK_NUMPAD1))
	{
		FileLoad("../Assets/Map.txt");
	}

	if(Engine::Get().GetKeyDown(VK_NUMPAD2))
	{
		FileLoad("../Assets/Map_main.txt");
	}

	if(Engine::Get().GetKeyDown(VK_NUMPAD3))
	{
		FileLoad("../Assets/Map_block.txt");
	}*/
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

	if(goal)
	{
		goal->Draw();
	}
	if(start)
	{
		start->Draw();
	}
}