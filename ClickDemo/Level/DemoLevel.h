#pragma once

#include "Level/Level.h"
#include "Algorithm\AStar.h"
#include "Algorithm\Node.h"

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

	//경로그리기
	void DrawPath();

private:

public:
	Actor* start;
	Actor* goal;

	AStar* aStar;

	Node* startNode;
	Node* goalNode;
};