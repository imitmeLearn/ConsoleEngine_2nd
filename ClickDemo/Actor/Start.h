#pragma once

#include "Actor/DrawableActor.h"
#include "Level\DemoLevel.h"

class Start: public DrawableActor
{
public:
	Start();
	Start(DemoLevel* level);

	virtual void Update(float deltaTime) override;

private:
	DemoLevel* refLevel = nullptr;
};