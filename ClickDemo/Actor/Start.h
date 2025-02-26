#pragma once

#include "Actor/DrawableActor.h"
#include "Level\DemoLevel.h"

class Start: public DrawableActor
{
	RTTI_DECLARATIONS(Start,DrawableActor)

public:
	Start();
	Start(DemoLevel* level);

	virtual void Update(float deltaTime) override;
	//void SetCurrPath(const std::vector<Node*>& path_node) {
	//	curr_path_node = path_node;
	//}

	void PlayAnimation();
	void StopAnimation();
	void PlayAnimation(float deltaTime);
	bool isArrived();
	bool isArrived(Vector2 start,Vector2 next);
private:
	DemoLevel* refLevel = nullptr;
	//Animation* animation = nullptr;
	float speed = 10.f;
	float yPosition = 0.f;
	float xPosition = 0.f;
	Vector2 direction = Vector2(0.f,0.f);
	Vector2 tempPos;
};