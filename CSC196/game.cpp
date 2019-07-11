#include "game.h"
#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

void Game::Startup()
{
	rapidjson::Document document;
	json::load("actor.txt", document);

	m_actor.Load(document);
}

void Game::Shutdown()
{
}

void Game::Update(float dt)
{
	m_actor.Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	m_actor.Draw(graphics);

	//color c(1.0f, 0.0f, 0.0f);
	//graphics.SetColor(c);

	//vector2 v1(m_random(800.0f), m_random(600.0f));
	//vector2 v2(m_random(800.0f), m_random(600.0f));
	//graphics.DrawLine(v1.x, v1.y, v2.x, v2.y);
}
