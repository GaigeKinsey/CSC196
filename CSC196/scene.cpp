#include "scene.h"
#include "player.h"
#include "missile.h"
#include "enemy.h"
#include "emitter.h"
#include "..\\effects\particle_system.h"

void Scene::Startup()
{
	m_particleSystem = new ParticleSystem(200);

	m_actorFactory = new ActorFactory;
	m_actorFactory->Register("Missile", new Creator<Missile, Actor>());
	m_actorFactory->Register("Player", new Creator<Player, Actor>());
	m_actorFactory->Register("Enemy", new Creator<Enemy, Actor>());
	m_actorFactory->Register("Emitter", new Creator<Emitter, Actor>());
}

void Scene::Shutdown()
{
	delete m_particleSystem;
	delete m_actorFactory;
	for (Actor* actor : m_actors) {
		delete actor;
	}
}

void Scene::Update(float dt)
{
	m_spawnTimer = m_spawnTimer + dt;
	if (m_spawnTimer >= 2.0f) {
		m_spawnTimer = 0.0f;
		Actor* actor = m_actorFactory->Create("Enemy_Spawner");

		random_real_t random;
		actor->m_transform.translation = vector2(random(800.0f), random(600.0f));
		actor->m_transform.rotation = random(math::TWO_PI);
		AddActor(actor);
	}

	for (Actor* actor : m_actors) {
		actor->Update(dt);
	}

	for (auto iter = m_actors.begin(); iter != m_actors.end();) {
		if ((*iter)->m_destroy) {
			delete *iter;
			iter = m_actors.erase(iter);
		}
		else {
			iter++;
		}
	}
	m_particleSystem->Update(dt);
}

void Scene::Draw(Core::Graphics& graphics)
{
	for (Actor* actor : m_actors) {
		actor->Draw(graphics);
	}

	m_particleSystem->Draw(graphics);
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

Actor* Scene::GetActorByName(const std::string& name)
{
	Actor* actor = nullptr;

	for (Actor* actor_ : m_actors) {
		if (actor_->GetName() == name) {
			actor = actor_;
			break;
		}
	}

	return actor;
}

std::vector<Actor*> Scene::GetActorsByTag(const std::string& tag)
{
	std::vector<Actor*> actors;

	for (Actor* actor : m_actors) {
		if (actor->GetTag() == tag) {
			actors.push_back(actor);
		}
	}

	return actors;
}

bool Scene::LoadActors(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& actor_value = value[i];
		std::string type;
		if (json::get_string(actor_value, "type", type)) {
			Actor* actor = m_actorFactory->Create(type);
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
			Actor* actor = m_actorFactory->Create(type);
			if (actor && actor->Load(actor_value)) {
				m_actorFactory->Register(actor->GetName(), new Spawner<Actor>(actor));
			}
		}
	}

	return true;
}
