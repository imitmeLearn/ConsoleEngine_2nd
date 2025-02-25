﻿#pragma once
#include "Level/Level.h"
#include "Engine/Engine.h"

#include "../Algorithm/RBT/RedBlackTree.h"

class RBTLevel: public Level
{
	RTTI_DECLARATIONS(RBTLevel,Level)

public:
	RBTLevel();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	RedBlackTree	tree;
private:
	void Initialization(const char * path,RedBlackTree * tree);
	void Print(RedBlackTree * tree);
};
