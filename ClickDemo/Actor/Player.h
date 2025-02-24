#pragma once

#include "Actor/DrawableActor.h"
#include "Level\DemoLevel.h"

class Player: public DrawableActor
{
	RTTI_DECLARATIONS(Player,DrawableActor)

public:
	Player();
	Player(DemoLevel* level);

	virtual void Update(float deltaTime) override;

private:
	DemoLevel* refLevel = nullptr;
};