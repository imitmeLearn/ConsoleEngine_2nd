#include "Start.h"
#include "Engine/Engine.h"

Start::Start()
	: DrawableActor("s")
{
	color = Color::Blue;
}

Start::Start(DemoLevel* level)
	: DrawableActor("s")
{
	color = Color::Blue;
	position = Vector2(1,1);
	refLevel = level;
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		//if(!refLevel->isDraw) false;
		//
		//이미SE 생성된 위치에,재 생성 못하도록

		if(refLevel->IsClickedOutofMap()) return;

		position = Engine::Get().MousePosition();
		refLevel->DrawPath();
	}
}