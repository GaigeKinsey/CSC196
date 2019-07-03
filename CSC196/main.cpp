#include "..\\core\core.h"
#include "..\\math\math.h"
#include "..\\renderer\renderer.h"
#include "..\\external\core\include\core.h"

#include <iostream>
#include <assert.h>
#include <chrono>
#include <thread>
#include <random>

bool Update(float dt)
{
	bool quit = false;
	if (Core::Input::IsPressed(Core::Input::KEY_ESCAPE))
	{
		quit = true;
	}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	random_real_t random;

	color c(1.0f, 0.0f, 0.0f);
	graphics.SetColor(c);
	vector2 v1(random(800.0f), random(600.0f)); vector2 v2(random(800.0f), random(600.0f));
	graphics.DrawLine(v1.x, v1.y, v2.x, v2.y);
}

int main()
{
	char window[] = "CSC195";
	Core::Init(window, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();

	return 0;
}
