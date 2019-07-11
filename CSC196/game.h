#pragma once

#include "actor.h"
#include "..\\core\core.h"
#include "..\\framework\singleton.h"
#include "..\\external\core\include\core.h"

class Game : public Singleton<Game> {
public:
	void Startup();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

protected:
	Game() {}

	friend class Singleton<Game>;

private:
	random_real_t m_random;
	Actor m_actor;
};
