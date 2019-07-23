#include "game.h"
#include "..\\external\core\include\core.h"

Game game;

bool Update(float dt)
{
	game.Update(dt);

	bool quit = false;
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE))
	{
		quit = true;
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);

}

int main()
{
	game.Startup();

	char window[] = "CSC196";
	Core::Init(window, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();

	AudioSystem::Instance()->Shutdown();
	AudioSystem::Instance()->Destroy();

	return 0;
}
