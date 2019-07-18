#pragma once

#include "actor.h"
#include "..\\framework\factory.h"
#include "..\\framework\singleton.h"
#include <list>

class ActorFactory : public Factory<Actor>, public Singleton<ActorFactory> {
protected:
	ActorFactory() {}
	friend class Singleton<ActorFactory>;
};

class Scene {
public:
	Scene() {}
	~Scene() {}

	void Startup();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	bool Load(const char* filename);

	void AddActor(Actor* actor);

	Actor* GetActorByName(const std::string& name);
	std::vector<Actor*> GetActorsByTag(const std::string& tag);

protected:
	bool LoadActors(const rapidjson::Value& value);
	bool LoadSpawners(const rapidjson::Value& value);

private:
	std::list<Actor*> m_actors;
	float m_spawnTimer = 0.0f;
};