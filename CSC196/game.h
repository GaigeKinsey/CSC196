#pragma once

#include "scene.h"

class Game {
public:
	enum eState {
		INIT,
		TITLE,
		START_GAME,
		UPDATE_GAME,
		GAME_OVER,
		RESET
	};

public:
	Game() {}
	~Game() {}

	void Startup();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	int GetScore() { return m_score; }
	void SetScore(int score) { m_score = score; }

	int GetLives() { return m_lives; }
	void SetLives(int lives) { m_lives = lives; }

private:
	random_real_t m_random;
	Scene* m_scene = nullptr;

	int m_score = 0;
	int m_lives = 0;

	eState m_state = eState::INIT;
	float m_stateTimer = 0;
};
