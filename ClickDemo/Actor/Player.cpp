#include "Player.h"
#include "Engine/Engine.h"

Player::Player()
	: DrawableActor("e")
{
	color = Color::Green;
	position = Vector2(5,5);
}

Player::Player(DemoLevel * level)
	: DrawableActor("e")
{
	color = Color::Green;
	position = Vector2(5,5);
	refLevel = level;
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if(Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if(Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		//if(!refLevel->isDraw) false;

		//이미SE 생성된 위치에,재 생성 못하도록
		if(refLevel->goal->Position() ==  Engine::Get().MousePosition()
			||refLevel->start->Position() ==  Engine::Get().MousePosition())
		{
			return;
		}
		position = Engine::Get().MousePosition();
		refLevel->DrawPath();
	}
}