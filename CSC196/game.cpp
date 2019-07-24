#include "game.h"
#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

void Game::Startup()
{
	AudioSystem::Instance()->Startup();
	m_state = eState::INIT;
}

void Game::Shutdown()
{
	if (m_scene) {
		m_scene->Shutdown();
		delete m_scene;
	}
}

void Game::Update(float dt)
{
	switch (m_state)
	{
	case Game::INIT:
		m_state = eState::TITLE;
		break;
	case Game::TITLE:
		if (Core::Input::IsPressed(Core::Input::KEY_SPACE)) {
			m_state = eState::START_GAME;
		}
		break;
	case Game::START_GAME:
		m_lives = 5;
		m_score = 0;
		m_scene = new Scene(this);
		m_scene->Startup();
		m_scene->Load("scene.txt");
		m_state = eState::UPDATE_GAME;
		break;
	case Game::UPDATE_GAME:
		if (m_lives == 0) {
			m_stateTimer = 3.0f;
			m_state = eState::GAME_OVER;
		}
		m_scene->Update(dt);
		AudioSystem::Instance()->Update();
		break;
	case Game::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_state = eState::RESET;
		}
		break;
	case Game::RESET:
		m_scene->Shutdown();
		delete m_scene;
		m_scene = nullptr;

		AudioSystem::Instance()->Shutdown();

		Startup();
		break;
	default:
		break;
	}
}

void Game::Draw(Core::Graphics& graphics)
{
	color textcolor = color::white;
	graphics.SetColor(textcolor);

	switch (m_state)
	{
	case Game::INIT:
		break;
	case Game::TITLE:
		graphics.DrawString(400, 300, "Shootyshoots");
		break;
	case Game::START_GAME:
		break;
	case Game::UPDATE_GAME:
	{
		std::string score = "Score: " + std::to_string(m_score);
		std::string lives = "Lives: " + std::to_string(m_lives);

		graphics.DrawString(20, 20, score.c_str());
		graphics.DrawString(20, 40, lives.c_str());
	}
		m_scene->Draw(graphics);
		break;
	case Game::GAME_OVER:
		graphics.DrawString(400, 300, "Game Over");
		break;
	default:
		break;
	}
}
