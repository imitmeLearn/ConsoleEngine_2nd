#pragma once
#include "Level/Level.h"
#include "Engine/Engine.h"

#include "../Algorithm/RBT/RedBlackTree.h"
#include "../Actor/RBT/NodeRBTActor.h"

class DrawableActor;
class RBTLevel: public Level
{
	RTTI_DECLARATIONS(RBTLevel,Level)

public:
	RBTLevel();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	void Init();
	void Initialization(const char * path,RedBlackTree * tree);
	void Insert(RedBlackTree * tree,std::vector<int> datas);
	void Print(RedBlackTree * tree);
private:
	RedBlackTree	tree;
	List<NodeRBTActor*> nodeRBTs;
};
