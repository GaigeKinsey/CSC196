#include "game.h"
#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

void Game::Startup()
{
	m_scene.Startup();
	m_scene.Load("scene.txt");
}

void Game::Shutdown()
{
	m_scene.Shutdown();
}

void Game::Update(float dt)
{
	m_scene.Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	m_scene.Draw(graphics);
}
