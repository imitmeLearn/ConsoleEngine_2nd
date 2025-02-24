#pragma once

#include "Actor/DrawableActor.h"

class Path: public DrawableActor
{
public:
	Path();

	virtual void Update(float deltaTime) override;

private:
};
