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
		position = Engine::Get().MousePosition();
		refLevel->DrawPath();
	}
}