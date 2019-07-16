#include "scene.h"
#include "player.h"
#include "missile.h"

void Scene::Startup()
{
	ActorFactory::Instance()->Register("Missile", new Creator<Missile, Actor>());
	ActorFactory::Instance()->Register("Player", new Creator<Player, Actor>());
}

void Scene::Shutdown()
{
	ActorFactory::Destroy();
	for (Actor* actor : m_actors) {
		delete actor;
	}
}

void Scene::Update(float dt)
{
	for (Actor* actor : m_actors) {
		actor->Update(dt);
	}

	for (auto iter = m_actors.begin(); iter != m_actors.end();) {
		Actor* actor = *iter;
		iter++;
		if (actor->destroy) {
			m_actors.remove(actor);
			delete actor;
		}
	}
}

void Scene::Draw(Core::Graphics& graphics)
{
	for (Actor* actor : m_actors) {
		actor->Draw(graphics);
	}
}

bool Scene::Load(const char* filename)
{
	rapidjson::Document document;
	json::load(filename, document);

	const rapidjson::Value& actors = document["actors"];

	if (actors.IsArray()) {
		LoadActors(actors);
	}
	
	const rapidjson::Value& spawners = document["spawners"];

	if (actors.IsArray()) {
		LoadSpawners(spawners);
	}

	return true;
}

void Scene::AddActor(Actor* actor)
{
	actor->SetScene(this);
	m_actors.push_back(actor);
}

bool Scene::LoadActors(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& actor_value = value[i];
		std::string type;
		if (json::get_string(actor_value, "type", type)) {
			Actor* actor = ActorFactory::Instance()->Create(type);
			if (actor && actor->Load(actor_value)) {
				AddActor(actor);
			}
		}
	}

	return true;
}

bool Scene::LoadSpawners(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& actor_value = value[i];
		std::string type;
		if (json::get_string(actor_value, "type", type)) {
			Actor* actor = ActorFactory::Instance()->Create(type);
			if (actor && actor->Load(actor_value)) {
				ActorFactory::Instance()->Register(actor->GetName(), new Spawner<Actor>(actor));
			}
		}
	}

	return true;
}