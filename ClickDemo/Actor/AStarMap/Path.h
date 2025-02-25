#pragma once

#include "Actor/DrawableActor.h"

class Path: public DrawableActor
{
	RTTI_DECLARATIONS(Path,DrawableActor)

public:
	Path();
	Path(const Vector2& position);

	virtual void Update(float deltaTime) override;

private:
};
