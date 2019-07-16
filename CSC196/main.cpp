#include "game.h"
#include "..\\framework\factory.h"
#include "..\\external\core\include\core.h"

#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>
#include <random>

//class GameObject {};
//class Player : public GameObject {};
//class Enemy : public GameObject {};

//random_real_t random;

bool Update(float dt)
{
	Game::Instance()->Update(dt);

	bool quit = false;
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE))
	{
		quit = true;
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	Game::Instance()->Draw(graphics);

}

int main()
{
	Game::Instance()->Startup();

	//Factory<GameObject> factory;

	//factory.Register("PLAYER", new Creator <Player, GameObject>);
	//factory.Register("ENEMY", new Creator <Enemy, GameObject>);

	//GameObject* go = factory.Create("PLAYER");

	char window[] = "CSC196";
	Core::Init(window, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();

	Game::Instance()->Shutdown();
	Game::Instance()->Destroy();

	return 0;
}
