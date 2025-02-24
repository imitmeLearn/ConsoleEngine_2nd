#include "Start.h"
#include "Engine/Engine.h"

Start::Start()
	: DrawableActor("s")
{
	color = Color::Red;
}

Start::Start(DemoLevel* level)
	: DrawableActor("s")
{
	color = Color::Red;
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