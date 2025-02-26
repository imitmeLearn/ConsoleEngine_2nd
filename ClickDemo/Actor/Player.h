#pragma once

#include "Actor/DrawableActor.h"
#include "Level\DemoLevel.h"
//#include "../etc/Animation.h"

class Player: public DrawableActor
{
	RTTI_DECLARATIONS(Player,DrawableActor)

public:
	Player();
	Player(DemoLevel* level);

	virtual void Update(float deltaTime) override;

public:
private:
	DemoLevel* refLevel = nullptr;
};