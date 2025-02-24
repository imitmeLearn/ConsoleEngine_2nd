#pragma once

#include "Level/Level.h"
#include "Algorithm\AStar.h"
#include "Algorithm\Node.h"

class DrawableActor;
class DemoLevel: public Level
{
	enum NodeType{
		START = 0
		,GOAL = 1

		,count
	};
	// RTTI 정의.
	RTTI_DECLARATIONS(DemoLevel,Level)
private:
	//시작, 끝 객체 지정
	void SetActor(NodeType type,Actor* actor);

public:
	DemoLevel();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	//경로그리기
	void DrawPath();
private:
	void DrawMap();
	//void DisplayGridWithPath(std::vector<std::vector<int>>& grid,std::vector<Node*>& path);

public:
	DrawableActor* start;
	DrawableActor* goal;

	AStar* aStar;

	Node* startNode;
	Node* goalNode;
	std::vector<Node*> path_node;
};