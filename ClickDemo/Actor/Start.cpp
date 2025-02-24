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
		position = Engine::Get().MousePosition();
		refLevel->DrawPath();
	}
}