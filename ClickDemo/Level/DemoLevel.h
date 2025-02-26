#pragma once

#include "Level/Level.h"
#include "Algorithm\AStar.h"
#include "Algorithm\Node.h"
#include <Actor\AStarMap\Path.h>
//#include "etc/Animation.h"
class DrawableActor;
class DemoLevel : public Level
{
	enum NodeType {
		START = 0
		, GOAL = 1

		, count
	};
	// RTTI 정의.
	RTTI_DECLARATIONS(DemoLevel, Level)
private:
	//시작, 끝 객체 지정
	void SetActor(NodeType type, Actor* actor);

public:
	DemoLevel();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	//경로그리기
	void DrawPath();
	void RemoveCurrPathActor(Vector2 curr);
	bool IsClickedOutofMap();

	//bool IsEmpty_curr_path_node ()
	//{
	//	return curr_path_node.empty();
	//}

	//void Set_curr_path_node(std::vector<Node*> path_node)
	//{
	//	curr_path_node = path_node;
	//}
	//std::vector<Node*> Curr_path_node()
	//{
	//	return curr_path_node;
	//}

	//void PlayAnimation();
	void StopAnimation();
	const int NodePointer()
	{
		return nodePointer;
	}
	void NextNode();
	//	Vector2 NextNodeDirection(const Vector2 start);
	Vector2 Normalize(Vector2 vec);
	bool IsNextNodeGoal(Vector2 start);
	//Vector2 GetNextNode(const Vector2 & start);
	//Vector2 GetNextNode();
	Vector2 CheckNextNode(Vector2 start);
	void SetNextPointer();
	//Vector2 GetGaolNodePosition(int node);
	//Vector2 GetGaolNodePosition();
	//Vector2 GetNextNodeDir(const Vector2& start);
	//Vector2 GetNextPathDir(const Vector2 & start);
	Vector2 GetNextNodeDir(const Vector2& start);
	Vector2 GetDirection(Vector2 start, Vector2 end);
private:
	//void SetActors();
	//void SetActors(std::vector<std::vector<int>>& grid);
	//void SetActors(std::vector<std::vector<int>>& grid,const std::vector<Node*>& path);
	//void DisplayGridWithPath(std::vector<std::vector<int>>& grid,std::vector<Node*>& path);
	void InitSetMapActors();
public:
	DrawableActor* start;
	DrawableActor* goal;

	//AStar* aStar;

	std::vector<std::vector<int>> origin_grid;

	//	bool isDraw;
	//	bool isInit=false;

	List <DrawableActor*> maps;	//벽 땅 액터 배열
	std::vector<DrawableActor*> curr_paths;	//순서대로 할 수 없어
	std::vector<Node*> curr_path_node;//노드정보 그대로 담아보기
	std::vector<Node*> add_path_node;//노드정보 그대로 담아보기
	std::vector<std::shared_ptr<Node>>  add_path_node_smart;//노드정보 그대로 담아보기
	const std::vector<Node*>* astar_path_node;//노드정보 그대로 담아보기

private:
	//Animation* animation = nullptr;
	int nodePointer = -1;
};