#include "Path.h"

Path::Path()
	:DrawableActor("+")
{
	color=(Color)((int)Color::Red + (int)Color::Green);
}

void Path::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	//todo :테스트용 나중에 지우기?
	//if(Engine::Get().GetKeyDown(VK_RBUTTON)
	//	||Engine::Get().GetKeyDown(VK_LBUTTON))
	//{
	//	//std::cout<<"클릭";
	//	position = Engine::Get().MousePosition();
	//}
}