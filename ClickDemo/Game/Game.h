#include <Engine/Engine.h>

#include "Level/DemoLevel.h"
class Game: public Engine
{
public:
	Game();
	void SetCursorPosition(int x,int y);
	static Game& Get() {
		return *instance;
	}
	~Game();

private:
	static Game* instance;
};
