#include "game.h"
#include "..\\math\math.h"
#include "..\\renderer\renderer.h"

void Game::Startup()
{
}

void Game::Shutdown()
{
}

void Game::Update(float dt)
{
}

void Game::Draw(Core::Graphics& graphics)
{
	color c(1.0f, 0.0f, 0.0f);
	graphics.SetColor(c);

	vector2 v1(m_random(800.0f), m_random(600.0f));
	vector2 v2(m_random(800.0f), m_random(600.0f));
	graphics.DrawLine(v1.x, v1.y, v2.x, v2.y);
}
